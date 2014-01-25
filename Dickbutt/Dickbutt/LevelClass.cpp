#include "LevelClass.h"


LevelClass::LevelClass(void)
{
	sf::FloatRect spriteSize = SpriteLibrary::GetSprite(0).getLocalBounds();
	for(int i = 0; i < 10;i++)
	{
		for(int j = 0;j < 10; j++)
		{
			_levelGrid[i][j].SetPosition(sf::Vector2f(i*spriteSize.width,j*spriteSize.height));
			if(j==9||i==0||i==9)
			{
				_levelGrid[i][j].SetSpriteID(SpriteLibrary::GROUND);
			}
			else
			{
				_levelGrid[i][j].SetSpriteID(SpriteLibrary::AIR);
			}
		}
	}

	_levelGrid[4][4].SetSpriteID(SpriteLibrary::SPIN_BLOCK);

	_spinningObjects.push_back(SpinningObject(4, 4));
}


LevelClass::~LevelClass(void)
{
}

void LevelClass::Update()
{
	for(std::vector<SpinningObject>::iterator spinObj = _spinningObjects.begin(); spinObj != _spinningObjects.end(); spinObj++)
		spinObj->Update();
}

void LevelClass::Draw(sf::RenderWindow* window)
{
	for(int i = 0; i < 10;i++)
	{
		for(int j = 0;j < 10; j++)
		{	
			_levelGrid[i][j].Draw(window);
		}
	}

	for(std::vector<SpinningObject>::iterator spinObj = _spinningObjects.begin(); spinObj != _spinningObjects.end(); spinObj++)
		spinObj->Draw(window);
}
