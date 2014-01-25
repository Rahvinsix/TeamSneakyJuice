#pragma once

#include "GlobalHeader.h"
#include "SpriteLibrary.h"


class GameObject
{
public:
	GameObject(void);
	~GameObject(void);

	int GetSpriteID(void);
	sf::Vector2f GetVelocity(void);

	static int CheckCollideWithVelocity(GameObject*, GameObject*);
	static bool CheckCollide(GameObject*,GameObject*);

	GameObject* SetPosition(sf::Vector2f);
	GameObject* SetSpriteID(int);
	GameObject* SetVelocity(sf::Vector2f);
	
	GameObject* Accelerate(sf::Vector2f);
	void Move(void);
	void MoveBy(sf::Vector2f);
	void Draw(sf::RenderWindow*);

	enum
	{
		V_COLLISION,
		H_COLLISION,
		NO_COLLISION
	};

private:
	
	int spriteID;
	sf::Vector2f _velocity;
	sf::Vector2f _position;
};

