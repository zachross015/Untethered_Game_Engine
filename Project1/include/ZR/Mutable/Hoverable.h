#ifndef HOVERABLE_H
#define HOVERABLE_H
#include <SFML/Graphics.hpp>
#include <ZR/FunctionHolder.h>
/////////////////////////////////////////////////////////////////////////////////
// The purpose of this class is to provide a mutable class that handles
// hover based functions
//
// Copyright � 2016 Zachary Ross. All rights reserved.
/////////////////////////////////////////////////////////////////////////////////

namespace zr
{
	class Hoverable : public sf::Transformable
	{
	public:
        
        //
        // Default class constructor
        //
		Hoverable();
        
        //
        // Default class deconstructor
        //
		~Hoverable();

        //
        // Function that returns a boolean whether or not the mouse is
        // currently hovering over this object
        // @result returns a bool if the mouse is inside the object
        //
		bool isHovering() const;
        
        //
        // Function that sets the bounding rectangle for the object
        // @param f is the width and height of the rectangle
        //
		void setSize(sf::Vector2f &f) { *width = f.x; *height = f.y; }
        
        // A function holder for all functions to be ran when this object is hovered on
		FunctionHolder<void(*)(Hoverable*)> hoverFunctions;

        //
        // Function that runs all functions in hoverFunctions
        //
		void runHoverFunctions();
	protected:
		float *width, *height;
	};
}

#endif