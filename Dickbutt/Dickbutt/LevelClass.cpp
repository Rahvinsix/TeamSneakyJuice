#include "LevelClass.h"


LevelClass::LevelClass(std::string fileName)
{
	sf::FloatRect spriteSize = SpriteLibrary::GetSprite(0).getLocalBounds();

	std::ifstream inputFile(fileName);
	std::vector<std::string> lines;

	while(!inputFile.eof())
	{
		std::string line;
		std::getline(inputFile, line);
		lines.push_back(line);
	}

	_width = lines.size()-1;
	_height = lines.at(0).length();

	_levelGrid = new GameObject*[_width];
	int lineNum = 0;

	for(std::vector<std::string>::iterator mapLine = lines.begin(); mapLine != lines.end(); mapLine++)
	{
		_levelGrid[lineNum] = new GameObject[mapLine->length()];

		for(int i = 0; i < mapLine->length(); i++)
		{
			_levelGrid[lineNum][i].SetPosition(sf::Vector2f(lineNum*spriteSize.width, i*spriteSize.height));
			_levelGrid[lineNum][i].SetSpriteID(mapLine->at(i)-48);

			if(mapLine->at(i)-48 == SpriteLibrary::SPIN_BLOCK)
				_spinningObjects.push_back(SpinningObject(lineNum, i));
		}

		lineNum++;
	}
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
	for(int i = 0; i < _width; i++)
	{
		for(int j = 0; j < _height; j++)
		{	
			_levelGrid[i][j].Draw(window);
		}
	}

	for(std::vector<SpinningObject>::iterator spinObj = _spinningObjects.begin(); spinObj != _spinningObjects.end(); spinObj++)
		spinObj->Draw(window);
}

GameObject* LevelClass::TileAt(int x, int y)
{
	return &_levelGrid[x][y];
}

int LevelClass::Width()
{
	return _width;
}

int LevelClass::Height()
{
	return _height;
}
