#include "Sprite.h"


Sprite::Sprite()
{
	texLoaded = false;
}

Sprite::Sprite(char* fileName)
{
	tex = new sf::Texture();

	if(!tex->loadFromFile(fileName))
	{
		printf("Sneaky juice interfering with file: %S", fileName);
		texLoaded = false;
	}
	else
	{
		printf("Finished loading: %s\n", fileName);
		texLoaded = true;
	}
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

sf::Texture Sprite::GetTexture()
{
	return *tex;
}