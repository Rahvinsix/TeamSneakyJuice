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
	sprites[1] = new Sprite("Assets/Images/floor.png");
	sprites[2] = new Sprite("Assets/Images/heart.png");
	sprites[3] = new Sprite("Assets/Images/spikeyball.png");
	sprites[4] = new Sprite("Assets/Images/spikes.png");
	sprites[5] = new Sprite("Assets/Images/spikes_vert.png");
	sprites[6] = new Sprite("Assets/Images/levelend.png");
	sprites[7] = new Sprite("Assets/Images/hit_from_above_guy.png");
	sprites[8] = new Sprite("Assets/Images/hit_from_side_guy.png");
	sprites[9] = new Sprite("Assets/Images/lava1.png");
	sprites[10] = new Sprite("Assets/Images/lava2.png");
	sprites[11] = new Sprite("Assets/Images/lava3.png");
	sprites[12] = new Sprite("Assets/Images/lava4.png");
	sprites[13] = new Sprite("Assets/Images/lava5.png");
	sprites[14] = new Sprite("Assets/Images/lava6.png");
	sprites[15] = new Sprite("Assets/Images/player.png");
	sprites[16] = new Sprite("Assets/Images/heart_and_ball.png");
	sprites[17] = new Sprite("Assets/Images/spikeyball2.png");
	sprites[18] = new Sprite("Assets/Images/ladder.png");
}

sf::Sprite SpriteLibrary::GetSprite(int spriteId)
{
	return sprites[spriteId]->GetSprite();
}