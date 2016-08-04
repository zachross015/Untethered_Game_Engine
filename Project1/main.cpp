#include <ZR/GameResources/Game.h>
#include <iostream>
int main()
{
	Window = new sf::RenderWindow(sf::VideoMode(1600, 900, 32), "SFML Game");
	std::cout << "" << std::endl;
	Game game;
	game.run();
}
