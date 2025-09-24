#pragma once
#include <Siv3D.hpp>
#include <vector>

// Forward declares
class Entity;
class GamePlatform;

class CollisionManager {
public:
    // General collision check between arbitrary entities
    void checkCollisions(s3d::Array<Entity*>& entities);

    // Handle generic collisions (extend with dynamic_cast or tags)
    void handleCollision(Entity* a, Entity* b);

    // Resolve player grounding against platforms
    void resolveGrounding(Entity* player, const std::vector<GamePlatform*>& platforms);
};
