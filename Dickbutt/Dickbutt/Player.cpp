#include "Player.h"


Player::Player(void)
{
	SetSpriteID(SpriteLibrary::PLAYER);
	SetPosition(sf::Vector2f(60.f,60.0f));
}


Player::~Player(void)
{
}

void Player::Update(void)
{
	if(Input::IsDown(sf::Keyboard::D))
	{
		SetVelocity(sf::Vector2f(2.0f,0.0f));
	}
	else if(Input::IsDown(sf::Keyboard::A))
	{
		SetVelocity(sf::Vector2f(-2.0f,0.0f));
	}

	this->Move();
	SetVelocity(sf::Vector2f(0.0f,0.0f));
}

