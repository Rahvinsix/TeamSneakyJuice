#include "SpriteLibrary.h"

Sprite** SpriteLibrary::libraryFile = new Sprite*[2];



SpriteLibrary::SpriteLibrary(void)
{
	
}

SpriteLibrary::~SpriteLibrary(void)
{
}

void SpriteLibrary::Initialise(void)
{
	libraryFile[GROUND] = new Sprite("Assets/Images/dirtCenter.png");
	libraryFile[AIR] = new Sprite("Assets/Images/bg.png");
}

sf::Sprite SpriteLibrary::GetSprite(int SpriteID)
{
	return libraryFile[SpriteID]->GetSprite();
}