// TrapManager.cpp
#include "TrapManager.h"


TrapManager::TrapManager() {
	// Initialize speed inside the constructor
	holeTexArr = {
		Texture{ U"Assets/hole.png"},
		Texture{ U"Assets/holeKing.png" },
		Texture{ U"Assets/HoleEnemy.png" },
		Texture{ U"Assets/hole.png"}
	};
	//Console << U"Called";
}


void TrapManager::SpawnTrap() {
	trapArr.emplace_back();
	//Console << U"trap spawned";
}


// update for the manager, spawn, update traps
// need arguments for player, king and soldiers
void TrapManager::Update(KingMoveManager& king, Player& player, std::vector<Enemy*>& enemyArr) {
	const double deltaTime = Scene::DeltaTime();

	UpdateTraps(deltaTime, king, player, enemyArr);

	if (isSpawning && king._timeFramePerSec > spawnStopTime) {
		if (spawnTimer < spawnTime) {
			spawnTimer += deltaTime;
		}
		else {
			SpawnTrap();
			spawnTimer = 0;
			spawnTime = Random(spawnTimeMin, spawnTimeMax);
		}
	}

	Draw();
}


void TrapManager::UpdateTraps(const double& deltaTime, KingMoveManager& king, Player& player,std::vector<Enemy*>& enemyArr) {

	for (int i = trapArr.size() - 1; i >= 0; --i) {
		Trap& trap = trapArr[i];
		if (isMoving) {
			if (!trap.activated) {
				// king check
				if (trap.collider.intersects(king.collider)) {
					king.fallen = true;	// boolean for the king falling
					TrapsPause(true);	// pause trap
					trap.state = 1;
					trap.activated = true;
				}
				// enemy check
				else if (enemyArr.size() != 0) {
					for (int j = enemyArr.size() - 1; j >= 0; --j) {
						Enemy enemy = *enemyArr[j];

						if (trap.collider.intersects(enemy.collider) && enemy.fallen) {
							trap.state = 2;
							trap.activated = true;
							//enemyArr.erase(enemyArr.begin() + j);
							continue;
						}
					}
				}
			}

			float speed = trapMoveSpeed * deltaTime;
			trap.TrapUpdate(speed);
			//Console << trap.currentPos.x;

			if (trap.currentPos.x < -50.0) {
				trapArr.remove_at(i);
				//Console << U"trap removed";
				continue;	// skip to next iteration
			}
		}
		// pull out king if fallen
		else if (trap.state == 1) {
			if (trap.collider.intersects(player.collider) && MouseL.down()) {
				//Console << U"collide";
				king.fallen = false;
				TrapsPause(false);	// unpause trap
				trap.state = 3;	// completely disable trap
			}
		}
	}
}


// true = pause spawning traps, false = resume
void TrapManager::TrapsPause(bool pause) {
	isMoving = isSpawning = !pause;

	for (int i = trapArr.size() - 1; i >= 0; --i) {
		if (trapArr[i].state == 1)
			trapArr[i].state = 0;
	}
}




void TrapManager::Draw() {
	for (Trap& trap : trapArr) {

		trap.TrapDraw(holeTexArr); // Pass the textures here
	}
}

