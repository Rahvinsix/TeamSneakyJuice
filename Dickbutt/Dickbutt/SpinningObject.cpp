#include "SpinningObject.h"


SpinningObject::SpinningObject(int xLoc, int yLoc)
{
	_xLoc = xLoc;
	_yLoc = yLoc;

	_angleStage = 0;
	_distance = 3;

	_gameObject.SetSpriteID(SpriteLibrary::SPIKE_END);
}


SpinningObject::~SpinningObject(void)
{
}

void SpinningObject::SetDistance(int distance)
{
	_distance = distance;
}

void SpinningObject::Update(void)
{
	_angleStage += 0.01;

	sf::FloatRect spriteSize = SpriteLibrary::GetSprite(_gameObject.GetSpriteID()).getLocalBounds();
	
	_gameObject.SetPosition(sf::Vector2f(_xLoc * spriteSize.width, _yLoc * spriteSize.height));
	_gameObject.MoveBy(sf::Vector2f(cos(_angleStage) * spriteSize.width * _distance, sin(_angleStage) * spriteSize.height * _distance));
}

void SpinningObject::Draw(sf::RenderWindow* window)
{
	sf::FloatRect spriteSize = SpriteLibrary::GetSprite(_gameObject.GetSpriteID()).getLocalBounds();

	for(int i = 0; i < _distance; i++)
	{
		sf::Sprite chainSprite = SpriteLibrary::GetSprite(SpriteLibrary::SPIN_CHAIN);
		chainSprite.setOrigin(spriteSize.width/2, spriteSize.height/2);
		chainSprite.setRotation(((_angleStage*180)/3.142) + 90);
		chainSprite.setPosition((_xLoc+0.5) * spriteSize.width, (_yLoc+0.5) * spriteSize.height);
		chainSprite.move(cos(_angleStage) * spriteSize.width * (i+0.5), sin(_angleStage) * spriteSize.height * (i+0.5));

		window->draw(chainSprite);
	}

	_gameObject.Draw(window);
}

GameObject* SpinningObject::GetGameObject(void)
{

	return &_gameObject;

}