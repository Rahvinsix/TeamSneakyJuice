#pragma once

#include "GameObject.h"
#include "SpinningObject.h"
#include <vector>
#include <fstream>


class LevelClass
{
public:
	LevelClass(std::string fileName);
	~LevelClass(void);

	void LoadFromFile(char* fileName);

	void Draw(sf::RenderWindow* window, sf::Vector2f playerCentre);
	void Update();

	GameObject* TileAt(int, int);
	void SetTileAt(int, int, int);

	bool LevelComplete();

	int Width();
	int Height();
	std::vector<SpinningObject> _spinningObjects;



private:
	GameObject** _levelGrid;
	
	int _width;
	int _height;
};

