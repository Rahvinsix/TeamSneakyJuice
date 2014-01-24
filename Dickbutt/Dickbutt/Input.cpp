#include "Input.h"

bool* Input::keys = new bool[sf::Keyboard::KeyCount];
bool* Input::prevKeys = new bool[sf::Keyboard::KeyCount];


Input::Input(void)
{
	
	
}


Input::~Input(void)
{
}

void Input::Update(void)
{
	for(int i = 0; i < sf::Keyboard::KeyCount;i++)
	{
		prevKeys[i] = keys[i];
	}
}

void Input::KeyPressed(sf::Keyboard::Key key)
{
	keys[key] = true;
}

void Input::KeyReleased(sf::Keyboard::Key key)
{
	keys[key] = false;
}

bool Input::IsDown(sf::Keyboard::Key key)
{
	return keys[key];
}

bool Input::IsUp(sf::Keyboard::Key key)
{
	return !keys[key];
}

bool Input::IsPressed(sf::Keyboard::Key key)
{
	if(keys[key] && !prevKeys[key])
	{
		return true;
	}
}

bool Input::IsReleased(sf::Keyboard::Key key)
{
	if(!keys[key] && prevKeys[key])
	{
		return true;
	}
}