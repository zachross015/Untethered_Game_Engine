#ifndef ACTOR_H
#define ACTOR_H
#include <ZR/Physics/PhysicsObject.h>
#include <ZR/Sprite/Animation.h>
#include <ZR/Mutable/Hoverable.h>
#include <ZR/Mutable/Clickable.h>

namespace zr
{

	namespace Movement
	{
		enum Type
		{
			ConstAccl,              // Constant Acceleration
			ConstVel                // Constant Velocity
		};
	}

	/////////////////////////////////////////////////////////////////////////////////
	// The purpose of this class is to provide a collection of classes
	// to make an entity that can be moved around, animated, and interacted with on the screen.
	//
	// Copyright © 2016 Zachary Ross. All rights reserved.
	/////////////////////////////////////////////////////////////////////////////////
	class Actor :
    public Drawable, public PhysicsVariables, public CollisionObject
	{
	public:
		//
		// Default class constructor
		//
		Actor();
		//
		// Default class deconstructor
		//
		~Actor();

		//
		// Function called every frame that is meant to handle frame based
		// movements and updates in translations.
		// @param dT is the delta time, or time between each frame.
		//
		virtual void update(sf::Time dT);

		//
		// Function called every frame that is meant to handle frame based
		// event occurences such as key presses or button presses
		// @param e is a reference to the event that has occurred
		//
		virtual void handleEvent(sf::Event &e);

		//
		// Function called every frame that is meant to handle frame based
		// drawing to the screen
		// @param target is a reference to the RenderWindow that sf::Drawable objects
		// are drawn to
		// @param states is the states that the RenderWindow contains
		//
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

		//
		// Function that adds an animation to a map containing all animations
		// for this actor.
		// @param identifier is the string used as an identifier for the animation
		// @param anim is a pointer to the animation being added to the map
		//
		void addAnimation(std::string identifier, Animation *anim);

		//
		// Function that sets the current active animation to the animation
		// equal to the identifier
		// @param identifier is the identifier used to get the animation
		//
		void setCurrentAnimation(std::string identifier);

		//
		// Function that gets the current animation being used by the Actor
		// @result returns the current animation
		//
		Animation *getCurrentAnimation() { return currentAnimation; }

		//
		// Function that sets the scale of the Actor's sprite being displayed
		// @param s is the scale to set the object to
		//
        virtual void setScale(sf::Vector2f s);

		//
		// Functions that sets the origin of the Actor's sprite. This is used
		// for determining all translation based changes to the Actor's sprite
		// @param f is the coordinates to set the origin to relative to the sprite
		//
        virtual void setOrigin(sf::Vector2f f);

		//
		// Function that set the rotation of the Actor's sprite
		// @param angle sets the current angle of the Actor's sprite
		//
		virtual void setRotation(float angle);

		//
		// Function that sets the rotation of the Actor's sprite relative to the current angle
		// @param angle sets the current angle of the Actor's sprite relative to the current angle
		//
		virtual void rotate(float angle);

		//
		// Fuction that sets the current position of the Actor's sprite
		// @param pos is the position to which the Actor's sprite will be set to
		//
		virtual void setPosition(sf::Vector2f pos);

		//
		// Function that returns the Actor's sprite to the previous position recorded
		//
		void goToPreviousPosition();

		//
		// Fuction that sets the current position of the Actor's sprite relative to
		// the current position
		// @param pos is the position to which the Actor's sprite will be moved to
		//
		virtual void move(sf::Vector2f pos);

		//
		// Function that sets the movement speed (which can be velocity or acceleration)
		// of the Actor and all underlying classes
		// @param amt is the amount to set the speed to
		//
		void setMovementSpeed(sf::Vector2f amt);

		//
		// Function that sets the current movement type of the Actor
		// @param t is the type of movement, the current options are
		// constant velocity or constant acceleration
		//
		void setMovementType(Movement::Type t);

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

		//
		// Function that retrieves the current movement speed of the actor
		// @result returns the current movement speed
		//
		sf::Vector2f getMovementSpeed();

	private:
		std::map<std::string, Animation *> animations;
		Animation *currentAnimation;
		CollisionObject **currentBounds;
		bool collision = false;
		bool animationIsBounded = false;
		Movement::Type type = Movement::ConstAccl;
        sf::Vector2f previousPos = { 0,0 };
	};
}
#endif
