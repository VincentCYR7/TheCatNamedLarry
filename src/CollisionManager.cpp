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

void CollisionManager::handleCollision(Entity* a, Entity* b) {
	ClearPrint();
    Print << U"collided";

	
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
