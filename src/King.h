#pragma once
#include "Entity.h"

class King : public Entity {
public:
    King(const s3d::Vec2& pos, const s3d::Texture& tex);

    // override update
    void update(bool scroll) override;
};