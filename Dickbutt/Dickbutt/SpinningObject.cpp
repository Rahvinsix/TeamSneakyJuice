#include "SpinningObject.h"


SpinningObject::SpinningObject(int xLoc, int yLoc)
{
	_xLoc = xLoc;
	_yLoc = yLoc;

	_angleStage = 0;
	_distance = 3;
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
}

void SpinningObject::Draw(sf::RenderWindow* window)
{
	sf::Sprite sprite = SpriteLibrary::GetSprite(SpriteLibrary::SPIN_OBJECT);
	sf::FloatRect spriteSize = sprite.getLocalBounds();
	
	sprite.setPosition(_xLoc * spriteSize.width, _yLoc * spriteSize.height);
	sprite.move(cos(_angleStage) * spriteSize.width * _distance, sin(_angleStage) * spriteSize.height * _distance);

	for(int i = 0; i < _distance; i++)
	{
		sf::Sprite chainSprite = SpriteLibrary::GetSprite(SpriteLibrary::SPIN_CHAIN);
		chainSprite.setOrigin(spriteSize.width/2, spriteSize.height/2);
		chainSprite.setRotation(((_angleStage*180)/3.142) + 90);
		chainSprite.setPosition((_xLoc+0.5) * spriteSize.width, (_yLoc+0.5) * spriteSize.height);
		chainSprite.move(cos(_angleStage) * spriteSize.width * (i+0.5), sin(_angleStage) * spriteSize.height * (i+0.5));

		window->draw(chainSprite);
	}

	window->draw(sprite);
}