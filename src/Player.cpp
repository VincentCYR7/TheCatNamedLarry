#include "Player.h"
using namespace s3d;

Player::Player(const Vec2& pos, const Texture& tex, const Size& si)
    : Entity(pos, tex, si)
    , targetPos(pos) // start with current position
{}



void Player::update(bool scroll) {
	if (!isGrounded)
	{
		velocity.y += gravity * Scene::DeltaTime();
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
	if (KeySpace.down()) {

	}
}



void Player::draw() {
    texture.scaled(0.2).mirrored(!facingLeft).drawAt(position);
}
