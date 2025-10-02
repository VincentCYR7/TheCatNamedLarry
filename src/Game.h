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

	void updateCamera();

private:

	Texture m_emoji;

	Stopwatch m_stopwatch;
	const Texture larryTexture{U"Assets/Larry/Larry0.png"};
	const Texture platformTex{ U"Assets/rooftop.png" };
	const Texture nightSky{U"Assets/nightSky.png"};
	const Texture buildings{U"Assets/buildings.png"};
	const Vec2 test{400,300};
	std::vector<std::unique_ptr<Entity>> entities;
	std::vector<GamePlatform*> platforms;

	Player* player;
	CollisionManager* collisionManager;

	double accumulator = 0.0;
	const double h = 1.0/120.0;

	s3d::Camera2D m_camera{ Vec2{0, 0}, 1.0, s3d::Camera2DParameters::NoControl() };
	//s3d::RectF m_deadZone{ -200, -150, 400, 300 };
	struct DeadZone {
		double leftX = -250;
		double rightX = 50;
		double topY = -20;
		double bottomY = 50;
	} m_deadZone;

};