#pragma once
#include "gameobject.h"
#include "Input.h"
class Player :
	public GameObject
{
public:
	Player(void);
	~Player(void);
	void Update(float timeElapsed);
	bool _playerFacing;
	void DrawPlayer(sf::RenderWindow* window);
	bool _onLadder;
	void VerticalCollision();
	void Death(void);
	void setSpawn(sf::Vector2f vector);
	void addHeart(void);
	int checkHearts(void);
private:
	float gravity;
	float jumpFrames;
	sf::Vector2f _playerSpawn;
	bool onGround;
	int hearts;

	int _currentFrame;
	bool _moving;
	float _animationStep;
	
};

