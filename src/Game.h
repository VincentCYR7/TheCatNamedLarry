#pragma once

# include <Siv3D.hpp>
# include "Entity.h"
# include "King.h"
# include "Player.h"
# include "TrapManager.h"
# include "Enemy.h"


class Game : public SceneManager<String>::Scene
{
public:

	Game(const InitData& init);
	~Game();

	void update() override;

	void draw() const override;

	void drawFadeIn(double t) const override;

	void drawFadeOut(double t) const override;

	bool scrolling;

private:

	Texture m_emoji;

	Stopwatch m_stopwatch;
	const Texture kingTexture{U"Assets/king.png" };
	const Texture queenTexture{U"Assets/queen.png" };
	const Texture knightTexture{U"Assets/knight.png"};
	const Texture grassTexture{U"Assets/grass.png"};
	const Texture enemyTexture{U"Assets/enemy.png"};
	const Vec2 test{400,300};
	std::vector<std::unique_ptr<Entity>> entities;

	KingMoveManager* king;

	Player* player;
	
	Entity* queen;

	TrapManager trapManager;

	std::vector<Enemy*> enemyArray;

	std::vector<Entity*> grassArray;
};