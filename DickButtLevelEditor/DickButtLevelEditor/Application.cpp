#include "Application.h"


Application::Application(void)
{
	window = new sf::RenderWindow(sf::VideoMode(800, 600), "Team Sneaky Juice Level Editor");

	SpriteLibrary::Initialise();

	gameEnded = false;
	mouseDown = false;

	std::ifstream myReadFile;
	myReadFile.open("levelDetails.txt");
	std::getline(myReadFile, fileName);
	std::string width;
	std::getline(myReadFile, width);
	std::string height;
	std::getline(myReadFile, height);

	mapGrid = new MapGrid(fileName, atoi(width.c_str()), atoi(height.c_str()));
	
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
    sf::Event event;
    while (window->pollEvent(event))
    {
		switch(event.type)
		{
		case sf::Event::Closed:
			gameEnded = true;
			break;
		case sf::Event::MouseButtonPressed:
			mouseDown = true;
			tileGrid.Click(event.mouseButton);
			mapGrid->Click(event.mouseButton.x, event.mouseButton.y, tileGrid.CurrentTile());
			break;
		case sf::Event::MouseButtonReleased:
			mouseDown = false;
			break;
		case sf::Event::MouseMoved:
			if(mouseDown)
				mapGrid->Click(event.mouseMove.x, event.mouseMove.y, tileGrid.CurrentTile());
		}
    }

}

void Application::Draw()
{
    window->clear(sf::Color(255, 255, 255, 255));

	mapGrid->Draw(window);
	tileGrid.Draw(window);

    window->display();
}

Application::~Application(void)
{
	delete mapGrid;
	delete window;
}
