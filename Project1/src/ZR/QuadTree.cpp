#include <ZR/QuadTree.h>
#include <iostream>

namespace zr
{
	QuadTree::QuadTree(int lvl, sf::FloatRect b)
		: nodes(4)
	{
		level = lvl;
		bounds = b;
	}


	QuadTree::~QuadTree()
	{
	}
	void QuadTree::clear()
	{
		objects.clear();
		for (int i = 0; i < nodes.size(); i++)
		{
			if (nodes[i] != nullptr)
			{
				nodes[i]->clear();
				delete nodes[i];
				nodes[i] = 0;
			}
		}
	}
	void QuadTree::split()
	{
		int subWidth = (int)(bounds.width / 2);
		int subHeight = (int)(bounds.height / 2);
		int x = bounds.left;
		int y = bounds.top;

		nodes[0] = new QuadTree(level + 1, sf::FloatRect(x + subWidth, y, subWidth, subHeight));
		nodes[1] = new QuadTree(level + 1, sf::FloatRect(x, y, subWidth, subHeight));
		nodes[2] = new QuadTree(level + 1, sf::FloatRect(x, y + subHeight, subWidth, subHeight));
		nodes[3] = new QuadTree(level + 1, sf::FloatRect(x + subWidth, y + subHeight, subWidth, subHeight));
	}
	int QuadTree::getIndex(CollisionObject *c)
	{
		sf::FloatRect fr = c->getGlobalBounds();
		int index = -1;
		double verticalMidpoint = bounds.left + (bounds.width / 2);
		double horizantalMidpoint = bounds.top + (bounds.height / 2);
		bool topQuadrant = (fr.top < horizantalMidpoint && fr.top + fr.height < horizantalMidpoint);
		bool bottomQuadrant = (fr.top > horizantalMidpoint);
		bool leftQuadrant = (fr.left < verticalMidpoint && fr.left + fr.width < verticalMidpoint);
		bool rightQuadrant = (fr.left > verticalMidpoint);
		if (leftQuadrant)
		{
			if (topQuadrant) index = 1;
			else if (bottomQuadrant) index = 2;
		}
		else if (rightQuadrant)
		{
			if (topQuadrant) index = 0;
			else if (bottomQuadrant) index = 3;
		}
		return index;
	}
	void QuadTree::insert(CollisionObject *c)
	{
		if (nodes[0] != nullptr)
		{
			int index = getIndex(c);
			if (index != -1)
				nodes[index]->insert(c);
		}
		objects.push_back(c);

		if (objects.size() > MAX_OBJECTS && level < MAX_LEVELS)
		{
			if (nodes[0] == nullptr)
				split();
			int i = 0;
			while (i < objects.size())
			{
				int index = getIndex(objects[i]);
				if (index != -1)
				{
					nodes[index]->insert(objects[i]);
					objects.erase(objects.begin() + i);
				}
				else i++;
			}

		}
	}
	std::vector<CollisionObject*> QuadTree::retrieve(std::vector<CollisionObject *> &vc, CollisionObject *c)
	{
		if (nodes[0])
		{
			int index = getIndex(c);
			if (index != -1)
				nodes[index]->retrieve(vc, c);
			else
				for (int i = 0; i < 4; i++)
					nodes[i]->retrieve(vc, c);
		}
		for (int i = 0; i < objects.size(); i++) vc.push_back(objects[i]);
		vc.erase(unique(vc.begin(), vc.end()), vc.end());
		return vc;
		
		
	}
}
