#include "Application.h"

sf::Clock _worldTime;
sf::Clock _updateTime;

Application::Application(void)
{
	_window = new sf::RenderWindow(sf::VideoMode(800, 600), "Team Sneaky Juice");

	SpriteLibrary::Initialise();

	Input::Initialise();
	_level = new LevelClass("Assets/Levels/level01.txt");
	_player = new Player();
	_gameEnded = false;
	
    while (_window->isOpen())
    {
		Update();
		Draw();

		if(_gameEnded || Input::IsDown(sf::Keyboard::Key::Escape))
			_window->close();
    }
}

void Application::Update()
{
	_timeSinceLastUpdate = _updateTime.getElapsedTime().asSeconds();
	_updateTime.restart();


	//Update player input
	Input::Update();
	_player->Update();

	for(int i = 0; i < _level->Width();i++)
	{
		for(int j = 0;j < _level->Height(); j++)
		{
			if(_level->TileAt(i, j)->GetSpriteID() == SpriteLibrary::GROUND)
			{
				if(GameObject::CheckHCollideWithVelocity(_player, _level->TileAt(i, j)))
				{
					_player->MoveBy(sf::Vector2f(-(_player->GetVelocity().x),0.0f));
				}
				if(GameObject::CheckVCollideWithVelocity(_player, _level->TileAt(i, j)))
				{
					_player->MoveBy(sf::Vector2f(0.0f,-(_player->GetVelocity().y)));
					_player->VerticalCollision();
				}
			}
		}
	}
	
    sf::Event event;
    while(_window->pollEvent(event))
    {
		switch(event.type)
		{
		case sf::Event::Closed:
			_gameEnded = true;
			break;
		case sf::Event::KeyPressed:
			Input::KeyPressed(event.key.code);
			break;
		case sf::Event::KeyReleased:
			Input::KeyReleased(event.key.code);
			break;
		}
    }

	_level->Update();
}

void Application::Draw()
{
    _window->clear(sf::Color(255, 255, 255, 255));

	_level->Draw(_window);
	_player->Draw(_window);

    _window->display();
}

Application::~Application(void)
{
	delete _window;
	delete _level;
	delete _player;
}
