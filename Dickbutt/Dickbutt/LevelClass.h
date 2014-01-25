#pragma once

#include "GameObject.h"
#include "SpinningObject.h"
#include <vector>


class LevelClass
{
public:
	LevelClass(void);
	~LevelClass(void);

	void Draw(sf::RenderWindow* window);
	void Update();


private:
	GameObject _levelGrid[10][10];
	std::vector<SpinningObject> _spinningObjects;
};

