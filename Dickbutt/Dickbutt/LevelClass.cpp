#include "LevelClass.h"


LevelClass::LevelClass(std::string fileName)
{
	sf::FloatRect spriteSize = SpriteLibrary::GetSprite(0).getLocalBounds();

	std::ifstream inputFile(fileName);
	std::vector<std::string> lines;

	if(!inputFile)
		printf("File missing: %s\n", fileName);
	else
		printf("File loaded: %s\n", fileName);

	while(!inputFile.eof())
	{
		std::string line;
		std::getline(inputFile, line);
		lines.push_back(line);
	}

	inputFile.close();

	printf("File closed %s\n", fileName);

	_width = lines.size()-1;
	_height = lines.at(0).length()/2;

	_levelGrid = new GameObject*[_width];
	int lineNum = 0;

	for(std::vector<std::string>::iterator mapLine = lines.begin(); mapLine != lines.end(); mapLine++)
	{
		_levelGrid[lineNum] = new GameObject[mapLine->length()];

		for(int i = 0; i < mapLine->length(); i+=2)
		{
			int num = (mapLine->at(i)-48) * 10 + mapLine->at(i+1)-48;

			_levelGrid[lineNum][int(i/2)].SetPosition(sf::Vector2f(lineNum*spriteSize.width, int(i/2)*spriteSize.height));
			_levelGrid[lineNum][int(i/2)].SetSpriteID(num);

			if(num == SpriteLibrary::HEART || num == SpriteLibrary::SPIKE_BALL)
				_spinningObjects.push_back(SpinningObject(lineNum, int(i/2), num, false));
			if(num == SpriteLibrary::HEART_AND_BALL)
			{
				_spinningObjects.push_back(SpinningObject(lineNum, int(i/2), SpriteLibrary::HEART, false));
				_spinningObjects.push_back(SpinningObject(lineNum, int(i/2), SpriteLibrary::SPIKE_BALL, true));
			}
			if(num == SpriteLibrary::DOUBLE_BALL)
			{
				_spinningObjects.push_back(SpinningObject(lineNum, int(i/2), SpriteLibrary::SPIKE_BALL, false));
				_spinningObjects.push_back(SpinningObject(lineNum, int(i/2), SpriteLibrary::SPIKE_BALL, true));
			}
		}

		lineNum++;
	}

	printf("Level loaded\n");

	_timeRemaining = 120.0f;
}


LevelClass::~LevelClass(void)
{
}

void LevelClass::Update(float timeSinceLastUpdate)
{
	for(std::vector<SpinningObject>::iterator spinObj = _spinningObjects.begin(); spinObj != _spinningObjects.end(); spinObj++)
		spinObj->Update(timeSinceLastUpdate);

	_timeRemaining -= timeSinceLastUpdate;
}

bool LevelClass::TimeUp()
{
	return _timeRemaining <= 0;
}

int LevelClass::TimeRemaining()
{
	return int(_timeRemaining);
}

void LevelClass::Draw(sf::RenderWindow* window, sf::Vector2f playerCentre)
{
	sf::FloatRect spriteSize = SpriteLibrary::GetSprite(0).getLocalBounds();
	sf::Vector2i playerTilePos(int(playerCentre.x / spriteSize.width), int(playerCentre.y / spriteSize.height));
	
	sf::Texture background = SpriteLibrary::GetTexture(SpriteLibrary::AIR);
	sf::Sprite backgroundSprite;
	
	background.setRepeated(true);
	
	backgroundSprite.setTexture(background);
	backgroundSprite.setOrigin(spriteSize.width / 2, spriteSize.height / 2);
	backgroundSprite.move(playerCentre);
	backgroundSprite.setScale(800/spriteSize.width, 600/spriteSize.height);

	window->draw(backgroundSprite);

	for(int i = MAX(playerTilePos.x - 14, 0); i < MIN(_width, playerTilePos.x + 14);i++)
	{
		for(int j = MAX(playerTilePos.y - 11, 0);j < MIN(_height, playerTilePos.y + 11); j++)
		{
			if(_levelGrid[i][j].GetSpriteID() != SpriteLibrary::AIR)
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

void LevelClass::SetTileAt(int x, int y, int num)
{
	_levelGrid[x][y].SetSpriteID(num);
}

int LevelClass::Width()
{
	return _width;
}

int LevelClass::Height()
{
	return _height;
}
