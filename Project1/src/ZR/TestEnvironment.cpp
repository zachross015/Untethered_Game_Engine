#include <ZR/GameResources/Resources.h>
#include <ZR/GUI/ButtonNode.h>
#include <iostream>
#include <random>

using namespace zr;
sf::Music m;

void Test()
{
	CurrentScene = new Scene("awakening");

	Actor *a = new Actor();
	sf::Vector2f pos;
	float scale;
	pos.x = rand() % 1600;
	pos.y = rand() % 900;
	scale = 4;
	a->addAnimation("down", &Animations.get("X_down"));
	a->setCurrentAnimation("down");
	//a->setPosition(pos);
	a->setScale({ scale, scale });
	a->setMovementType(zr::Movement::ConstVel);

	a->updateFunctions.add([](zr::Drawable *d, sf::Time)
	{
		if (Actor *b = dynamic_cast<Actor*>(d))
		{
			sf::Vector2f movement {0,0};
			float speed = 400;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) movement.x -= speed;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) movement.x += speed;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) movement.y -= speed;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) movement.y += speed;
			b->setMovementSpeed(movement);
		}
	});

	a->collisionFunctions.add([](CollisionObject *c, CollisionObject *) 
	{
		if (Actor *a = dynamic_cast<Actor*>(c))
		{
			a->goToPreviousPosition();
			a->setMovementSpeed({ 0,0 });
		}
	});

	CurrentScene->addObject(a);

	TextNode *tn = new TextNode();
	tn->setText("<text va = 'middle' ha = 'middle' pos = '(800,450)'><style color = 'black'>ch.1</style><style size = '100' color = 'black'>"+CurrentScene->getSceneName()+"</style></text>");
	CurrentScene->GUI->addNode(tn);
}