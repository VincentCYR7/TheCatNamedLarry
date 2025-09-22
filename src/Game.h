#pragma once

# include <Siv3D.hpp>
# include "Entity.h"
# include "Player.h"
# include "GamePlatform.h"
# include "CollisionManager.h"


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
	const Texture larryTexture{U"Assets/larry.png"};
	const Texture platformTex{ U"Assets/platform.png" };
	const Vec2 test{400,300};
	std::vector<std::unique_ptr<Entity>> entities;
	std::vector<GamePlatform*> platforms;


	Player* player;
	CollisionManager* collisionManager;

};