# include "Win.h"

Win::Win(const InitData& init)
		: IScene{ init }
{
	titleButton = new Button(Rect{ Scene::Width()/2 -150, Scene::Height()/2, 300, 100 }, FontAsset(U"TitleFont"), U"TITLE");
}

Win::~Win()
{ 
	titleButton = nullptr;
}

// Update function
void Win::update()
{
	// On left click
	titleButton->update();

	if (titleButton->clicked())
	{
		// Transition to game scene
		changeScene(U"Title", 1.5s);
	}
}

// Draw function
void Win::draw() const 
{
	Scene::SetBackground(ColorF{ 0.2, 0.2, 0.2 });

	// Add japanese text
	FontAsset(U"TitleFont")(String(U"GAME CLEAR")).drawAt(120, Vec2{ Scene::Size().x/2, Scene::Size().y/8 }, ColorF{ 0.3, 0.6, 0.3 });

	titleButton->draw();
	
}

void Win::drawFadeIn(double t) const
{
	draw();
	Circle{ Scene::Size().x/2, Scene::Size().y/2, Scene::Size().x }
		.drawFrame(((1 - t) * Scene::Size().x), 0, ColorF{ 0.2, 0.3, 0.4 });

	
	
}

void Win::drawFadeOut(double t) const
{
	draw();
	Circle{ Scene::Size().x/2, Scene::Size().y/2, Scene::Size().x }
		.drawFrame((t *  Scene::Size().x), 0, ColorF{ 0.2, 0.3, 0.4 });
}