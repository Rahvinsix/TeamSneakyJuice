#pragma once

#include "GlobalHeader.h"
#include "Input.h"
#include "GameObject.h"
#include "SpriteLibrary.h"
#include "LevelClass.h"
#include "Player.h"
#include <sstream>
#include <iostream>

#define TOTAL_LEVELS 7


class Application
{
public:
	Application(void);
	~Application(void);
private:
	void Update();
	void Draw();

	void StartLevel();
	void EndGame();


	sf::RenderWindow* _window;

	float _timeSinceLastUpdate;

	bool _gameEnded;

	int _currentLevel;
	int _doori;
	int _doorj;
	std::string* _levelNames;
	

	LevelClass* _level;
	Player* _player;
	sf::View* _camera;
	sf::Font* _font;
};

