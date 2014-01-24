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

	void Draw(sf::RenderWindow*);

private:
	
	int spriteID;

	sf::Vector2f position;
};

