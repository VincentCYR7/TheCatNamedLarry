#pragma once
#include "Entity.h"

class Player : public Entity {
public:
	bool scrolling = true;
    Player(const s3d::Vec2& pos, const s3d::Texture& tex, const Size& si);
	~Player() {};

    void update(bool scroll) override;
    void draw() override;
	
	Rect hitbox;
	bool isAttacking = false;

private:

    double speed = 280.0;

	double attackCoolDown = 0.1;

    s3d::Vec2 targetPos;        // destination
    bool facingLeft = false;
    double atkAnimInterval = 0;
	

	


};
