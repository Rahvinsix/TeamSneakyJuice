#pragma once

#include "GlobalHeader.h"


class Sprite
{
public:
	Sprite();
	Sprite(char*);
	~Sprite(void);

	sf::Sprite GetSprite();
	sf::Texture GetTexture();

private:
	sf::Texture* tex;

	bool texLoaded;
};