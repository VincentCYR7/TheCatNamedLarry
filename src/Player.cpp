#include "Player.h"
using namespace s3d;

Player::Player(const Vec2& pos, const Texture& tex, const Size& si)
    : Entity(pos, tex, si)
{}



void Player::update() {
    prevHitbox = getHitbox();
	isMoving = false;
    if (isGrounded && KeySpace.pressed()) {
        ignoreGroundUntil = Scene::Time() + 0.5;
        velocity.y = jumpStrength;
        isGrounded = false;
    }
	if (!isGrounded)
	{
		velocity.y += gravity;
		position += velocity * 0.005;
	}

    if (KeyLeft.pressed())
    {
        position.x -= speed * 0.005;
		facingLeft = true;
		isMoving = true;
    }
    if (KeyRight.pressed())
    {
        position.x += speed * 0.005;
		facingLeft = false;
		isMoving = true;
    }


	animTimer += 0.02;

	while (animTimer >= animInterval) {
		animTimer -= animInterval;
		if (isMoving) {
			curSpriteMoving++;
		}
		else {
			curSpriteIdle++;
		}
		
	}

	if (isMoving && !isGrounded){
		curSpriteMoving = 3;
	}
	else if (!isMoving && !isGrounded){
		curSpriteMoving = 0;
	}
	else if (isMoving) {
		if (curSpriteMoving > 3) {
			curSpriteMoving = 0;
		}
	}
	else if (isGrounded) {
		if (curSpriteIdle > 4) {
			curSpriteIdle = 0;
		}
	}
 
}



void Player::draw() {
    //texture.scaled(0.5).mirrored(!facingLeft).drawAt(position);
    getHitbox().drawFrame(2, 0, Palette::Red);
	if (isMoving) {
		switch (curSpriteMoving) {
			case 0:
				texture.scaled(0.5).mirrored(!facingLeft).drawAt(position);
				break;
			case 1:
				larryRun1Texture.scaled(0.5).mirrored(!facingLeft).drawAt(position);
				break;
			case 2:
				larryRun2Texture.scaled(0.5).mirrored(!facingLeft).drawAt(position);
				break;
			case 3:
				larryRun3Texture.scaled(0.5).mirrored(!facingLeft).drawAt(position);
				break;
			default:
				texture.scaled(0.5).mirrored(!facingLeft).drawAt(position);
				break;
    	}	
	} else {
		switch (curSpriteIdle) {
			case 0:
				texture.scaled(0.5).mirrored(!facingLeft).drawAt(position);
				break;
			case 1:
				larryIdle1Texture.scaled(0.5).mirrored(!facingLeft).drawAt(position);
				break;
			case 2:
				larryIdle2Texture.scaled(0.5).mirrored(!facingLeft).drawAt(position);
				break;
			case 3:
				larryIdle3Texture.scaled(0.5).mirrored(!facingLeft).drawAt(position);
				break;
			case 4:
				larryIdle4Texture.scaled(0.5).mirrored(!facingLeft).drawAt(position);
				break;
			default:
				texture.scaled(0.5).mirrored(!facingLeft).drawAt(position);
				break;
    	}	


		//texture.scaled(0.5).mirrored(!facingLeft).drawAt(position);
	}

}

RectF Player::getHitbox() const {
    float centerCorrection;
    if (facingLeft) {
        centerCorrection = -20.0f;
    } else {
        centerCorrection = 20.0f;
    }
    return RectF{ Vec2{position.x - (size.x/2) + centerCorrection, position.y - (size.y/2)}, size};
}


