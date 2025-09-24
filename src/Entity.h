#pragma once
#include <Siv3D.hpp>

class Entity {
protected:
    s3d::Vec2 position;
    s3d::Texture texture;
	Size size;
	
	
	const double gravity = 9.8; 

public:
	Circle collider{ 400, 300, 70 };
    Entity(const s3d::Vec2& pos, const s3d::Texture& tex, const Size& si);
    virtual ~Entity();

    virtual void update(); 
    virtual void draw(); 
	virtual void updateScroll();

    double getY() const;

	void SetPos(Vec2 pos);

	Vec2 GetPos() const;

	virtual RectF getHitbox() const = 0;

	bool isGrounded = false;

	Vec2 velocity = Vec2{ 0, 0 };

	RectF prevHitbox;
	float ignoreGroundUntil = 0.0;
};
