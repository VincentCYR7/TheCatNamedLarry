#pragma once
#include <Siv3D.hpp>

class PlayerP{
public:
	Circle collider{ 400, 300, 30 };

	void Update() {
		collider.setPos(Cursor::Pos());
		Draw();
	}

	void Draw() {
		collider.draw();
	}
};