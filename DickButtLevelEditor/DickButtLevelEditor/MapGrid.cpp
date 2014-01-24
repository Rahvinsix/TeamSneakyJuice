#include "MapGrid.h"


MapGrid::MapGrid(void)
{
	sprites = new Sprite*[2];

	sprites[0] = new Sprite("Assets/Images/dirtCenter.png");
	sprites[1] = new Sprite("Assets/Images/dirtCenter_2.png");

	map = new int*[MAP_WIDTH];
	for(int i = 0; i < MAP_WIDTH; i++)
	{
		map[i] = new int[MAP_HEIGHT];
		for(int j = 0; j < MAP_HEIGHT; j++)
			map[i][j] = i % 2;
	}
}


MapGrid::~MapGrid(void)
{
}

void MapGrid::Draw(sf::RenderWindow* window)
{
	spriteSize = sprites[0]->GetSprite().getLocalBounds();

	float mapSize = MAP_SCREEN_WIDTH / MAP_WIDTH;
	if(mapSize > MAP_SCREEN_HEIGHT / MAP_HEIGHT)
		mapSize = MAP_SCREEN_HEIGHT / MAP_HEIGHT;

	spriteSize.width = mapSize;
	spriteSize.height = mapSize;

	for(int i = 0; i < MAP_WIDTH; i++)
		for(int j = 0; j < MAP_HEIGHT; j++)
		{
			sf::Sprite sprite = sprites[map[i][j]]->GetSprite();
			sprite.setPosition(spriteSize.width * i, spriteSize.height * j);
			sprite.setScale(spriteSize.width / sprite.getLocalBounds().width, spriteSize.height / sprite.getLocalBounds().height);
			window->draw(sprite);
		}
}

void MapGrid::Click(sf::Event::MouseMoveEvent mE)
{
	if(mE.x < spriteSize.width * MAP_WIDTH && mE.x >= 0 && mE.y < spriteSize.height * MAP_HEIGHT && mE.y >= 0)
		map[int(mE.x / spriteSize.width)][int(mE.y / spriteSize.height)] = 1;
}