#include <ZR/GameResources/Game.h>
#include <iostream>

#if defined(_DEBUG) || defined(NDEBUG) || defined(DEBUG)
int main()
{
	Window = new sf::RenderWindow(sf::VideoMode(1600, 900, 32), "SFML Game");
	Game game;
	game.run();
}
#endif