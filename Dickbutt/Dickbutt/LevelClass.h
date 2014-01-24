#pragma once
#include "GameObject.h"
class LevelClass
{
public:
	LevelClass(void);
	~LevelClass(void);
	void Draw(sf::RenderWindow* window);
private:
	GameObject levelGrid[10][10];
};

