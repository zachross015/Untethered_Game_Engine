//
//  Game.cpp
//
//
//  Created by Zachary Ross on 7/10/15.
//
//
#include <ZR/GameResources/Game.h>
#include <fstream>

#if defined(_DEBUG) || defined(NDEBUG) || defined(DEBUG)
extern void Test();
#endif

Game::Game()
{
	Window->setFramerateLimit(120.f);
	Window->setKeyRepeatEnabled(false);
	#if defined(_DEBUG) || defined(NDEBUG) || defined(DEBUG)
	Test();
	#endif
}

void Game::run()
{
	
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    const sf::Time TimePerFrame = sf::seconds(1.f/120.f);
	update(TimePerFrame);
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

