#pragma once

#include <SFML/Graphics.hpp>


class Application
{
public:
	Application(void);
	~Application(void);
private:
	sf::RenderWindow* _window;

	bool _gameEnded;


	void Update();
	void Draw();
};

