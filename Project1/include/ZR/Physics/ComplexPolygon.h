#ifndef COMPLEXPOLYGON_H
#define COMPLEXPOLYGON_H
#include <SFML/Graphics.hpp>
#include <ZR/Physics/Range.h>

namespace zr
{
	/////////////////////////////////////////////////////////////////////////////////
	// The purpose of this class is to create an organized structure for multiple
	// polygons within one polygon
	//
	// Copyright � 2016 Zachary Ross. All rights reserved.
	/////////////////////////////////////////////////////////////////////////////////
	class ComplexPolygon
	{
	public:
        //
        // Default class constructor
        //
		ComplexPolygon();
        
        //
        // Default class deconstructor
        //
		~ComplexPolygon();
        
        //
        // Function that returns the convex shape at the index given
        // @param index is the index of the polygon to be retrieved
        // @result returns a pointer to the convex shape
        //
		sf::ConvexShape getShape(int index) { return polygons[index]; }
        
        //
        // Function that returns the convex shape at the index given
        // @param index is the index of the polygon to be retrieved
        // @result returns a pointer to the convex shape
        //
		sf::ConvexShape getShape(int index) const { return polygons[index]; }

		//
		// Function that gets the rectangle encasing the complex polygon
		// @result returns the rectangle used for the complex shape
		//
		sf::FloatRect getLocalBounds();

		//
		// Function that gets the rectangle encasing the complex polygon with
		// all translations
		// @result returns the rectangle used for the complex shape
		//
		sf::FloatRect getGlobalBounds();
        
        //
        // Function that gets the amount of individual polygons within the
        // complex polygon
        // @result returns an int of the amount of polygons
        //
		int getPolygonCount() { return polygons.size(); }
        
        //
        // Function that gets the amount of individual polygons within the
        // complex polygon
        // @result returns an int of the amount of polygons
        //
		int getPolygonCount() const { return polygons.size(); }
        
        //
        // Function that sets the scale of each polygon
        // @param s is the x and y scale to set the polygon to
        //
		void setScale(sf::Vector2f s);
        
        //
        // Function that sets the current position of each of the polygons
        // @param pos is the position to set the polygons to
        //
		void setPosition(sf::Vector2f pos);

		//
		// Function that sets the position relative to the current position of the object
		// @param pos is the position to be moved to
		//
		void move(sf::Vector2f pos);
        
        //
        // Function that sets the origin of each polygon
        // @param orig is the position to set the origin of the polygon
        //
		void setOrigin(sf::Vector2f orig);
        
        //
        // Function that sets the rotation of each polygon
        // @param angle is the angle to set the rotation to
        //
		void setRotation(float angle);
        
        //
        // Function that sets the rotation of each polygon relative to the
        // current rotation
        // @param angle is the angle to move the polygon by
        //
		void rotate(float angle);
        
        //
        // Function that sets the fill color of each polygon
        // @param r is the color to set the polygons to
        //
		void setFillColor(sf::Color r);
        
        //
        // Function that returns the current color being used by the polygons
        // @result returns the color being used
        //
		sf::Color getFillColor();
        
        //
        // Function that adds a polygon to the vector of polygons given a system
        // of coordinates
        // @param vec is the vector of coordinates for the polygon
        //
		void addPolygon(std::vector<sf::Vector2f> vec);
        
        //
        // Function that sets a polygon to the vector of polygons given a system
        // of coordinates and the index of the polygon to be changed
        // @param index is the index of the polygon to be changed
        // @param vec is the vector of coordinates for the polygon
        //
		void setPolygonAtIndex(int index, std::vector<sf::Vector2f> vec);

	protected:
		std::vector<sf::ConvexShape> polygons;
	};
}

#endif