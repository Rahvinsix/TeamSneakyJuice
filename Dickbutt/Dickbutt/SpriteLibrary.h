#pragma once
#include "Sprite.h"

#define TOTAL_SPRITES 5


class SpriteLibrary
{
public:
	SpriteLibrary(void);
	~SpriteLibrary(void);

	static void Initialise(void);

	static sf::Sprite GetSprite(int);

	
	enum
	{
		AIR,
		GROUND,
		SPIN_BLOCK,
		SPIN_OBJECT,
		SPIN_CHAIN,
		PLAYER
	};

	static Sprite** _libraryFile;
};

