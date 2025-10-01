#include "GamePlatform.h"

GamePlatform::GamePlatform(const Vec2& pos, const Texture& tex, const Size& si)
    : Entity(pos, tex, si) {}

void GamePlatform::update() {

}

void GamePlatform::draw() {    
    texture.scaled(0.31).drawAt(Vec2{position.x, position.y + size.y}); // default draw top-left
	getHitbox().drawFrame(2, 0, Palette::Red);
}

RectF GamePlatform::getHitbox() const {
    return RectF{ position, size };
}