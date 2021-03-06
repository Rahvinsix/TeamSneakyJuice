#pragma once

#include "GlobalHeader.h"
#include "GameObject.h"


class SpinningObject :
	public GameObject
{
public:
	SpinningObject(int, int, int, bool);
	~SpinningObject(void);

	void SetDistance(int);
	GameObject* GetGameObject(void);
	void Update(float);
	void Draw(sf::RenderWindow*);


private:
	GameObject _gameObject;

	int _type;

	float _angleStage;

	int _distance;

	int _xLoc;
	int _yLoc;
};

