#pragma once
#include <Siv3D.hpp>
#include "Entity.h"
#include "Player.h"
#include "GamePlatform.h"

class CollisionManager {
public:
    // Checks collisions between all entities
    void checkCollisions(Array<Entity*>& entities);

    // Checks if the player is grounded on any platform
    void checkGrounded(Entity* player, const std::vector<GamePlatform*>& platforms);

private:
    void handleCollision(Entity* a, Entity* b);
};