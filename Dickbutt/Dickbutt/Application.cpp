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
	

	_camera = new sf::View(sf::FloatRect(0, 0, 800, 600));
	_window->setView(*_camera);

	for(int i = 0; i < _level->Width();i++)
	{
		for(int j = 0;j < _level->Height(); j++)
		{
			if(_level->TileAt(i, j)->GetSpriteID() == SpriteLibrary::PLAYER)
			{
				_player->SetSpriteID(_level->TileAt(i, j)->GetSpriteID());
				_player->SetPosition(_level->TileAt(i, j)->GetPosition());
			}
		}
	}

	_font = new sf::Font();
	_font->loadFromFile("Assets/Fonts/arial.ttf");

	
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

	if(_player->_playerFacing)
	{
		for(int i = 0; i < _level->Width();i++)
			for(int j = 0;j < _level->Height(); j++)
				if((_level->TileAt(i, j)->GetSpriteID() != SpriteLibrary::AIR) && (_level->TileAt(i, j)->GetPosition().x > _player->GetPosition().x))
					_level->TileAt(i, j)->seen = true;
				else
					_level->TileAt(i, j)->seen = false;

		for(std::vector<SpinningObject>::iterator i = _level->_spinningObjects.begin();i!= _level->_spinningObjects.end();i++)
			if(i->GetGameObject()->GetPosition().x > _player->GetPosition().x)
				i->GetGameObject()->seen = true;
			else
				i->GetGameObject()->seen = false;
	}
	else
	{
		for(int i = 0; i < _level->Width();i++)
			for(int j = 0;j < _level->Height(); j++)
				if((_level->TileAt(i, j)->GetSpriteID() != SpriteLibrary::AIR) && (_level->TileAt(i, j)->GetPosition().x < _player->GetPosition().x))
					_level->TileAt(i, j)->seen = true;
				else
					_level->TileAt(i, j)->seen = false;

		for(std::vector<SpinningObject>::iterator i = _level->_spinningObjects.begin();i!= _level->_spinningObjects.end();i++)
		{
	
			if(i->GetGameObject()->GetPosition().x < _player->GetPosition().x)
			{
		
				i->GetGameObject()->seen = true;

			}
			else
			{
			
				i->GetGameObject()->seen = false;

			}
	
		}
	}

	//Update player input
	Input::Update();
	_player->Update();

	sf::FloatRect spriteSize = SpriteLibrary::GetSprite(0).getLocalBounds();
	sf::Vector2i playerTilePos(int(_player->GetCentre().x / spriteSize.width), int(_player->GetCentre().y / spriteSize.height));

	for(int i = MAX(playerTilePos.x - 2, 0); i < MIN(_level->Width(), playerTilePos.x + 2);i++)
	{
		for(int j = MAX(playerTilePos.y - 2, 0);j < MIN(_level->Height(), playerTilePos.y + 2); j++)
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
			else if(_level->TileAt(i, j)->GetSpriteID() == SpriteLibrary::DOOR)
			{
				if(GameObject::CheckCollide(_player, _level->TileAt(i, j)))
				{
		
					printf("DOOR COLLIDE\N");

				}
			}
			else if(_level->TileAt(i, j)->GetSpriteID() == SpriteLibrary::LADDER)
			{
			
				if(GameObject::CheckCollide(_player, _level->TileAt(i, j)))
				{
					_player->_onLadder = true;
				}
				else
				{
					_player->_onLadder = false;				
				}
			}
		}
	}

	for(std::vector<SpinningObject>::iterator i = _level->_spinningObjects.begin();i!= _level->_spinningObjects.end();i++)
	{
	
		if(GameObject::CheckCollide(_player, i->GetGameObject()))
		{
		
			printf("Collide with spinner");

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

	_camera->setCenter(_player->GetCentre());
	_window->setView(*_camera);
}

void Application::Draw()
{
    _window->clear(sf::Color(255, 255, 255, 255));

	_level->Draw(_window, _player->GetCentre());
	_player->DrawPlayer(_window);
	
	sf::Text fps;
	std::stringstream ss;
	ss << "FPS: ";
	ss << int(1 / _timeSinceLastUpdate);
	fps.setString(ss.str());
	fps.setFont(*_font);
	fps.setPosition(_player->GetCentre() + sf::Vector2f(-380, -280));
	_window->draw(fps);
	
    _window->display();
}

Application::~Application(void)
{
	delete _window;
	delete _level;
	delete _player;
	delete _camera;
	delete _font;
}
