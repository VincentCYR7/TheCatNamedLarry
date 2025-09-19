// TrapManager.hpp
#pragma once
#include <Siv3D.hpp>
#include "KingMoveManager.h"
#include "Enemy.h"
#include "Player.h"

class TrapManager {
private:
	struct Trap
	{
		Vec2 spawnPos{ 1300, 400 };
		Vec2 currentPos{ 900, 0 };
		Circle collider{ 900, 0, 40 };
		float trapScale = 0.2f;

		int state = 0;	//0 - normal, 1 - king fell in, 2 - enemy fell in, 3 - disabled
		bool activated = false;

		Trap() {
			currentPos = spawnPos;
			collider.setPos(spawnPos);

		}

		void TrapUpdate(float& deltaSpeed) {
			currentPos.x -= deltaSpeed;
			collider.setPos(currentPos);
		}

		void TrapCollide(int type) {

		}

		void TrapDraw(const Array<Texture>& textures) {
			textures[state].scaled(trapScale).drawAt(currentPos);
			//collider.draw();
		}
	};

	const float spawnTimeMin = 3.0f;
	const float spawnTimeMax = 8.0f;
	float spawnTime = 2.0f;
	float spawnTimer = 0.0f;

	float spawnStopTime = 35.0f;

	void SpawnTrap();	// add a trap to array
	void UpdateTraps(const double& deltaTime, KingMoveManager& king, Player& player, std::vector<Enemy*>& enemyArr);	// update individual traps

public:
	Array<Texture> holeTexArr;
	Array<Trap> trapArr;
	bool isSpawning = true;
	bool isMoving = true;

	float trapMoveSpeed = 75.0f;

	TrapManager();	// constructor
	void Update(KingMoveManager& king, Player& player, std::vector<Enemy*>& enemyArr);	// update for the manager, spawn, update traps
	void Draw();
	void TrapsPause(bool pause); // true = pause spawning traps, false = resume
};
