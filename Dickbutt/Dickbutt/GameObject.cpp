#include "GameObject.h"


GameObject::GameObject(void)
{
	hasSprite = false;
}


GameObject::~GameObject(void)
{
	if(hasSprite)
		delete sprite;
}

GameObject* GameObject::SetSprite(char* fileName)
{
	sprite = new Sprite(fileName);
	hasSprite = true;

	return this;
}

GameObject* GameObject::SetPosition(sf::Vector2f pos)
{
	position = pos;

	return this;
}

void GameObject::Draw(sf::RenderWindow* window)
{
	sf::Sprite renderSprite = sprite->GetSprite();

	renderSprite.setPosition(position);

	window->draw(renderSprite);
}