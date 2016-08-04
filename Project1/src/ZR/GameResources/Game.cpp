//
//  Game.cpp
//
//
//  Created by Zachary Ross on 7/10/15.
//
//
#include <ZR/GameResources/Game.h>
#include <fstream>
extern void Test();

Game::Game()
{
	Window->setFramerateLimit(60.f);
	loadResources();
	Test();
}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    const sf::Time TimePerFrame = sf::seconds(1.f/60.f);
    
    while(Window->isOpen())
    {
        processEvents();
        timeSinceLastUpdate += clock.restart();
        while(timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }
        
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
	
    while(Window->pollEvent(event))
    {
        switch (event.type) {
            case sf::Event::Closed:
                Window->close();
                break;
            case sf::Event::Resized:
                break;
            case sf::Event::MouseButtonPressed:
                break;
            default:
                break;
        }
		CurrentScene->handleEvent(event);
    }
}

void Game::update(sf::Time deltaTime)
{
	CurrentScene->update(deltaTime);
}

void Game::render()
{
    Window->clear();
	Window->draw(*CurrentScene);
    Window->display();
}

void Game::loadResources()
{
	std::ifstream s;
	s.open("assets/assets.txt");
	if (!s.fail())
	{
		while (!s.eof())
		{
			std::string type, name, path;
			s >> type >> name >> path;
			if (type == "Texture")
				Textures.load(name, path);
			else if (type == "Font")
				Fonts.load(name, path);
			else if (type == "Sound")
				Sounds.load(name, path);
			else if (type == "Animation")
				Animations.load(name, path);
		}
	}
	else
	{
		throw std::runtime_error("Game::loadResources - failed to open resource file");
	}
	s.close();
}
