#include "GameObject.h"


GameObject::GameObject(void)
{
	bool seen = false;

	_rotation = 0.0f;
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
	_position = pos;

	return this;
}

GameObject* GameObject::SetRotation(float rot)
{
	_rotation = rot;
	
	return this;
}

void GameObject::Draw(sf::RenderWindow* window)
{
	sf::Sprite mySprite = SpriteLibrary::GetSprite(spriteID);
	sf::Sprite playerSprite = SpriteLibrary::GetSprite(SpriteLibrary::PLAYER);

	mySprite.setPosition(_position);
	playerSprite.setPosition(_position);

	if(_rotation != 0)
	{
		mySprite.setOrigin(mySprite.getLocalBounds().width / 2, mySprite.getLocalBounds().height / 2);
		mySprite.setRotation(_rotation);
		mySprite.move(mySprite.getLocalBounds().width / 2, mySprite.getLocalBounds().height / 2);

		playerSprite.setOrigin(playerSprite.getLocalBounds().width / 2, playerSprite.getLocalBounds().height / 2);
		playerSprite.setRotation(_rotation);
		playerSprite.move(playerSprite.getLocalBounds().width / 2, playerSprite.getLocalBounds().height / 2);

		if((_playerSight > _position.x && !_playerDirec) || (_playerSight < _position.x && _playerDirec))
			window->draw(playerSprite);
		else
			window->draw(mySprite);
		return;
	}
	else
		if(!_playerDirec)
		{
			if(_playerSight - _position.x > 0 && _playerSight - _position.x < mySprite.getLocalBounds().width)
			{
				sf::FloatRect spriteBounds = mySprite.getLocalBounds();
				sf::IntRect newSprite(spriteBounds.left + (_playerSight - _position.x), spriteBounds.top, spriteBounds.width - (_playerSight - _position.x), spriteBounds.height);
				mySprite.setTextureRect(newSprite);
				mySprite.move(sf::Vector2f((_playerSight - _position.x), 0));
			}
		}
		else
		{
			_playerSight -= mySprite.getLocalBounds().width;
			if(_position.x - _playerSight > 0 && _position.x - _playerSight < mySprite.getLocalBounds().width)
			{
				sf::FloatRect spriteBounds = mySprite.getLocalBounds();
				sf::IntRect newSprite(spriteBounds.left, spriteBounds.top, spriteBounds.width - (_position.x - _playerSight), spriteBounds.height);
				mySprite.setTextureRect(newSprite);
			}
		}
	window->draw(playerSprite);
	if(!(!_playerDirec && _playerSight - _position.x >= 32) && !(_playerDirec && _position.x - _playerSight >= 32))
		window->draw(mySprite);
}

GameObject* GameObject::SetVelocity(sf::Vector2f velocity)
{
	_velocity = velocity;

	return this;
}

sf::Vector2f GameObject::GetVelocity(void)
{
	return _velocity;
}

GameObject* GameObject::Accelerate(sf::Vector2f acceleration)
{
	_velocity += acceleration;

	return this;
}

void GameObject::Move(float timeElapsed)
{
	_position += sf::Vector2f(timeElapsed * _velocity.x * 60, timeElapsed * _velocity.y * 60);
}

int GameObject::CheckCollideWithVelocity(GameObject* object1, GameObject* object2)
{
	if(CheckHCollideWithVelocity(object1, object2))
		return H_COLLISION;

	if(CheckVCollideWithVelocity(object1, object2))
		return V_COLLISION;

	return NO_COLLISION;
}

bool GameObject::CheckVCollideWithVelocity(GameObject* object1, GameObject* object2)
{
	sf::Vector2f veloc = object1->GetVelocity();

	GameObject* newObj1 = (new GameObject())->SetPosition(object1->_position + sf::Vector2f(0, veloc.y));

	return CheckCollide(newObj1, object2);
}

bool GameObject::CheckHCollideWithVelocity(GameObject* object1, GameObject* object2, bool onLadder)
{
	sf::Vector2f veloc = object1->GetVelocity();

	GameObject* newObj1 = (new GameObject())->SetPosition(object1->_position + sf::Vector2f(veloc.x, (onLadder ? -2 : 0)));

	return CheckCollide(newObj1, object2);
}

bool GameObject::CheckCollide(GameObject* object1, GameObject* object2)
{
	sf::FloatRect objectBounds = SpriteLibrary::GetSprite(0).getLocalBounds();

	if((object1->_position.x + (objectBounds.width))<(object2->_position.x)) return(false);
    if((object1->_position.x)>((object2->_position.x + (objectBounds.width)))) return(false);
	if((object1->_position.y + (objectBounds.height))<(object2->_position.y)) return(false);
    if((object1->_position.y)>(object2->_position.y + (objectBounds.height))) return(false);
   
	return(true);
}

int GameObject::GetSpriteID(void)
{
	return spriteID;
}

sf::Vector2f GameObject::GetPosition(void)
{
	return _position;
}

sf::Vector2f GameObject::GetCentre(void)
{
	sf::FloatRect spriteSize = SpriteLibrary::GetSprite(spriteID).getLocalBounds();

	return _position + sf::Vector2f(spriteSize.width/2, spriteSize.height/2);
}

void GameObject::MoveBy(sf::Vector2f vector)
{
	_position.x += vector.x;
	_position.y += vector.y;
}

void GameObject::DeltaVy(float vy)
{
	_velocity.y += vy;
}

void GameObject::PlayerSight(float sightX, bool direc)
{
	_playerSight = sightX;
	_playerDirec = direc;
}