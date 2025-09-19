# include "Title.h"



Title::Title(const InitData& init)
		: IScene{ init }
{
	playButton = new Button(Rect{ Scene::Width()/2 -150, Scene::Height()/4, 300, 100 }, FontAsset(U"TitleFont"), U"PLAY");
	quitButton = new Button(Rect{ Scene::Width()/2 -150, Scene::Height()/2, 300, 100 }, FontAsset(U"TitleFont"), U"QUIT");
}

Title::~Title()
{
	playButton = nullptr;
	quitButton = nullptr;
}

// Update function
void Title::update()
{
	// On left click
	playButton->update();
	quitButton->update();

	if (playButton->clicked())
	{
		// Transition to game scene
		changeScene(U"Game", 1.5s);
	}

	if (quitButton->clicked())
	{
		// Transition to game scene
		System::Exit();
	}
}

// Draw function
void Title::draw() const 
{
	Scene::SetBackground(ColorF{ 0.3, 0.3, 0.3 });

	// Add japanese text
	FontAsset(U"TitleFont")(String(U"HEISHI WA TSURAI YO")).drawAt(60, Vec2{ Scene::Size().x/2, Scene::Size().y/8 }, ColorF{ 0.9, 0.9, 0.1 });



	playButton->draw();
	quitButton->draw();
	
}

void Title::drawFadeIn(double t) const
{
	draw();
	Circle{ Scene::Size().x/2, Scene::Size().y/2, Scene::Size().x }
		.drawFrame(((1 - t) * Scene::Size().x), 0, ColorF{ 0.2, 0.3, 0.4 });

	
	
}

void Title::drawFadeOut(double t) const
{
	draw();
	Circle{ Scene::Size().x/2, Scene::Size().y/2, Scene::Size().x }
		.drawFrame((t *  Scene::Size().x), 0, ColorF{ 0.2, 0.3, 0.4 });
}