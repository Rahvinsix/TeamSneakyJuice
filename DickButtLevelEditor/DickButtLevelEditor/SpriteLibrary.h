#pragma once

#include "Sprite.h"

class SpriteLibrary
{
public:
	SpriteLibrary(void);
	~SpriteLibrary(void);

	static void Initialise();

	static sf::Sprite GetSprite(int);

private:
	static Sprite** sprites;
};

