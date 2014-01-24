#include "Application.h"


Application::Application(void)
{
	_window = new sf::RenderWindow(sf::VideoMode(800, 600), "Team Sneaky Juice");

	_gameEnded = false;

    while (_window->isOpen())
    {
		Update();
		Draw();

		if(_gameEnded)
			_window->close();
    }
}

void Application::Update()
{
    sf::Event event;
    while (_window->pollEvent(event))
    {
		switch(event.type)
		{
		case sf::Event::Closed:
			_gameEnded;
			break;
		case sf::Event::KeyPressed:
			break;
		case sf::Event::KeyReleased:
			break;
		}
    }
}

void Application::Draw()
{
    _window->clear(sf::Color(255, 255, 255, 255));
    _window->display();
}

Application::~Application(void)
{
	delete _window;
}
