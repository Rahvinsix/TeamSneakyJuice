#pragma once

#include "GlobalHeader.h"
#include "SpriteLibrary.h"


class GameObject
{
public:
	GameObject(void);
	~GameObject(void);

	GameObject* SetPosition(sf::Vector2f);
	GameObject* SetSpriteID(int);
	GameObject* SetVelocity(sf::Vector2f);
	GameObject* Accelerate(sf::Vector2f);

	void Move(void);
	void Draw(sf::RenderWindow*);

private:
	
	int spriteID;
	sf::Vector2f _velocity;
	sf::Vector2f position;
};

