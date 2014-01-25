#pragma once
#include "GlobalHeader.h"


class Input
{
public:
	Input(void);
	~Input(void);
	static void GetInput(void);
	static void Update(void);
	static void KeyPressed(sf::Keyboard::Key);
	static void KeyReleased(sf::Keyboard::Key);
	static bool IsDown(sf::Keyboard::Key);
	static bool IsUp(sf::Keyboard::Key);
	static bool IsPressed(sf::Keyboard::Key);
	static bool IsReleased(sf::Keyboard::Key);
	static void Initialise(void);


private:
	static bool* keys;//[sf::Keyboard::KeyCount];
	static bool* prevKeys;//[sf::Keyboard::KeyCount];
	
	
};

