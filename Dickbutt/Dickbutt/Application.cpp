#include "Application.h"


Application::Application(void)
{
	window = new sf::RenderWindow(sf::VideoMode(800, 600), "Team Sneaky Juice");

	SpriteLibrary::Initialise();
	Input::Initialise();
	level = new LevelClass();
	player = new Player();
	gameEnded = false;
	
    while (window->isOpen())
    {
		Update();
		Draw();

		if(gameEnded)
			window->close();
    }
}

void Application::Update()
{
	//Update player input
	Input::Update();
	player->Update();
	
    sf::Event event;
    while (window->pollEvent(event))
    {
		switch(event.type)
		{
		case sf::Event::Closed:
			gameEnded = true;
			break;
		case sf::Event::KeyPressed:
			Input::KeyPressed(event.key.code);
			break;
		case sf::Event::KeyReleased:
			Input::KeyReleased(event.key.code);
			break;
		}
    }

}

void Application::Draw()
{
    window->clear(sf::Color(255, 255, 255, 255));
	level->Draw(window);
	player->Draw(window);
    window->display();
}

Application::~Application(void)
{
	delete window;
	delete level;
}
