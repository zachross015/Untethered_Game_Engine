#ifndef COLLISIONOBJECT_H
#define COLLISIONOBJECT_H
#include <ZR/Physics/Range.h>
#include <ZR/Physics/ComplexPolygon.h>
#include <ZR/Physics/PhysicsVariables.h>
#include <ZR/FunctionHolder.h>
#include <vector>

namespace zr
{
	/////////////////////////////////////////////////////////////////////////////////
	// The purpose of this class is to create an inheritable class
	// that handles all physics based items
	//
	// Copyright � 2016 Zachary Ross. All rights reserved.
	/////////////////////////////////////////////////////////////////////////////////
	class CollisionObject
		: public sf::Transformable,
		  public ComplexPolygon
	{
	public:
        //
        // Default class constructor
        //
		CollisionObject();

		//
		// Copy constructor
		// @param other is the other CollisionObject to copy from
		//
		CollisionObject(CollisionObject *other);
        
        //
        // Default class deconstructor
        //
		~CollisionObject();
        
        //
        // Function that tests whether or not another PhysicsObject is within
        // the bounds of this objects bounding rectangle
        // @param po is a pointer to the object to be checked against
        //
		bool simpleCollision(CollisionObject *po);
        
        //
        // Function utilizing the seperate axis theorem to determine whether or
        // not there is a collision between two polygons
        // @param o is a pointer to the other polygon
        // @param index is the index of the polygon to be tested in this object
        // @param index2 is the index of the polygon to be tested in the othe object
        //
		bool collision(CollisionObject *o, int index, int index2);

        //
        // Function that runs all collision functions in collisionFunctions
        // @param otherObj is a pointer to the other PhysicsObject so that
        // a collision with this object can change what happens to the other object
        // on collision
        //
		void runCollisionFunctions(CollisionObject *otherObj);

        //
        // Function that sets the scale of the object being displayed
        // @param s is the scale to set the object to
        virtual void setScale(sf::Vector2f s);
        
        //
        // Fuction that sets the current position of the object
        // @param pos is the position to which the object will be set to
        //
        virtual void setPosition(sf::Vector2f pos);

		//
		// Function that sets the position relative to the current position of the object
		// @param pos is the position to be moved to
		//
		virtual void move(sf::Vector2f pos);
        
        //
        // Functions that sets the origin of the object. This is used
        // for determining all translation based changes to the object
        // @param f is the coordinates to set the origin to relative to the object
        //
        virtual void setOrigin(sf::Vector2f f);
        
        //
        // Function that set the rotation of the object
        // @param angle sets the current angle of the object
        //
        virtual void setRotation(float angle);
        
        //
        // Function that sets the rotation of the object relative to the current angle
        // @param angle sets the current angle of the object relative to the current angle
        //
        virtual void rotate(float angle);

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
        // Function that adds a polygon from a list of coordinates to the current vector
        // of polygons
        // @param p is the vector of coordinates to be added
        //
		void addPolygon(std::vector<sf::Vector2f> p);
        
        //
        // Function that sets the polygon at a certain index to a list of new coordinates
        // @param index is the index of the polygon to be changed
        // @param v is the new coordinates for the polygon
        //
		void setPolygonAtIndex(int index, std::vector<sf::Vector2f> v);
		
		FunctionHolder<std::function<void(CollisionObject*, CollisionObject*)> > collisionFunctions;

		void makeCopy(CollisionObject *);
	private:
		sf::Vector2f dir(sf::ConvexShape *, int point);
		float dot(sf::Vector2f a, sf::Vector2f b);
		sf::Vector2f normalize(sf::Vector2f v);
		sf::Vector2f perp(sf::Vector2f v);
		Range projection(sf::ConvexShape *, sf::Vector2f axis);
		bool contains(float n, Range r);
		bool overlap(Range r1, Range r2);
		float getRotationInRadians() { return float((getRotation()) * (3.14159265 / 180.00)); };
		sf::Vector2f getPointRotation(sf::Vector2f pos);
	};
}
#endif