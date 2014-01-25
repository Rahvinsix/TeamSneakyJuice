#include "TileGrid.h"


TileGrid::TileGrid(void)
{
	_currentTile = 0;
}


TileGrid::~TileGrid(void)
{
}

void TileGrid::Draw(sf::RenderWindow* window)
{
	for(int i = 0; i < TOTAL_SPRITES; i++)
	{
		sf::Sprite mySprite = SpriteLibrary::GetSprite(i);
		mySprite.setPosition(TILE_GRID_OFFSET + sf::Vector2f((i % GRID_WIDTH) * mySprite.getLocalBounds().width, int(i / GRID_WIDTH) * mySprite.getLocalBounds().height));
		window->draw(mySprite);
	}
}

void TileGrid::Click(sf::Event::MouseButtonEvent mE)
{
	sf::FloatRect spriteSize = SpriteLibrary::GetSprite(0).getLocalBounds();

	sf::Vector2f mousePos(mE.x, mE.y);
	mousePos -= TILE_GRID_OFFSET;
	mousePos.x += spriteSize.width * int((mousePos.y / spriteSize.width) / GRID_WIDTH);

	if(mE.x > TILE_GRID_OFFSET.x && mE.x < TILE_GRID_OFFSET.x + GRID_WIDTH * spriteSize.width)
	{
		int tilePos = int(mousePos.x / spriteSize.width) + int(mousePos.y / spriteSize.height) * GRID_WIDTH;
		if(tilePos < TOTAL_SPRITES && tilePos >= 0)
			_currentTile = tilePos;
	}
	
	printf("Tile pos: %d. Tile is %d\n", int(mousePos.x / spriteSize.width) + int(mousePos.y / spriteSize.height) * GRID_WIDTH, _currentTile);
}

int TileGrid::CurrentTile()
{
	return _currentTile;
}