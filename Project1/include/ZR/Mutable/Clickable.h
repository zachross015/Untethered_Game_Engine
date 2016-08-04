#ifndef CLICKABLE_H
#define CLICKABLE_H
#include <SFML/Graphics.hpp>
#include <ZR/FunctionHolder.h>

namespace zr
{
	/////////////////////////////////////////////////////////////////////////////////
	// The purpose of this class is to provide a collection of methods that simplify
	// the process of making interactable objects.
	//
	// Copyright © 2016 Zachary Ross. All rights reserved.
	/////////////////////////////////////////////////////////////////////////////////
	class Clickable : public sf::Transformable
	{
	public:
		//
		// Default class constructor
		//
		Clickable();

		//
		// Default class deconstructor
		//
		~Clickable();

		//
		// Function that returns whether or not the player
		// has clicked within the bounds of this entity
		//
		bool clickedInBounds();


		//
		// FunctionHolder for functions that deal with click events
		//
		FunctionHolder<void(*)(Clickable*)> clickFunctions;
	
		//
		// Function that runs all functions that are stored in clickFunctions
		//
		void runClickFunctions();

	protected:
		float *width, *height;
	};
}

#endif