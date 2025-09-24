#include "GamePlatform.h"

GamePlatform::GamePlatform(const Vec2& pos, const Texture& tex, const Size& si)
    : Entity(pos, tex, si) {}

void GamePlatform::update() {

}

void GamePlatform::draw() {
    //texture.resized(size).draw(position);
    //getHitbox().drawFrame(2, 0, Palette::Red);
    texture.scaled(0.31).drawAt(Vec2{position.x, position.y + size.y}); // default draw top-left
}

RectF GamePlatform::getHitbox() const {
    return RectF{ position, size };
}