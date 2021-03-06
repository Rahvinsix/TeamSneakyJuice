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

sf::Sprite Sprite::GetSprite()
{
	sf::Sprite sprite;

	if(texLoaded)
	{
		sprite.setTexture(*tex);
	}

	return sprite;
}