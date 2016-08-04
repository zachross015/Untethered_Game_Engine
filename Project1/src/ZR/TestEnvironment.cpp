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
	tn->setText("<style size = '30'>hello </style><style size = '20'>world. </style><style size = '15'>my name is </style><style>zach</style>");
	tn->setLineWidth(400.f);
	tn->setHorizantalAlign(zr::HorizantalAlign::Right);
	tn->setVerticalAlign(zr::VerticalAlign::Bottom);
	gui->addNode(tn);
	CurrentScene->GUI = gui;
}