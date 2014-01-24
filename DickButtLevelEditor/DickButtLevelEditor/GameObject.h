#pragma once

#include "GlobalHeader.h"
#include "sprite.h"


class GameObject
{
public:
	GameObject(void);
	~GameObject(void);
	
	GameObject* SetSprite(char*);
	GameObject* SetPosition(sf::Vector2f);

	void Draw(sf::RenderWindow*);

private:
	bool hasSprite;
	Sprite* sprite;

	sf::Vector2f position;
};

