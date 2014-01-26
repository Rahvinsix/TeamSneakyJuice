#include "Application.h"

sf::Clock _worldTime;
sf::Clock _updateTime;

enum {SPLASH,PLAYING,END};

Application::Application(void)
{
	_window = new sf::RenderWindow(sf::VideoMode(800, 600), "Team Sneaky Juice");

	SpriteLibrary::Initialise();

	Input::Initialise();
	_gameEnded = false;
	
	int gameState = SPLASH;

	_camera = new sf::View(sf::FloatRect(0, 0, 800, 600));
	_window->setView(*_camera);

	_currentLevel = 1;
	StartLevel();

	_font.loadFromFile("Assets/Fonts/arial.ttf");

	_window->setFramerateLimit(60);

	
	sf::Music music;
	if (!music.openFromFile("Assets/Sounds/track01.ogg"))
	{
		printf("Error loading musics");
	}
    
	music.play();
	music.setLoop(true);

	_died = false;
	_goToNextLevel = false;
	_timeToWait = 0.0f;
	
	printf("Start to draw splash\n");
	splash = new sf::Sprite();
	splash->setTexture(SpriteLibrary::GetTexture(SpriteLibrary::SPLASH));
	SplashScreen();
	printf("End drawing splash\n");
	
	_updateTime.restart();

	
   while (_window->isOpen())
    {
		Input::Update();
		switch(gameState)
		{
			case SPLASH:
				if(Input::IsDown(sf::Keyboard::Space))
					gameState = PLAYING;
				break;
			case PLAYING:
				Update();
				Draw();
				break;
			case END:
				EndGame();
				break;
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

		if(_gameEnded || Input::IsDown(sf::Keyboard::Key::Escape))
			_window->close();
    }
}

void Application::Update()
{
	_timeSinceLastUpdate = _updateTime.getElapsedTime().asSeconds();
	_updateTime.restart();

	for(int i = 0; i < _level->Width();i++)
		for(int j = 0;j < _level->Height(); j++)
			if((_level->TileAt(i, j)->GetSpriteID() != SpriteLibrary::AIR))
				_level->TileAt(i, j)->PlayerSight(_player->GetCentre().x, _player->_playerFacing);
	for(std::vector<SpinningObject>::iterator i = _level->_spinningObjects.begin();i!= _level->_spinningObjects.end();i++)
		i->GetGameObject()->PlayerSight(_player->GetCentre().x, _player->_playerFacing);

	if(_died || _goToNextLevel)
	{
		_timeToWait -= _timeSinceLastUpdate;

		if(_timeToWait <= 0)
		{
			if(_died)
			{
				_died = false;
				
				StartLevel();
			}
			if(_goToNextLevel)
			{
				_currentLevel++;
				if(_currentLevel <= TOTAL_LEVELS)
					StartLevel();
				else
					EndGame();
				_goToNextLevel = false;
			}
		}

		return;
	}
	
	switch(_player->checkHearts())
	{
		case 0 :
			_level->SetTileAt(_doori,_doorj,SpriteLibrary::HEART0);
			break;
		case 1:
			_level->SetTileAt(_doori,_doorj,SpriteLibrary::HEART1);
			break;
		case 2:
			_level->SetTileAt(_doori,_doorj,SpriteLibrary::HEART2);
			break;
		case 3:
			_level->SetTileAt(_doori,_doorj,SpriteLibrary::HEART3);
			break;
		case 4:
			_level->SetTileAt(_doori,_doorj,SpriteLibrary::HEART4);
			break;
		case 5:
			_level->SetTileAt(_doori,_doorj,SpriteLibrary::HEART5);
			break;
		case 6:
			_level->SetTileAt(_doori,_doorj,SpriteLibrary::HEART6);
			_level->SetTileAt(_doori,_doorj+1,SpriteLibrary::DOOR_OPEN);
			break;
	}

	//Update player input
	//Input::Update();
	_player->Update(_timeSinceLastUpdate);

	sf::FloatRect spriteSize = SpriteLibrary::GetSprite(0).getLocalBounds();
	sf::Vector2i playerTilePos(int(_player->GetCentre().x / spriteSize.width), int(_player->GetCentre().y / spriteSize.height));

	for(int i = MAX(playerTilePos.x - 2, 0); i < MIN(_level->Width(), playerTilePos.x + 2); i++)
		for(int j = MAX(playerTilePos.y - 2, 0); j < MIN(_level->Height(), playerTilePos.y + 2); j++)
			if(_level->TileAt(i, j)->GetSpriteID() == SpriteLibrary::LADDER)
				if(!_player->_onLadder)
				{
					if(GameObject::CheckCollide(_player, _level->TileAt(i, j)))
					{
						_player->_onLadder = true;
					}
					if(_level->TileAt(i, j-1)->GetSpriteID() == SpriteLibrary::AIR && playerTilePos.y == j-1)
						if(GameObject::CheckVCollideWithVelocity(_player, _level->TileAt(i, j)) && _player->GetVelocity().y < 0)
						{
							_player->VerticalCollision();
						}
				}

	for(int i = MAX(playerTilePos.x - 2, 0); i < MIN(_level->Width(), playerTilePos.x + 2);i++)
	{
		for(int j = MAX(playerTilePos.y - 2, 0);j < MIN(_level->Height(), playerTilePos.y + 2); j++)
		{
			switch(_level->TileAt(i, j)->GetSpriteID())
			{
			case SpriteLibrary::GROUND:
			case SpriteLibrary::DOUBLE_BALL:
			case SpriteLibrary::HEART_AND_BALL:
			case SpriteLibrary::SPIKE_BALL:
			case SpriteLibrary::HEART:
			case SpriteLibrary::FLOOR_LB:
			case SpriteLibrary::FLOOR_LC:
			case SpriteLibrary::FLOOR_RB:
			case SpriteLibrary::FLOOR_RC:
				if(GameObject::CheckVCollideWithVelocity(_player, _level->TileAt(i, j)))
				{
					_player->MoveBy(sf::Vector2f(0.0f,-(_player->GetVelocity().y)*_timeSinceLastUpdate*60));
					_player->VerticalCollision();
				}
				if(GameObject::CheckHCollideWithVelocity(_player, _level->TileAt(i, j), _player->_onLadder))
				{
					_player->MoveBy(sf::Vector2f(-(_player->GetVelocity().x)*_timeSinceLastUpdate*60,(_player->_onLadder ? -2.0f : 0.0f)));
				}
				break;
			case SpriteLibrary::DOOR_OPEN:
				if(GameObject::CheckCollide(_player, _level->TileAt(i, j)))
				{
					if(_player->checkHearts() == 6)
					{
						_goToNextLevel = true;
					}
				}
				break;
			case SpriteLibrary::LAVA_1:
			case SpriteLibrary::LAVA_2:
			case SpriteLibrary::LAVA_3:
			case SpriteLibrary::LAVA_4:
			case SpriteLibrary::LAVA_5:
			case SpriteLibrary::LAVA_6:
				if(GameObject::CheckCollide(_player, _level->TileAt(i, j)))
				{
					_died = true;
					_timeToWait = 1;
				}   
				break;
			case SpriteLibrary::HIT_FROM_ABOVE_GUY:
			case SpriteLibrary::H_SPIKES:
			case SpriteLibrary::H_SPIKES_FLIPPED:
				if(GameObject::CheckVCollideWithVelocity(_player, _level->TileAt(i, j)) && _level->TileAt(i, j)->GetSpriteID() == SpriteLibrary::HIT_FROM_ABOVE_GUY)
				{
					_level->SetTileAt(i, j, SpriteLibrary::AIR);
				}
				else if(GameObject::CheckHCollideWithVelocity(_player, _level->TileAt(i, j)))
				{
					_died = true;
					_timeToWait = 1;
				}
				break;
			case SpriteLibrary::V_SPIKES:
			case SpriteLibrary::HIT_FROM_SIDE_GUY:
				if(GameObject::CheckHCollideWithVelocity(_player, _level->TileAt(i, j)) && _level->TileAt(i, j)->GetSpriteID() == SpriteLibrary::HIT_FROM_SIDE_GUY)
				{
					_level->SetTileAt(i, j, SpriteLibrary::AIR);
					
				}else if(GameObject::CheckVCollideWithVelocity(_player, _level->TileAt(i, j)))
				{
					_died = true;
					_timeToWait = 1;
				} 
				break;
			}
		}
	}

	for(std::vector<SpinningObject>::iterator i = _level->_spinningObjects.begin();i!= _level->_spinningObjects.end();i++)
	{
		if((GameObject::CheckCollide(_player, i->GetGameObject())))
		{
			if(i->GetGameObject()->GetSpriteID() == SpriteLibrary::HEART_END)
			{
				i->GetGameObject()->SetSpriteID(SpriteLibrary::AIR);
				_player->addHeart();
				printf("Hearts: %d\n",_player->checkHearts());
			}
			if(i->GetGameObject()->GetSpriteID() == SpriteLibrary::SPIKE_END)
			{
				_died = true;
				_timeToWait = 1;
			}
		}
	}

	_level->Update(_timeSinceLastUpdate);
	if(_level->TimeUp())
	{
		_died = true;
		_timeToWait = 1.0f;
	}

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
	fps.setFont(_font);
	fps.setPosition(_player->GetCentre() + sf::Vector2f(-380, -280));
	fps.setColor(sf::Color::Black);
	_window->draw(fps);

	sf::Text levelTime;
	std::stringstream lvlSS;
	lvlSS << int(_level->TimeRemaining());
	lvlSS << "s";
	levelTime.setString(lvlSS.str());
	levelTime.setFont(_font);
	levelTime.setOrigin(levelTime.getLocalBounds().width / 2, levelTime.getLocalBounds().height / 2);
	levelTime.setPosition(_player->GetCentre() + sf::Vector2f(0, -260));// + sf::Vector2f(-levelTime.getLocalBounds().width/2, -260-levelTime.getLocalBounds().height/2));
	levelTime.setColor(_level->TimeRemaining() >= 10 ? sf::Color::Black : sf::Color::Red);

	sf::Sprite levelTimeBG = SpriteLibrary::GetSprite(SpriteLibrary::LEVEL_TIMER_BG);
	levelTimeBG.setOrigin(levelTimeBG.getLocalBounds().width/2, levelTimeBG.getLocalBounds().height/2);
	levelTimeBG.setPosition(_player->GetCentre() + sf::Vector2f(0, -252));
	levelTimeBG.setPosition(int(levelTimeBG.getPosition().x), int(levelTimeBG.getPosition().y));

	_window->draw(levelTimeBG);
	_window->draw(levelTime);

    _window->display();
}

void Application::SplashScreen()
{
	_window->clear(sf::Color(255, 0, 255, 255));
	sf::Sprite mySplash = SpriteLibrary::GetSprite(SpriteLibrary::SPLASH);
	_window->draw(mySplash);
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
			if(_level->TileAt(i, j)->GetSpriteID() == SpriteLibrary::DOOR)
			{
				_level->TileAt(i,j-1)->SetSpriteID(SpriteLibrary::HEART0);
				_doori = i;
				_doorj = j-1;
			
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
	/*delete _window;
	delete _level;
	delete _player;
	delete _camera;
	delete _font;*/
}
