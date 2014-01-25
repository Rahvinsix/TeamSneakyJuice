#include "Application.h"

sf::Clock _worldTime;
sf::Clock _updateTime;

Application::Application(void)
{
	_window = new sf::RenderWindow(sf::VideoMode(800, 600), "Team Sneaky Juice");

	SpriteLibrary::Initialise();

	Input::Initialise();
	_gameEnded = false;
	

	_camera = new sf::View(sf::FloatRect(0, 0, 800, 600));
	_window->setView(*_camera);

	_currentLevel = 1;
	StartLevel();

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
			switch(_level->TileAt(i, j)->GetSpriteID())
			{
			case SpriteLibrary::GROUND:
				if(GameObject::CheckHCollideWithVelocity(_player, _level->TileAt(i, j)))
				{
					_player->MoveBy(sf::Vector2f(-(_player->GetVelocity().x),0.0f));
				}
				if(GameObject::CheckVCollideWithVelocity(_player, _level->TileAt(i, j)))
				{
					_player->MoveBy(sf::Vector2f(0.0f,-(_player->GetVelocity().y)));
					_player->VerticalCollision();
				}
				break;
			case SpriteLibrary::DOOR:
				if(GameObject::CheckCollide(_player, _level->TileAt(i, j)))
				{
					if(_level->LevelComplete())
					{
						_currentLevel++;
						if(_currentLevel <= TOTAL_LEVELS)
							StartLevel();
						else
							EndGame();
					}
				}
				break;
			case SpriteLibrary::LAVA_1:
			case SpriteLibrary::LAVA_2:
			case SpriteLibrary::LAVA_3:
			case SpriteLibrary::LAVA_4:
			case SpriteLibrary::LAVA_5:
			case SpriteLibrary::LAVA_6:
			case SpriteLibrary::H_SPIKES:
			case SpriteLibrary::V_SPIKES:
			case SpriteLibrary::H_SPIKES_FLIPPED:
				if(GameObject::CheckCollide(_player, _level->TileAt(i, j)))
				{
					_player->Death();
					printf("DEAD");
				}
				break;
			case SpriteLibrary::LADDER:
				if(GameObject::CheckCollide(_player, _level->TileAt(i, j)))
				{
					_player->_onLadder = true;
				}
				else
				{
					_player->_onLadder = false;				
				}
				break;
			}
		}
	}

	for(std::vector<SpinningObject>::iterator i = _level->_spinningObjects.begin();i!= _level->_spinningObjects.end();i++)
	{
	
		if((GameObject::CheckCollide(_player, i->GetGameObject())) && (i->GetGameObject()->GetSpriteID() == SpriteLibrary::HEART_END))
		{
		
			i->GetGameObject()->SetSpriteID(SpriteLibrary::AIR);
			_player->addHeart();
			printf("Hearts %d\n",_player->checkHearts());

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

void Application::StartLevel()
{
	std::stringstream lvlName;
	lvlName << "Assets/Levels/level";
	if(_currentLevel < 10)
		lvlName << "0";
	lvlName << _currentLevel;
	lvlName << ".txt";

	_level = new LevelClass(lvlName.str());
	_player = new Player();

	for(int i = 0; i < _level->Width();i++)
	{
		for(int j = 0;j < _level->Height(); j++)
		{
			if(_level->TileAt(i, j)->GetSpriteID() == SpriteLibrary::PLAYER)
			{
				_player->SetSpriteID(_level->TileAt(i, j)->GetSpriteID());
				_player->SetPosition(_level->TileAt(i, j)->GetPosition());
				_player->setSpawn(_level->TileAt(i, j)->GetPosition());
				_level->SetTileAt(i, j, SpriteLibrary::AIR);
			}
		}
	}
}

void Application::EndGame()
{
	printf("Game over, chump");
}

Application::~Application(void)
{
	delete _window;
	delete _level;
	delete _player;
	delete _camera;
	delete _font;
}
