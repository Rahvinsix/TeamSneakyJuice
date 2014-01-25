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
	sf::Vector2f GetPosition(void);
	sf::Vector2f GetCentre(void);

	static int CheckCollideWithVelocity(GameObject*, GameObject*);
	static bool CheckVCollideWithVelocity(GameObject*, GameObject*);
	static bool CheckHCollideWithVelocity(GameObject*, GameObject*);
	static bool CheckCollide(GameObject*,GameObject*);

	GameObject* SetPosition(sf::Vector2f);
	GameObject* SetSpriteID(int);
	GameObject* SetVelocity(sf::Vector2f);
	GameObject* SetRotation(float);
	
	GameObject* Accelerate(sf::Vector2f);
	void Move(void);
	void MoveBy(sf::Vector2f);
	void Draw(sf::RenderWindow*);
	void DeltaVy(float vy);

	enum
	{
		V_COLLISION,
		H_COLLISION,
		NO_COLLISION
	};
	
	bool seen;

private:
	
	int spriteID;
	sf::Vector2f _velocity;
	sf::Vector2f _position;
	float _rotation;
};

