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
		printf("Sneaky juice interfering with file: %s\n", fileName);
		texLoaded = false;
	}
	else
	{
		printf("Loaded file: %s\n", fileName);
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