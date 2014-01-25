#include "Player.h"


Player::Player(void)
{
	
	_playerSpawn.x = 0.0f;
	_playerSpawn.y = 0.0f;
	gravity = 2.0f;
	jumpFrames = 0;
	onGround = false;
	_playerFacing = true;
	_onLadder = false;
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
	if(Input::IsDown(sf::Keyboard::Space) && jumpFrames == 0 && onGround && !_onLadder)
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

	if(_playerFacing)
	{
	
		
	
	}

	if(!_onLadder)
	{
		DeltaVy(gravity);
	}
	else
	{
		if(Input::IsDown(sf::Keyboard::W))
		{
			SetVelocity(sf::Vector2f(0.0f,-2.0f));
			
		}
		else if(Input::IsDown(sf::Keyboard::S))
		{
			SetVelocity(sf::Vector2f(0.0f,2.0f));
			
		}
	}
	Move();
	
}

void Player::VerticalCollision()
{
	if(GetVelocity().y >= 0)
		onGround = true;
}

void Player::DrawPlayer(sf::RenderWindow* window)
{
	sf::Sprite playerSprite;
	playerSprite = SpriteLibrary::GetSprite(SpriteLibrary::PLAYER);
	playerSprite.setPosition(GetPosition() + sf::Vector2f(playerSprite.getLocalBounds().width/2,(playerSprite.getLocalBounds().height/2)));
	playerSprite.setOrigin(GetCentre()-GetPosition());
	if(!_playerFacing)
	{
		playerSprite.setScale(-1,1);
	}
	
	window->draw(playerSprite);
}

void Player::Death(void)
{

	SetPosition(sf::Vector2f(_playerSpawn.x,_playerSpawn.y));

}

void Player::setSpawn(sf::Vector2f vector)
{

	_playerSpawn = vector;

}