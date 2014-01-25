#pragma once
#include "Sprite.h"
class SpriteLibrary
{
public:
	SpriteLibrary(void);
	~SpriteLibrary(void);
	static void Initialise(void);
	enum{GROUND,AIR,PLAYER};
	static Sprite** libraryFile;
	static sf::Sprite GetSprite(int);
};

