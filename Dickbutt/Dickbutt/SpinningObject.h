#pragma once

#include "GlobalHeader.h"
#include "GameObject.h"


class SpinningObject :
	public GameObject
{
public:
	SpinningObject(int, int);
	~SpinningObject(void);

	void Update(void);
	void Draw(sf::RenderWindow*);


private:
	float _angleStage;

	int _xLoc;
	int _yLoc;
};

