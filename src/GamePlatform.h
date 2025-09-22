#pragma once
#include <Siv3D.hpp>
#include "Entity.h"

class GamePlatform : public Entity {
public:
    GamePlatform(const Vec2& pos, const Texture& tex, const Size& si);

    void update(bool scroll) override;
    void draw() override;

    RectF getHitbox() const override;
};