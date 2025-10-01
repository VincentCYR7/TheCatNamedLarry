#include "Player.h"
using namespace s3d;

Player::Player(const Vec2& pos, const Texture& tex, const Size& si)
    : Entity(pos, tex, si)
{}


void Player::update() {
	if (position.y > 1000) {
		position = Vec2{200, 100};
		velocity = Vec2{0, 0};
	}

    prevHitbox = getHitbox();
	isMoving = false;
	updateInput();
	updateAnim();
 
}

void Player::updateInput() {
	if (isGrounded && (KeySpace.pressed() || KeyUp.pressed())) {
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
}

void Player::updateAnim(){
	animTimer += 0.02;

while (animTimer >= animInterval) {
    animTimer -= animInterval;

    const bool airborne = !isGrounded;

    if (airborne) {
        // Airborne frames: force a specific pose
        curSpriteMoving = isMoving ? 3 : 0;
    } else {
        if (isMoving) {
            // Grounded + moving: advance [0..3]
            curSpriteMoving = (curSpriteMoving + 1) % 4;
        } else {
            // Grounded + idle
            if (!isBlinking) {
                // Normal idle cycle [0..4]
                curSpriteIdle++;
                if (curSpriteIdle > 4) curSpriteIdle = 0;
            } else {
                // Blinking sequence: 1 -> 5,6,7 -> 0 (then stop blinking)
                if (curSpriteIdle < 1) {
                    curSpriteIdle = 1;              // snap to blink start if needed
                } else if (curSpriteIdle == 1) {
                    curSpriteIdle = 5;              // jump into blink frames
                } else if (curSpriteIdle >= 7) {
                    curSpriteIdle = 0;
                    isBlinking = false;
                } else {
                    ++curSpriteIdle;                // 5 -> 6 -> 7
                }
            }
        }
    }

    // Blink trigger: only when grounded, idle, at frame 1
    if (!airborne && !isMoving && curSpriteIdle == 1) {
        isBlinking = (Random(0, 6) == 3);
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
			case 5:
				larryIdle5Texture.scaled(0.5).mirrored(!facingLeft).drawAt(position);
				break;
			case 6:
				larryIdle6Texture.scaled(0.5).mirrored(!facingLeft).drawAt(position);
				break;
			case 7:
				larryIdle7Texture.scaled(0.5).mirrored(!facingLeft).drawAt(position);
				break;
			default:
				texture.scaled(0.5).mirrored(!facingLeft).drawAt(position);
				break;
    	}	
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


