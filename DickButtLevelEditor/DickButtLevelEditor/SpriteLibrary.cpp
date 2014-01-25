#include "SpriteLibrary.h"

Sprite** SpriteLibrary::sprites = new Sprite*[TOTAL_SPRITES];


SpriteLibrary::SpriteLibrary(void)
{
}


SpriteLibrary::~SpriteLibrary(void)
{
}

void SpriteLibrary::Initialise()
{
	sprites[0] = new Sprite("Assets/Images/bg.png");
	sprites[1] = new Sprite("Assets/Images/dirtCenter.png");
	sprites[2] = new Sprite("Assets/Images/SpinCentre.png");
}

sf::Sprite SpriteLibrary::GetSprite(int spriteId)
{
	return sprites[spriteId]->GetSprite();
}