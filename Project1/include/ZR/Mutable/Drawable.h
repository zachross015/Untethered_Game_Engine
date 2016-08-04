#ifndef DRAWABLE_H
#define DRAWABLE_H
#include <SFML/Graphics.hpp>
#include <ZR/Counter.h>
#include <ZR/FunctionHolder.h>

namespace zr
{
	/////////////////////////////////////////////////////////////////////////////////
	// The purpose of this class is to provide a base class for all
	// entites drawn on to the screen. This class's functions are necessary for
	// each class as a way to organize different types of actions during the draw event
	//
	// Copyright © 2016 Zachary Ross. All rights reserved.
	/////////////////////////////////////////////////////////////////////////////////

	class Drawable :
		public sf::Drawable
	{
	public:

		//
		// Default class constructor
		//
		Drawable();

		//
		// Default class deconstructor
		//
		~Drawable();

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
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;

		//
		// FunctionHolder for all functions that require an event to occure
		//
		FunctionHolder<void(*)(Drawable*, sf::Event)> eventFunctions;
		
		//
		// FunctionHolder for all functions that should be updated every frame
		//
		FunctionHolder<void(*)(Drawable*, sf::Time)> updateFunctions;

		//
		// FunctionHolder for functions that will occur after a set amount of time
		//
		FunctionHolder < std::pair<void(*)(Drawable*, sf::Time), Counter>> delayedFunctions;

	};
}

#endif