#ifndef PHYSICSVARIABLES_H
#define PHYSICSVARIABLES_H
#include <SFML/Graphics.hpp>
namespace zr
{
	struct PhysicsVariables
	{
		static float gravity;
		static float friction;
		float mass;
		sf::Vector2f velocity = { 0,0 };
		sf::Vector2f acceleration = { 0,0 };
		float inertia;
	};
}
#endif