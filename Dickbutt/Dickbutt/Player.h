#pragma once
#include "gameobject.h"
#include "Input.h"
class Player :
	public GameObject
{
public:
	Player(void);
	~Player(void);
	void Update(void);
	bool _playerFacing;

	void VerticalCollision();

private:
	float gravity;
	int jumpFrames;

	bool onGround;
	
};

