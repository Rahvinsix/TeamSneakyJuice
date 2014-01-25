#include "SpriteLibrary.h"

Sprite** SpriteLibrary::_libraryFile = new Sprite*[];


SpriteLibrary::SpriteLibrary(void)
{
	
}

SpriteLibrary::~SpriteLibrary(void)
{
	delete _libraryFile;
}

void SpriteLibrary::Initialise(void)
{
	_libraryFile[AIR] = new Sprite("Assets/Images/bg.png");
	_libraryFile[GROUND] = new Sprite("Assets/Images/floor.png");
	_libraryFile[HEART] = new Sprite("Assets/Images/rotatebase.png");
	_libraryFile[SPIKE_BALL] = new Sprite("Assets/Images/rotatebase.png");
	_libraryFile[H_SPIKES] = new Sprite("Assets/Images/spikes.png");
	_libraryFile[V_SPIKES] = new Sprite("Assets/Images/spikes_vert.png");
	_libraryFile[DOOR] = new Sprite("Assets/Images/levelend.png");
	_libraryFile[HIT_FROM_ABOVE_GUY] = new Sprite("Assets/Images/hit_from_above_guy.png");
	_libraryFile[HIT_FROM_SIDE_GUY] = new Sprite("Assets/Images/hit_from_side_guy.png");
	_libraryFile[LAVA_1] = new Sprite("Assets/Images/lava1.png");
	_libraryFile[LAVA_2] = new Sprite("Assets/Images/lava2.png");
	_libraryFile[LAVA_3] = new Sprite("Assets/Images/lava3.png");
	_libraryFile[LAVA_4] = new Sprite("Assets/Images/lava4.png");
	_libraryFile[LAVA_5] = new Sprite("Assets/Images/lava5.png");
	_libraryFile[LAVA_6] = new Sprite("Assets/Images/lava6.png");
	_libraryFile[PLAYER] = new Sprite("Assets/Images/player.png");
	_libraryFile[HEART_AND_BALL] = new Sprite("Assets/Images/rotatebase.png");
	_libraryFile[DOUBLE_BALL] = new Sprite("Assets/Images/rotatebase.png");
	_libraryFile[LADDER] = new Sprite("Assets/Images/ladder.png");
	_libraryFile[H_SPIKES_FLIPPED] = new Sprite("Assets/Images/spikes_right.png");
	_libraryFile[HEART_END] = new Sprite("Assets/Images/heart.png");
	_libraryFile[SPIKE_END] = new Sprite("Assets/Images/spikeyball.png");
	_libraryFile[SPIN_CHAIN] = new Sprite("Assets/Images/SpinChain.png");
}

sf::Sprite SpriteLibrary::GetSprite(int spriteID)
{
	return _libraryFile[spriteID]->GetSprite();
}

sf::Texture SpriteLibrary::GetTexture(int spriteID)
{
	return _libraryFile[spriteID]->GetTexture();
}