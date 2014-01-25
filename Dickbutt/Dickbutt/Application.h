#pragma once

#include "GlobalHeader.h"
#include "Input.h"
#include "GameObject.h"
#include "SpriteLibrary.h"
#include "LevelClass.h"


class Application
{
public:
	Application(void);
	~Application(void);
private:
	void Update();
	void Draw();


	sf::RenderWindow* _window;

	bool _gameEnded;
	LevelClass* _level;

	GameObject* _testObject;
};

