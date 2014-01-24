#pragma once

#include "GlobalHeader.h"
#include "GameObject.h"
#include "MapGrid.h"


class Application
{
public:
	Application(void);
	~Application(void);
private:
	sf::RenderWindow* window;

	bool gameEnded;

	MapGrid mapGrid;
	
	bool mouseDown;


	void Update();
	void Draw();
};

