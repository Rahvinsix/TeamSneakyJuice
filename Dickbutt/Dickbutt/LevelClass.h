#pragma once
#include "GameObject.h"
class LevelClass
{
public:
	LevelClass(void);
	~LevelClass(void);
	void Draw(sf::RenderWindow* window);
	GameObject levelGrid[10][10];
	
private:
	
};

