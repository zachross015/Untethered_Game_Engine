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
		a->setMovementSpeed(movement);
		if (animName != "")
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
	});

	zr::TextBox *tb = new zr::TextBox();
	std::string text = "Hello my name is </style><style size = '100' font = 'distorted'>billy joe</style><style> and </style><style size = '40'>i am pc</style><style> and extremely triggered and outraged by the fact that women dont get to decide whether or not they want to be alive and working and asdf yeada";
	tb->setSpaceSize(20);
	tb->setText("<textbox pos = '(5,700)' lw = '1590' va = 'middle' ha = 'middle' bgcolor = 'black' olcolor = 'white' olthk = '0'><style>" + text + "</style></textbox>");
	CurrentScene->GUI->addNode(tb);

	CurrentScene->addObject(a);
}