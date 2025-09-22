#include "CollisionManager.h"

void CollisionManager::checkCollisions(Array<Entity*>& entities) {
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
    // Placeholder: customize based on entity types
    // Example: push player out of wall, trigger damage, etc.
    // You can use dynamic_cast or tags to specialize behavior
}

void CollisionManager::checkGrounded(Entity* player, const std::vector<GamePlatform*>& platforms) {
    constexpr double groundTolerance = 2.0; // Adjustable vertical margin
    player->isGrounded = false;

    const RectF playerBox = player->getHitbox();
    const double playerBottomY = playerBox.y + playerBox.h;

    for (const auto& platform : platforms) {
        const RectF platformBox = platform->getHitbox();
        const double platformTopY = platformBox.y;

        // Check horizontal overlap
        const bool horizontalOverlap =
            playerBox.x + playerBox.w > platformBox.x &&
            playerBox.x < platformBox.x + platformBox.w;

        // Check vertical proximity (player just above platform)
        const bool verticalTouch =
            Abs(playerBottomY - platformTopY) <= groundTolerance;

        if (horizontalOverlap && verticalTouch) {
            player->isGrounded = true;
            //player->velocity.y = 0;
            break;
        }
        //player->isGrounded = true;
        //player->velocity.y = 0;

    }
}