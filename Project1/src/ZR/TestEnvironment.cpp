#include <ZR/GameResources/Resources.h>
#include <ZR/GUI/ButtonNode.h>
#include <iostream>
#include <random>

using namespace zr;
sf::Music m;

void Test()
{
	CurrentScene = new Scene();
	GUIOverlay *gui = new GUIOverlay();
	gui->loadFromFile("guitest.xml");
	CurrentScene->GUI = gui;
}