#pragma once
#include <Siv3D.hpp>

class KingP{
public:
	Circle collider{ 400, 300, 40 };
	bool fallen = false;

	void Draw(){
		if(!fallen)
			collider.draw();
	}
};