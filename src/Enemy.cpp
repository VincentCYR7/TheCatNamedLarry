#include "Enemy.h"
using namespace s3d;

Enemy::Enemy(const Vec2& pos, const Texture& tex)
    : Entity(pos, tex)// start with current position
{}



void Enemy::update(bool scroll) {


	if(movingTime > 0.0){

		movingTime -= Scene::DeltaTime();
		

		position.x = Math::Lerp(position.x,movingToPos.x,Scene::DeltaTime());
		position.y = Math::Lerp(position.y,movingToPos.y,Scene::DeltaTime());

		movingToPos.x -= 25 * Scene::DeltaTime();

		if (Math::Abs(movingToPos.x - position.x) < 5)
			movingTime = 0.0;



		collider.setPos(position);
		return;
	}

	position.x -= 100 * Scene::DeltaTime();
	position.y += ( position.x < 300 ? (position.y > Scene::Height()/2 ? -100 : 100)  * Scene::DeltaTime() : 0);
	collider.setPos(position);
	// if (hitbox.intersects(otherHitbox) && isAttacking) {
    // 	// Collision detected
	// }

	if (scroll) {
		updateScroll();
	}
}

void Enemy::updateScroll() {
	movingToPos.x -= 75 * Scene::DeltaTime();
}


void Enemy::draw() {
    if(!fallen)
		texture.scaled(0.2).drawAt(position);
	
}

void Enemy::MoveTo(Vec2 pos){
	position = pos;
	movingTime = 0;
}

void Enemy::PushTo(Vec2 pos, double time){
	
	double scaleX,scaleY,scaleFactor = 0;
	if(position.distanceFrom(pos) > 200){
		scaleFactor = 200/(position.distanceFrom(pos));
		scaleX = position.x + (pos.x - position.x) * scaleFactor;
		scaleY = position.y + (pos.y - position.y) * scaleFactor;

		pos = Vec2{scaleX,scaleY};
	}

	movingToPos = pos;
	movingTime = time;

	
}
