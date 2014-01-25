#pragma once

#include "GlobalHeader.h"
#include "Input.h"
#include "GameObject.h"
#include "SpriteLibrary.h"
#include "LevelClass.h"
#include "Player.h"
#include <sstream>


class Application
{
public:
	Application(void);
	~Application(void);
private:
	void Update();
	void Draw();


	sf::RenderWindow* _window;
	sf::Font* _font;

	float _timeSinceLastUpdate;

	bool _gameEnded;

	
	LevelClass* _level;
	Player* _player;
	sf::View* _camera;
};

