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

	void Draw(sf::RenderWindow* window);
	void Update();

	GameObject* TileAt(int, int);

	int Width();
	int Height();


private:
	GameObject** _levelGrid;
	std::vector<SpinningObject> _spinningObjects;

	int _width;
	int _height;
};

