#include "Player.h"
using namespace s3d;

Player::Player(const Vec2& pos, const Texture& tex)
    : Entity(pos, tex)
    , targetPos(pos) // start with current position
{}



void Player::update(bool scroll) {
	
	if (MouseR.down()) {
        targetPos = Cursor::PosF();
		targetPos.y -= 80;
		double dx = targetPos.x - position.x;
    	if (dx > 0.01 * speed || dx < -0.01 * speed) {
        	facingLeft = (targetPos.x < position.x);
    	}
    }

    const Vec2 delta = (targetPos - position);
    const double distance = delta.length();
    const Vec2 direction = (distance > 0.0) ? (delta / distance) : Vec2::Zero();

    Circle{ Vec2(targetPos.x, targetPos.y + 80), 5 }.draw(ColorF{ 0.4, 0.4, 0.4 });

	if(scroll) {
		updateScroll();
	}

    if (distance > 1.0) {
        position += direction * speed * Scene::DeltaTime();
    } else {
        position = targetPos;
    }



    if (MouseL.down() && attackCoolDown >= 0.6) {
		attackCoolDown = 0;
        atkAnimInterval = 0.06;
        isAttacking = true;
		if (!facingLeft) {
			hitbox = Rect(position.x + 50, position.y - 50, 50, 150);
		}
		else if (facingLeft) {
			hitbox = Rect(position.x - 100, position.y - 50, 50, 150);
		}
    } else if (atkAnimInterval > 0) {
        atkAnimInterval -= Scene::DeltaTime();
		isAttacking = true;
		if (!facingLeft) {
			hitbox = Rect(position.x + 50, position.y - 50, 60, 150);
		}
		else if (facingLeft) {
			hitbox = Rect(position.x - 110, position.y - 50, 60, 150);
		}
    } else if (atkAnimInterval <= 0){
        isAttacking = false;
    }

	if (attackCoolDown < 0.6) {
		attackCoolDown += Scene::DeltaTime();
	}

	collider.setPos(position);


	// if (hitbox.intersects(otherHitbox) && isAttacking) {
    // 	// Collision detected
	// }
}

void Player::updateScroll() {
	targetPos.x = Max(50.0, targetPos.x - 75 * Scene::DeltaTime());
}


	





void Player::draw() {
    if (isAttacking) {
        knightAtkTexture.scaled(0.2).mirrored(facingLeft).drawAt(position);
		//hitbox.drawFrame(2, ColorF(1.0, 0.0, 0.0));
    } else {
        texture.scaled(0.2).mirrored(!facingLeft).drawAt(position);
    }

	//collider.draw();

	//Circle{position, 10}.draw(ColorF{ 1, 0.4, 0.4 });
}
