#include "SpriteLibrary.h"

Sprite** SpriteLibrary::_libraryFile = new Sprite*[TOTAL_SPRITES];



SpriteLibrary::SpriteLibrary(void)
{
	
}

SpriteLibrary::~SpriteLibrary(void)
{
}

void SpriteLibrary::Initialise(void)
{
	_libraryFile[GROUND] = new Sprite("Assets/Images/dirtCenter.png");
	_libraryFile[AIR] = new Sprite("Assets/Images/bg.png");

	_libraryFile[SPIN_BLOCK] = new Sprite("Assets/Images/SpinCentre.png");
	_libraryFile[SPIN_OBJECT] = new Sprite("Assets/Images/SpinEnd.png");
	_libraryFile[SPIN_CHAIN] = new Sprite("Assets/Images/SpinChain.png");
}

sf::Sprite SpriteLibrary::GetSprite(int spriteID)
{
	return _libraryFile[spriteID]->GetSprite();
}
