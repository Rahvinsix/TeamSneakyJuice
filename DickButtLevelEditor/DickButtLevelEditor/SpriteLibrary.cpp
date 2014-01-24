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
	sprites[0] = new Sprite("Assets/Images/dirtCenter.png");
	sprites[1] = new Sprite("Assets/Images/dirtCenter_2.png");
}

sf::Sprite SpriteLibrary::GetSprite(int spriteId)
{
	return sprites[spriteId]->GetSprite();
}