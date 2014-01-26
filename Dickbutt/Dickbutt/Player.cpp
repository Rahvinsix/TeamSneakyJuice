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
	hearts = 0;

	_moving = false;
	_animationStep = 0.0f;
	_currentFrame = 0;
}


Player::~Player(void)
{
}

void Player::Update(float timeElapsed)
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
	if(Input::IsDown(sf::Keyboard::Space) && jumpFrames == 0 && (onGround || _onLadder))
	{
		jumpFrames = 0.6f;
		onGround = false;
	}
	if(Input::IsUp(sf::Keyboard::Space))
	{
		jumpFrames = 0.0f;
	}

	if(jumpFrames > 0)
	{
		jumpFrames-=timeElapsed;
		SetVelocity(sf::Vector2f(GetVelocity().x, -5.0f));//DeltaVy(-5.0f * 30 * timeElapsed);
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
	Move(timeElapsed);
	
	_onLadder = false;
	onGround = false;

	bool oldMoving = _moving;
	_moving = GetVelocity().x != 0;
	if(_moving && !oldMoving)
	{
		_currentFrame = 0;
		_animationStep = 0;
	}
	else if(_moving && oldMoving)
	{
		_animationStep += timeElapsed;
		if(_animationStep >= 0.25)
		{
			_animationStep = 0;
			// Alternates between 0 and 1
			_currentFrame = 1 - _currentFrame;
		}
	}

	if(!_moving)
		_currentFrame = 0;
}

void Player::VerticalCollision()
{
	if(GetVelocity().y >= 0)
		onGround = true;
}

void Player::DrawPlayer(sf::RenderWindow* window)
{
	sf::Sprite playerSprite;
	playerSprite = SpriteLibrary::GetSprite((_currentFrame == 0 ? SpriteLibrary::PLAYER : SpriteLibrary::PLAYER_1));
	playerSprite.setPosition(GetPosition() + sf::Vector2f(playerSprite.getLocalBounds().width/2,(playerSprite.getLocalBounds().height/2)));
	playerSprite.setOrigin(GetCentre()-GetPosition());
	if(!_playerFacing)
		playerSprite.setScale(-1,1);
	
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

void Player::addHeart(void)
{
	hearts++;
}
int Player::checkHearts(void)
{

	return hearts;

}