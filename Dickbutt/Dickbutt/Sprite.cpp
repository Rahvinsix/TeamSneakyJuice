#include "Sprite.h"


Sprite::Sprite(char* fileName)
{
	tex = new sf::Texture();

	if(!tex->loadFromFile(fileName))
	{
		printf("Sneaky juice interfering with file: %S", fileName);
		texLoaded = false;
	}
	else
		texLoaded = true;
}


Sprite::~Sprite(void)
{
	delete tex;
}

void Sprite::Draw(sf::RenderWindow* window)
{
	if(texLoaded)
	{
		sf::Sprite sprite;

		sprite.setTexture(*tex);

		window->draw(sprite);
	}
}