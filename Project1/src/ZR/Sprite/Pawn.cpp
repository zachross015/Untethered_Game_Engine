#include <ZR/Sprite/Pawn.h>


namespace zr
{
	Pawn::Pawn()
	{
	}


	Pawn::~Pawn()
	{
	}

	void Pawn::update(sf::Time dT)
	{
		Actor::update(dT);
		sf::Vector2f movement;
		float moveSpeed = 60.f;
		if (upPressed) movement.y -= moveSpeed * dT.asSeconds();
		if (downPressed) movement.y += moveSpeed * dT.asSeconds();
		if (leftPressed) movement.x -= moveSpeed * dT.asSeconds();
		if (rightPressed) movement.x += moveSpeed * dT.asSeconds();
		move(movement);
	}

	void Pawn::handleEvent(sf::Event & e)
	{
		Actor::handleEvent(e);
		if (e.type == sf::Event::KeyPressed)
		{
			if (e.key.code == sf::Keyboard::Up)
				upPressed = true;
			else if (e.key.code == sf::Keyboard::Down)
				downPressed = true;
			else if (e.key.code == sf::Keyboard::Left)
				leftPressed = true;
			else if (e.key.code == sf::Keyboard::Right)
				rightPressed = true;
		}
		else if (e.type == sf::Event::KeyReleased)
		{
			if (e.key.code == sf::Keyboard::Up)
				upPressed = false;
			else if (e.key.code == sf::Keyboard::Down)
				downPressed = false;
			else if (e.key.code == sf::Keyboard::Left)
				leftPressed = false;
			else if (e.key.code == sf::Keyboard::Right)
				rightPressed = false;
		}
	}

	void Pawn::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		Actor::draw(target, states);
	}
}