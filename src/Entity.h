#pragma once
#include <Siv3D.hpp>

class Entity {
protected:
    s3d::Vec2 position;
    s3d::Texture texture;

public:
	Circle collider{ 400, 300, 70 };
    Entity(const s3d::Vec2& pos, const s3d::Texture& tex);
    virtual ~Entity();

    virtual void update(bool scroll);   // can be overridden by Player
    virtual void draw();     // can be overridden by Player
	virtual void updateScroll();
    double getY() const;

	void SetPos(Vec2 pos);

	Vec2 GetPos() const;
};
