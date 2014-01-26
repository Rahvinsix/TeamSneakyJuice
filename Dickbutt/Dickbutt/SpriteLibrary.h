#pragma once
#include "Sprite.h"

#define TOTAL_SPRITES 27


class SpriteLibrary
{
public:
	SpriteLibrary(void);
	~SpriteLibrary(void);

	static void Initialise(void);
	static void Delete(void);

	static sf::Sprite GetSprite(int);
	static sf::Texture GetTexture(int);

	
	enum
	{
		AIR,
		GROUND,
		HEART,
		SPIKE_BALL,
		H_SPIKES,
		V_SPIKES,
		DOOR,
		HIT_FROM_ABOVE_GUY,
		HIT_FROM_SIDE_GUY,
		LAVA_1,
		LAVA_2,
		LAVA_3,
		LAVA_4,
		LAVA_5,
		LAVA_6,
		PLAYER,
		HEART_AND_BALL,
		DOUBLE_BALL,
		LADDER,
		H_SPIKES_FLIPPED,
		FLOOR_LB,
		FLOOR_RB,
		FLOOR_LC,
		FLOOR_RC,

		HEART_END,
		SPIKE_END,
		SPIN_CHAIN,
		HEART0,
		HEART1,
		HEART2,
		HEART3,
		HEART4,
		HEART5,
		HEART6,
		DOOR_OPEN
	};

	static Sprite* _libraryFile[TOTAL_SPRITES];
};

