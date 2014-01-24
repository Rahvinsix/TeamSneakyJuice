#pragma once

#include "GlobalHeader.h"
#include "Input.h"
#include "GameObject.h"


class Application
{
public:
	Application(void);
	~Application(void);
private:
	sf::RenderWindow* window;

	bool gameEnded;


	void Update();
	void Draw();

	GameObject* testObject;
};

