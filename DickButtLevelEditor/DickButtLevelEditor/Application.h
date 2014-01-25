#pragma once

#include "GlobalHeader.h"
#include "GameObject.h"
#include "MapGrid.h"
#include "SpriteLibrary.h"
#include "TileGrid.h"
#include <fstream>
#include <sstream>


class Application
{
public:
	Application(void);
	~Application(void);
private:
	sf::RenderWindow* window;

	bool gameEnded;

	MapGrid* mapGrid;
	TileGrid tileGrid;
	
	bool mouseDown;

	std::string fileName;


	void Update();
	void Draw();
};

