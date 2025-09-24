#include "GamePlatform.h"

GamePlatform::GamePlatform(const Vec2& pos, const Texture& tex, const Size& si)
    : Entity(pos, tex, si) {}

void GamePlatform::update(bool scroll) {
    if (scroll) {
        position.x -= 2; // Example scroll speed
    }
}

void GamePlatform::draw() {
    texture.resized(size).draw(position);
    //getHitbox().drawFrame(2, 0, Palette::Red);
}

RectF GamePlatform::getHitbox() const {
    return RectF{ position, size };
}