#include "Application.h"


Application::Application(void)
{
	window = new sf::RenderWindow(sf::VideoMode(800, 600), "Team Sneaky Juice");

	gameEnded = false;
	
	testSprite = new Sprite("Assets/Images/dirtCenter.png");

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

	testSprite->Draw(window);

    window->display();
}

Application::~Application(void)
{
	delete window;
}
