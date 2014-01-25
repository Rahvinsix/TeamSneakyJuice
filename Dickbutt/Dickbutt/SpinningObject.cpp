#include "SpinningObject.h"


SpinningObject::SpinningObject(int xLoc, int yLoc)
{
	_xLoc = xLoc;
	_yLoc = yLoc;

	_angleStage = 0;
}


SpinningObject::~SpinningObject(void)
{
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

	sprite.move(cos(_angleStage) * spriteSize.width * 5, sin(_angleStage) * spriteSize.height * 5);

	window->draw(sprite);
}