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
	tn->setText("<style size = '10'>hp </style><style size = '30'>99/100</style>");
	tn->setVerticalAlign(zr::VerticalAlign::Middle);
	tn->setLineWidth(600.f);
	tn->setPosition({ 20,20 });
	gui->addNode(tn);
	CurrentScene->GUI = gui;

	Actor *a = new Actor();
	a->addAnimation("default",&Animations.get("Projectile_Fire"));
	a->setCurrentAnimation("default");
	a->collisionFunctions.add([](CollisionObject*, CollisionObject*) {std::cout << "hello"; });
	a->setScale({ 4,4 });
	CurrentScene->addObject(a);

	Actor *b = new Actor();
	b->addAnimation("default", &Animations.get("X_up"));
	b->setCurrentAnimation("default");
	b->setScale({ 4,4 });
	b->setPosition({ 64,64 });
	CurrentScene->addObject(b);
}