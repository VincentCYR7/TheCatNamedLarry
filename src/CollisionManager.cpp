#include "CollisionManager.h"
#include "Entity.h"
#include "GamePlatform.h"

// Tunables for feel
namespace {
    constexpr double kSkin  = 2.0;   // allowed penetration below top (px)
    constexpr double kSnap  = 3.0;   // snap distance when hovering just above (px)
    constexpr double kMinFallSpeedForSnap = 20.0; // px/s
	constexpr double kHover = 0.5;
}

void CollisionManager::checkCollisions(std::vector<std::unique_ptr<Entity>>& entities) {
    for (size_t i = 0; i < entities.size(); ++i) {
        for (size_t j = i + 1; j < entities.size(); ++j) {
            Entity* a = entities[i].get();  // .get() gives raw pointer
            Entity* b = entities[j].get();

            if (a->getHitbox().intersects(b->getHitbox())) {
                handleCollision(a, b);
            }
        }
    }
}

inline bool isStaticEntity(const Entity* e) {
    return dynamic_cast<const GamePlatform*>(e) != nullptr;
}

static inline double dot(const s3d::Vec2& a, const s3d::Vec2& b) {
    return a.x * b.x + a.y * b.y;
}

void CollisionManager::handleCollision(Entity* a, Entity* b) {
    // Axis-aligned boxes
    const s3d::RectF ra = a->getHitbox();
    const s3d::RectF rb = b->getHitbox();

    // Centers and half-sizes
    const s3d::Vec2 ca{ ra.x + ra.w * 0.5, ra.y + ra.h * 0.5 };
    const s3d::Vec2 cb{ rb.x + rb.w * 0.5, rb.y + rb.h * 0.5 };
    const s3d::Vec2 ha{ ra.w * 0.5, ra.h * 0.5 };
    const s3d::Vec2 hb{ rb.w * 0.5, rb.h * 0.5 };

    // Delta & overlaps
    const s3d::Vec2 d = cb - ca;
    const double ox = (ha.x + hb.x) - std::abs(d.x);
    const double oy = (ha.y + hb.y) - std::abs(d.y);
    if (ox <= 0 || oy <= 0) return; // no longer overlapping

    // MTV normal & penetration (push along the smaller overlap)
    s3d::Vec2 n;
    double pen;
    if (ox < oy) {
        n = { (d.x >= 0.0) ? 1.0 : -1.0, 0.0 };
        pen = ox;
    } else {
        n = { 0.0, (d.y >= 0.0) ? 1.0 : -1.0 };
        pen = oy;
    }

    // Who moves? (platforms/static don't)
    const bool aStatic = isStaticEntity(a);
    const bool bStatic = isStaticEntity(b);

    s3d::Vec2 corr = n * pen;

    if (!aStatic && !bStatic) {
        // split correction
        a->SetPos(a->GetPos() - corr * 0.5);
        b->SetPos(b->GetPos() + corr * 0.5);
    } else if (!aStatic && bStatic) {
        // move A only
        // optional hover for floor contacts
        if (kHover > 0.0 && n.y < 0.0) corr.y += kHover;
        a->SetPos(a->GetPos() - corr);
    } else if (aStatic && !bStatic) {
        // move B only
        if (kHover > 0.0 && n.y > 0.0) corr.y += kHover;
        b->SetPos(b->GetPos() + corr);
    } else {
        // both static—nothing to do
        return;
    }

    // Zero the normal component of velocity (no sticking through)
    // Note: we use each body's own velocity against the collision normal.
    const double vAn = dot(a->velocity, n);
    const double vBn = dot(b->velocity, n);

    if (!aStatic && vAn > 0.0) a->velocity -= n * vAn; // A moving into B along n
    if (!bStatic && vBn < 0.0) b->velocity -= n * vBn; // B moving into A along -n

    // Grounding hint (optional): if A ended up above B with vertical MTV, mark grounded
    if (n.y < 0.0 && !aStatic) { a->isGrounded = true; }
    if (n.y > 0.0 && !bStatic) { b->isGrounded = true; }
}


void CollisionManager::resolveGrounding(Entity* player, const std::vector<GamePlatform*>& platforms) {
    if (player->velocity.y < 0) return;
    player->isGrounded = false;

    const s3d::RectF boxNow  = player->getHitbox();
    const s3d::RectF boxPrev = player->prevHitbox;
    const double halfH       = boxNow.h * 0.5;

    // Effective bottoms used for tests so we still "count" as grounded while hovering
    const double bottomNowEff  = (boxNow.y + boxNow.h)  + kHover;
    const double bottomPrevEff = (boxPrev.y + boxPrev.h) + kHover; 

    const bool falling = (player->velocity.y > kMinFallSpeedForSnap);

    struct Candidate {
        const GamePlatform* plat = nullptr;
        double topY = 0.0;
        double gap  = 0.0;
    };
    std::optional<Candidate> best;

    for (const auto* platform : platforms) {
        const s3d::RectF p = platform->getHitbox();
        const double top   = p.y;

        // Horizontal overlap check
        const bool overlapX =
            (boxNow.x + boxNow.w > p.x) &&
            (boxNow.x < p.x + p.w);

        if (!overlapX) continue;

        // Compute gap/penetration with the effective bottom (includes hover)
        const double gap = top - bottomNowEff; 
        const double pen = -gap;

        // A) within skin from above (using effective bottom)
        const bool withinSkinFromAbove =
            (pen >= 0.0) && (pen <= kSkin) && (bottomPrevEff <= top + kSkin); 

        // B) snap when just above and falling (using effective bottom)
        const bool snapFromAbove =
            falling && (gap > 0.0) && (gap <= kSnap) && (bottomPrevEff <= top + kSnap);

        if (withinSkinFromAbove || snapFromAbove) {
            if (!best || std::abs(gap) < std::abs(best->gap)) {
                best = Candidate{ platform, top, gap };
            }
        }
    }

    if (best) {
        // Place CENTER so that the bottom is kHover above the platform
        const double centerX = player->GetPos().x;
        const double centerY = best->topY - halfH - kHover;  // <- CHANGED: hover above

        player->SetPos({ centerX, centerY });
        player->velocity.y = 0.0;
        player->isGrounded = true;
    }
}
