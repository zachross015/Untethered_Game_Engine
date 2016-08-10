#ifndef STATICACTOR_H
#define STATICACTOR_H
#include <SFML/Graphics.hpp>
#include <ZR/Physics/CollisionObject.h>
namespace zr
{
	class StaticActor
		: public sf::Sprite
		, public zr::CollisionObject
	{
	public:
		StaticActor();
		~StaticActor();

		//
		// Function that sets the scale of the Actor's sprite being displayed
		// @param s is the scale to set the object to
		//
		void setScale(sf::Vector2f s);

		//
		// Functions that sets the origin of the Actor's sprite. This is used
		// for determining all translation based changes to the Actor's sprite
		// @param f is the coordinates to set the origin to relative to the sprite
		//
		void setOrigin(sf::Vector2f f);

		//
		// Function that set the rotation of the Actor's sprite
		// @param angle sets the current angle of the Actor's sprite
		//
		void setRotation(float angle);

		//
		// Function that sets the rotation of the Actor's sprite relative to the current angle
		// @param angle sets the current angle of the Actor's sprite relative to the current angle
		//
		void rotate(float angle);

		//
		// Fuction that sets the current position of the Actor's sprite
		// @param pos is the position to which the Actor's sprite will be set to
		//
		void setPosition(sf::Vector2f pos);

		//
		// Function that retrieves the current position of the actor
		// @result returns the current position
		//
		sf::Vector2f getPosition();

		//
		// Function that retrieves the current scale of the actor
		// @result returns the current scale
		//
		sf::Vector2f getScale();

		//
		// Function that retrieves the current rotation of the actor
		// @result returns the current rotation
		//
		float getRotation();

		//
		// Function that retrieves the current origin of the actor
		// @result returns the current origin
		//
		sf::Vector2f getOrigin();
		
	};
}
#endif
