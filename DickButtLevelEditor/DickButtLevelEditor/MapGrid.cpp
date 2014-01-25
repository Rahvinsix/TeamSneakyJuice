#include "MapGrid.h"


MapGrid::MapGrid(std::string fileName, int width, int height)
{
	_mapWidth = width;
	_mapHeight = height;
	_fileName = fileName;
	std::ifstream file(_fileName);
	std::string currentLine;

	map = new int*[_mapWidth];
	for(int i = 0; i < _mapWidth; i++)
	{
		if(file)
			std::getline(file, currentLine);
		map[i] = new int[_mapHeight];
		for(int j = 0; j < _mapHeight; j++)
			if(!file)
				map[i][j] = 0;
			else
				map[i][j] = currentLine.at(j)-48;
	}
}


MapGrid::~MapGrid(void)
{
	std::ofstream file(_fileName);

	for(int i = 0; i < _mapWidth; i++)
	{
		for(int j = 0; j < _mapHeight; j++)
			file << map[i][j];
		file << "\n";
	}

	file.close();
}

void MapGrid::Draw(sf::RenderWindow* window)
{
	spriteSize = SpriteLibrary::GetSprite(0).getLocalBounds();

	float mapSize = MAP_SCREEN_WIDTH / _mapWidth;
	if(mapSize > MAP_SCREEN_HEIGHT / _mapHeight)
		mapSize = MAP_SCREEN_HEIGHT / _mapHeight;

	spriteSize.width = mapSize;
	spriteSize.height = mapSize;

	for(int i = 0; i < _mapWidth; i++)
		for(int j = 0; j < _mapHeight; j++)
		{
			sf::Sprite sprite = SpriteLibrary::GetSprite(map[i][j]);
			sprite.setPosition(spriteSize.width * i, spriteSize.height * j);
			sprite.setScale(spriteSize.width / sprite.getLocalBounds().width, spriteSize.height / sprite.getLocalBounds().height);
			window->draw(sprite);
		}
}

void MapGrid::Click(int x, int y, int currentTile)
{
	if(x < spriteSize.width * _mapWidth && x >= 0 && y < spriteSize.height * _mapHeight && y >= 0)
		map[int(x / spriteSize.width)][int(y / spriteSize.height)] = currentTile;
}