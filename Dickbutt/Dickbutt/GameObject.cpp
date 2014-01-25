#include "GameObject.h"


GameObject::GameObject(void)
{
	
}


GameObject::~GameObject(void)
{
	
}

GameObject* GameObject::SetSpriteID(int spriteID)
{
	this->spriteID = spriteID;
	
	return this;
}

GameObject* GameObject::SetPosition(sf::Vector2f pos)
{
	position = pos;

	return this;
}

void GameObject::Draw(sf::RenderWindow* window)
{
	sf::Sprite renderSprite = SpriteLibrary::GetSprite(spriteID);

	renderSprite.setPosition(position);

	window->draw(renderSprite);
}

GameObject* GameObject::SetVelocity(sf::Vector2f velocity)
{
	_velocity = velocity;

	return this;
}

GameObject* GameObject::Accelerate(sf::Vector2f acceleration)
{
	_velocity += acceleration;

	return this;
}

void GameObject::Move(void)
{
	position += _velocity;
}