#include "Player.h"
using namespace s3d;

Player::Player(const Vec2& pos, const Texture& tex, const Size& si)
    : Entity(pos, tex, si)
{}



void Player::update(bool scroll) {
    prevHitbox = getHitbox();

    if (isGrounded && KeySpace.pressed()) {
        ignoreGroundUntil = Scene::Time() + 0.5;
        velocity.y = jumpStrength;
        isGrounded = false;
    }
	if (!isGrounded)
	{
		velocity.y += gravity;
		position += velocity * Scene::DeltaTime();
	}

    if (KeyA.pressed())
    {
        position.x -= speed * Scene::DeltaTime();
		facingLeft = true;
;
    }
    if (KeyD.pressed())
    {
        position.x += speed * Scene::DeltaTime();
		facingLeft = false;
    }


}



void Player::draw() {
    texture.scaled(0.2).mirrored(!facingLeft).drawAt(position);
    //getHitbox().drawFrame(2, 0, Palette::Red);
}

RectF Player::getHitbox() const {
    return RectF{ Vec2{position.x - (size.x/2), position.y - (size.y/2)}, size};
}


