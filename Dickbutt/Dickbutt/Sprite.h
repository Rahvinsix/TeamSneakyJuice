#pragma once

#include <SFML/Graphics.hpp>


class Sprite
{
public:
	Sprite(char*);
	~Sprite(void);

	void Draw(sf::RenderWindow*);

private:
	sf::Texture* tex;

	bool texLoaded;
};