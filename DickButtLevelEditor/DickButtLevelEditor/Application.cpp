#include "Application.h"


Application::Application(void)
{
	window = new sf::RenderWindow(sf::VideoMode(800, 600), "Team Sneaky Juice Level Editor");

	gameEnded = false;
	mouseDown = false;
	
	SpriteLibrary::Initialise();
	
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
		case sf::Event::MouseButtonPressed:
			mouseDown = true;
			break;
		case sf::Event::MouseButtonReleased:
			mouseDown = false;
			break;
		case sf::Event::MouseMoved:
			if(mouseDown)
				mapGrid.Click(event.mouseMove);
		}
    }

}

void Application::Draw()
{
    window->clear(sf::Color(255, 255, 255, 255));

	mapGrid.Draw(window);

    window->display();
}

Application::~Application(void)
{
	delete window;
}
