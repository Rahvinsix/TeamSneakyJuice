#include "Application.h"


Application::Application(void)
{
	window = new sf::RenderWindow(sf::VideoMode(800, 600), "Team Sneaky Juice");

	SpriteLibrary::Initialise();
	Input::Initialise();
	level = new LevelClass();
	player = new Player();
	gameEnded = false;
	
    while (window->isOpen())
    {
		Update();
		Draw();

		if(gameEnded)
			window->close();
    }
}

void Application::Update()
{
	//Update player input
	Input::Update();
	player->Update();

	for(int i = 0; i < 10;i++)
	{
		for(int j = 0;j < 10; j++)
		{
			if(level->levelGrid[i][j].GetSpriteID() == SpriteLibrary::GROUND)
			{
				int collisionType = GameObject::CheckCollideWithVelocity(player, &level->levelGrid[i][j]);
				switch(collisionType)
				{
				case GameObject::H_COLLISION:
					player->MoveBy(sf::Vector2f(-(player->GetVelocity().x),0.0f));
					printf("H_COLLIDE");
					break;
				case GameObject::V_COLLISION:
					player->SetVelocity(sf::Vector2f(player->GetVelocity().x,0.0f));
					break;
				}
			}
		}
	}
	
    sf::Event event;
    while (window->pollEvent(event))
    {
		switch(event.type)
		{
		case sf::Event::Closed:
			gameEnded = true;
			break;
		case sf::Event::KeyPressed:
			Input::KeyPressed(event.key.code);
			break;
		case sf::Event::KeyReleased:
			Input::KeyReleased(event.key.code);
			break;
		}
    }

}

void Application::Draw()
{
    window->clear(sf::Color(255, 255, 255, 255));
	level->Draw(window);
	player->Draw(window);
    window->display();
}

Application::~Application(void)
{
	delete window;
	delete level;
}
