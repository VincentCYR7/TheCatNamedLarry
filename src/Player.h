#pragma once
#include "Entity.h"

class Player : public Entity {
public:
	bool scrolling = true;
    Player(const s3d::Vec2& pos, const s3d::Texture& tex, const Size& si);
	~Player() {};

    void update() override;
    void draw() override;
	
	Rect hitbox;
	bool isAttacking = false;
    RectF getHitbox() const override;
    RectF prevHitbox;


private:

    double speed = 280.0;
    double jumpStrength = -800.0;
	double attackCoolDown = 0.1;


    s3d::Vec2 targetPos;        // destination
    bool facingLeft = false;

    
	const Texture larryRun1Texture{U"Assets/Larry/LarryRun1.png"};
    const Texture larryRun2Texture{U"Assets/Larry/LarryRun2.png"};
    const Texture larryRun3Texture{U"Assets/Larry/LarryRun3.png"};
    const Texture larryIdle1Texture{U"Assets/Larry/LarryIdle1.png"};
    const Texture larryIdle2Texture{U"Assets/Larry/LarryIdle2.png"};
    const Texture larryIdle3Texture{U"Assets/Larry/LarryIdle3.png"};
    const Texture larryIdle4Texture{U"Assets/Larry/LarryIdle4.png"};
    const Texture larryIdle5Texture{U"Assets/Larry/LarryIdle5.png"};
    const Texture larryIdle6Texture{U"Assets/Larry/LarryIdle6.png"};
    const Texture larryIdle7Texture{U"Assets/Larry/LarryIdle7.png"};

	bool isMoving = false;
	int curSpriteMoving = 0;
	int curSpriteIdle = 0;
	double animInterval = 0.3;
	float animTimer = 0;
    //const Texture larryIdle8Texture{U"Assets/Larry/LarryIdle8.png"};
	
};
