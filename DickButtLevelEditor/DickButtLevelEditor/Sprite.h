#pragma once

#include "GlobalHeader.h"


class Sprite
{
public:
	Sprite(char*);
	~Sprite(void);

	sf::Sprite GetSprite();

private:
	sf::Texture* tex;

	bool texLoaded;
};