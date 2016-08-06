#include <ZR/GameResources/Resources.h>
#include <ZR/GUI/ButtonNode.h>
#include <iostream>
#include <random>

using namespace zr;

void Test()
{
	CurrentScene = new Scene();
	GUIOverlay *gui = new GUIOverlay();
	gui->loadFromFile("guitest.xml");

	ButtonNode *tn2 = new ButtonNode();
	//tn2->setPadding({ 10,10,10,10 });
	//tn2->hoverFunctions.add([](zr::Hoverable*) {std::cout << "Hover" << std::endl; });
	//tn2->clickFunctions.add([](zr::Clickable*) {std::cout << "Click" << std::endl; });

	CurrentScene->GUI = gui;
}