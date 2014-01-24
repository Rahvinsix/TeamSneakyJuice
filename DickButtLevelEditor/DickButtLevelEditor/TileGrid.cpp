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
		mySprite.setPosition(TILE_GRID_OFFSET + sf::Vector2f(i * mySprite.getLocalBounds().width, 0));
		window->draw(mySprite);
	}
}

void TileGrid::Click(sf::Event::MouseButtonEvent mE)
{
	sf::FloatRect spriteSize = SpriteLibrary::GetSprite(0).getLocalBounds();


	if(mE.x > TILE_GRID_OFFSET.x && mE.x < TILE_GRID_OFFSET.x + TOTAL_SPRITES * spriteSize.width && mE.y > TILE_GRID_OFFSET.y && mE.y < TILE_GRID_OFFSET.y + spriteSize.height)
		_currentTile = (mE.x - TILE_GRID_OFFSET.x) / spriteSize.width;
}

int TileGrid::CurrentTile()
{
	return _currentTile;
}