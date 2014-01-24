#include "LevelClass.h"


LevelClass::LevelClass(void)
{
	sf::FloatRect spriteSize = SpriteLibrary::GetSprite(0).getLocalBounds();
	for(int i = 0; i < 10;i++)
	{
		for(int j = 0;j < 10; j++)
		{
			levelGrid[i][j].SetPosition(sf::Vector2f(i*spriteSize.width,j*spriteSize.height));
			if(j%2==0)
			{
				levelGrid[i][j].SetSpriteID(SpriteLibrary::GROUND);
			}
			else
			{
				levelGrid[i][j].SetSpriteID(SpriteLibrary::AIR);
			}
		}
	}
}


LevelClass::~LevelClass(void)
{
}

void LevelClass::Draw(sf::RenderWindow* window)
{
	for(int i = 0; i < 10;i++)
	{
		for(int j = 0;j < 10; j++)
		{	
			levelGrid[i][j].Draw(window);
		}
	}
}
