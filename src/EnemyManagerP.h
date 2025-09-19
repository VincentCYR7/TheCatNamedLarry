#pragma once
#include <Siv3D.hpp>

class EnemyManagerP{
public:
	struct EnemyP{
		Circle collider{ 600, 300, 40 };
	};

	Array<EnemyP> enemyArr;

	EnemyManagerP(){
		enemyArr.emplace_back();
	}

	void Draw(){
		for (EnemyP& enemy : enemyArr) {
			enemy.collider.draw();
		}
	}
};