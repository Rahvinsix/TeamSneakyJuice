#pragma once

#include "Sprite.h"

#define TOTAL_SPRITES 2


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

