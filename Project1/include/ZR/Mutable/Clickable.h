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
		// Function that sets the bounding rectangle for the object
		// @param f is the width and height of the rectangle
		//
		void setSize(sf::Vector2f &f) { width = f.x; height = f.y; }


		//
		// FunctionHolder for functions that deal with click events
		//
		FunctionHolder<void(*)(Clickable*)> clickFunctions;
	
		//
		// Function that runs all functions that are stored in clickFunctions
		//
		void runClickFunctions();

	protected:
		float width = 0, height = 0;
	};
}

#endif