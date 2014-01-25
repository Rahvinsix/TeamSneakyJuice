#include "Player.h"


Player::Player(void)
{
	SetSpriteID(SpriteLibrary::PLAYER);
	SetPosition(sf::Vector2f(60.f,60.0f));
	gravity = 2.0f;
	jumpFrames = 0;
	onGround = false;
	_playerFacing = true;
}


Player::~Player(void)
{
}

void Player::Update(void)
{
	
	SetVelocity(sf::Vector2f(0.0f,0.0f));

	if(Input::IsDown(sf::Keyboard::D))
	{
		SetVelocity(sf::Vector2f(2.0f,0.0f));
		_playerFacing = true;
	}
	else if(Input::IsDown(sf::Keyboard::A))
	{
		SetVelocity(sf::Vector2f(-2.0f,0.0f));
		_playerFacing = false;
	}
	if(Input::IsDown(sf::Keyboard::Space) && jumpFrames == 0 && onGround)
	{
		jumpFrames = 40;
		onGround = false;
	}
	if(Input::IsUp(sf::Keyboard::Space))
	{
		jumpFrames = 0;
	}

	if(jumpFrames > 0)
	{
		jumpFrames--;
		DeltaVy(-5.0f);
	}

	DeltaVy(gravity);
	
	Move();
	
}

void Player::VerticalCollision()
{
	if(GetVelocity().y >= 0)
		onGround = true;
}