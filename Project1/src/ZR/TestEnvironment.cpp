#include <ZR/GameResources/Resources.h>
#include <ZR/GUI/TextNode.h>
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

	TextNode *tn2 = new TextNode();
	tn2->setText("<style size = '30' color = 'red'>99/100</style><style size = '10'> hp</style>");
	tn2->setVerticalAlign(zr::VerticalAlign::Middle);
	tn2->setHorizantalAlign(zr::HorizantalAlign::Right);
	tn2->setLineWidth(200.f);
	tn2->setPosition({ 1380,20 });
	gui->addNode(tn2);

	CurrentScene->GUI = gui;
}