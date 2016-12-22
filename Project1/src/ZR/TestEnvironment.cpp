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
	float scale;
	scale = 6;
	a->addAnimation("down", &Animations.get("ddown"));
	a->addAnimation("up", &Animations.get("dup"));
	a->addAnimation("left", &Animations.get("dleft"));
	a->addAnimation("right", &Animations.get("dright"));
	a->setCurrentAnimation("down");
	a->setPosition({1700,500});
	a->setScale({ scale, scale });
	a->setMovementType(zr::Movement::ConstVel);

	a->updateFunctions.add([a](sf::Time)
	{
		sf::Vector2f movement {0,0};
		float speed = 400;
		std::string animName = "";
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			movement.x -= speed;
			animName = "left";
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			movement.x += speed;
			animName = "right";
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			movement.y -= speed;
			animName = "up";
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			movement.y += speed;
			animName = "down";
		}
		sf::Vector2f s = a->getMovementSpeed();
		a->setMovementSpeed(movement);
		if (animName != "" && s != movement)
			a->setCurrentAnimation(animName);
	});

	a->eventFunctions.add([a](sf::Event &e) 
	{
		if (e.type == sf::Event::KeyReleased)
			a->getCurrentAnimation()->stop();
		if (e.type == sf::Event::KeyPressed)
			a->getCurrentAnimation()->play();
	});

	a->collisionFunctions.add([a](CollisionObject *c, CollisionObject *) 
	{
			a->goToPreviousPosition();
			a->setMovementSpeed({ 0,0 });
			std::cout << "Collisions" << std::endl;
	});

	CollisionObject *c = new CollisionObject();
	c->setPosition({ 0,0 });
	c->addPolygon({ {0,0},{1,0}, {1,16}, {0,16 } });
	c->setScale({ 64,64	 });
	CurrentScene->addCollidableObject(c);
	c->collisionFunctions.add([](CollisionObject *, CollisionObject *)
	{
		std::cout << "Collisions" << std::endl;
	});


	CurrentScene->addObject(a);
}