#pragma once

#include "GlobalHeader.h"
#include "GameObject.h"
#include "MapGrid.h"
#include "SpriteLibrary.h"
#include "TileGrid.h"


class Application
{
public:
	Application(void);
	~Application(void);
private:
	sf::RenderWindow* window;

	bool gameEnded;

	MapGrid mapGrid;
	TileGrid tileGrid;
	
	bool mouseDown;


	void Update();
	void Draw();
};

