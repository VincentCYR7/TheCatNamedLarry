#include "CollisionManager.h"
#include "Entity.h"
#include "GamePlatform.h"

// Tunables for feel
namespace {
    constexpr double kSkin  = 2.0;   // allowed penetration below top (px)
    constexpr double kSnap  = 3.0;   // snap distance when hovering just above (px)
    constexpr double kMinFallSpeedForSnap = 20.0; // px/s
}

void CollisionManager::checkCollisions(s3d::Array<Entity*>& entities) {
    for (size_t i = 0; i < entities.size(); ++i) {
        for (size_t j = i + 1; j < entities.size(); ++j) {
            Entity* a = entities[i];
            Entity* b = entities[j];

            if (a->getHitbox().intersects(b->getHitbox())) {
                handleCollision(a, b);
            }
        }
    }
}

void CollisionManager::handleCollision(Entity* a, Entity* b) {
    // TODO: specialize by type if needed
    // Example: walls, enemies, pickups...
}

void CollisionManager::resolveGrounding(Entity* player, const std::vector<GamePlatform*>& platforms) {
    if (Time::GetSec() < player->ignoreGroundUntil) return;
    player->isGrounded = false;

    const s3d::RectF boxNow  = player->getHitbox();
    const s3d::RectF boxPrev = player->prevHitbox;  
    const double halfH       = boxNow.h * 0.5;

    const double bottomNow   = boxNow.y + boxNow.h;
    const double bottomPrev  = boxPrev.y + boxPrev.h;
    const bool   falling     = (player->velocity.y > kMinFallSpeedForSnap);

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

        const double gap = top - bottomNow;
        const double pen = -gap;

        // A) within skin from above
        const bool withinSkinFromAbove =
            (pen >= 0.0) && (pen <= kSkin) && (bottomPrev <= top + kSkin);

        // B) snap when just above and falling
        const bool snapFromAbove =
            falling && (gap > 0.0) && (gap <= kSnap) && (bottomPrev <= top + kSnap);

        if (withinSkinFromAbove || snapFromAbove) {
            if (!best || std::abs(gap) < std::abs(best->gap)) {
                best = Candidate{ platform, top, gap };
            }
        }
    }

    if (best) {
        // Clamp to surface: entity pos is CENTER
        const double centerX = player->GetPos().x;
        const double centerY = best->topY - halfH;

        player->SetPos({ centerX, centerY });
        player->velocity.y = 0.0;
        player->isGrounded = true;
    }
}
