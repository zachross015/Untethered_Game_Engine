#include <ZR/GameResources/Resources.h>
#include <ZR/GUI/ButtonNode.h>
#include <iostream>
#include <random>

using namespace zr;

void Test()
{
	CurrentScene = new Scene();
	GUIOverlay *gui = new GUIOverlay();
	TextNode *tn = new TextNode();
	tn->setText("<style size = '10'>hp </style><style color = 'blue' size = '30'>99/100</style>");
	tn->setVerticalAlign(zr::VerticalAlign::Middle);
	tn->setLineWidth(600.f);
	tn->setPosition({ 20,20 });
	gui->addNode(tn);

	ButtonNode *tn2 = new ButtonNode();
	tn2->setText("<style size = '30' color = 'rgba(255,0,0,150)'>99/100</style><style size = '10'> hp my name is mister mesinks blah bla asdf asdf asdfa sf</style>");
	tn2->setBackgroundColor(sf::Color::Blue);
	tn2->setVerticalAlign(zr::VerticalAlign::Middle);
	tn2->setHorizantalAlign(zr::HorizantalAlign::Right);
	tn2->setLineWidth(200.f);
	tn2->setPosition({ 1340,20 });
	tn2->setSpaceSize(10);
	//tn2->setLineHeight(100);
	gui->addNode(tn2);

	CurrentScene->GUI = gui;
}