#ifndef QUADTREE_H
#define QUADTREE_H

#include <vector>
#include <ZR/Physics/PhysicsObject.h>

namespace zr
{
	class QuadTree
	{
	public:
		//
		// Default constructor that initalizes variables
		// @param lvl is the amount to initialize level to
		// @param fr is the bounds to initialize the class to
		//
		QuadTree(int lvl, sf::FloatRect fr);

		//
		// Default deconstructor
		//
		~QuadTree();

		//
		// Function that clears the quad tree by recursively clearing
		// all objects from all nodes;
		//
		void clear();

		//
		// Function that splits the node into four subnodes by dividing
		// the node into four equal parts and initializing the four
		// subnodes with the new bounds
		//
		void split();

		//
		// Function that determines where an object belongs in the quadtree
		// by determining which node the object can fit in to
		// @param fr is the local bounds of the object to be tested
		// @result returns the index to fit the object into
		//
		int getIndex(CollisionObject *c);

		//
		// Function that determines whether the node has any child nodes and tries
		// add the object there. if there are no child nodes or the object doesn't
		// fit in, it adds the object to the parent node
		// @param fr is the local bounds of the object to be inserted
		//
		void insert(CollisionObject *c);

		//
		// Function that gets all nodes that the given object could potentially collide with
		// @param fr is the object to be tested for likely collisions
		// @result returns a std::vector<PhysicsObject *> that would be likely to collide
		// 
		std::vector<CollisionObject *> retrieve(std::vector<CollisionObject *> &vc, CollisionObject *c);


	private:
		const int MAX_OBJECTS = 10;
		const int MAX_LEVELS = 5;
		int level;
		std::vector<CollisionObject *> objects;
		sf::RectangleShape shape;
		sf::FloatRect bounds;
		std::vector<QuadTree *> nodes;
	};
}

#endif

