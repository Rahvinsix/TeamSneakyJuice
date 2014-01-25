#pragma once

#include "GlobalHeader.h"
#include "Input.h"
#include "GameObject.h"
#include "SpriteLibrary.h"
#include "LevelClass.h"
#include "Player.h"


class Application
{
public:
	Application(void);
	~Application(void);
private:
	sf::RenderWindow* window;

	bool gameEnded;
	LevelClass *level;
	Player *player;

	void Update();
	void Draw();

	GameObject* testObject;
};

