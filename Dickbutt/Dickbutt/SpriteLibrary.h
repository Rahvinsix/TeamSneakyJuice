#pragma once
#include "Sprite.h"

#define TOTAL_SPRITES 4


class SpriteLibrary
{
public:
	SpriteLibrary(void);
	~SpriteLibrary(void);

	static void Initialise(void);
	static sf::Sprite GetSprite(int);
	
	
	enum
	{
		GROUND,
		AIR,
		SPIN_BLOCK,
		SPIN_OBJECT,
	};

	static Sprite** _libraryFile;
};

