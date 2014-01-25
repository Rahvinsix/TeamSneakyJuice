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
		HEART_END,
		SPIKE_END,
		SPIN_CHAIN
	};

	static Sprite** _libraryFile;
};

