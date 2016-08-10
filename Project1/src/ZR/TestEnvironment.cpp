#include <ZR/GameResources/Resources.h>
#include <ZR/GUI/ButtonNode.h>
#include <iostream>
#include <random>

using namespace zr;
sf::Music m;

void Test()
{
	CurrentScene = new Scene("awakening");
	TextNode *tn = new TextNode();
	tn->setText("<text va = 'middle' ha = 'middle' pos = '(800,450)'><style color = 'black'>ch.1</style><style size = '100' color = 'black'>awakening</style></text>");
	CurrentScene->GUI->addNode(tn);
}