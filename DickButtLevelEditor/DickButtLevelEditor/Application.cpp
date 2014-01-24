#include "Application.h"


Application::Application(void)
{
	window = new sf::RenderWindow(sf::VideoMode(800, 600), "Team Sneaky Juice Level Editor");

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
    sf::Event event;
    while (window->pollEvent(event))
    {
		switch(event.type)
		{
		case sf::Event::Closed:
			gameEnded = true;
			break;
		}
    }

}

void Application::Draw()
{
    window->clear(sf::Color(255, 255, 255, 255));

    window->display();
}

Application::~Application(void)
{
	delete window;
}
