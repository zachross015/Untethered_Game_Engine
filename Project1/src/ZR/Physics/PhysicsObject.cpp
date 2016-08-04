#include <ZR/Physics/PhysicsObject.h>
#include <SFML/Graphics.hpp>

namespace zr
{
	PhysicsObject::PhysicsObject()
	{
	}
	PhysicsObject::~PhysicsObject()
	{
	}
	void PhysicsObject::update(sf::Time dT)
	{
		velocity += acceleration;
		if (velocity.x > 0.f) velocity.x -= (friction);
		else if (velocity.x < 0.f) velocity.x += (friction);
		if (velocity.y > 0.f) velocity.y -= (friction);
		else if (velocity.y < 0.f) velocity.y += (friction);

		if (velocity.y > -friction && velocity.y < friction) velocity.y = 0;
		if (velocity.x > -friction && velocity.x < friction) velocity.x = 0;

		move(velocity * dT.asSeconds());
	}
}