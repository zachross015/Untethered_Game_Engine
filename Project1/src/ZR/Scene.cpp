#include <ZR/Scene.h>
#include <iostream>
#include <ZR/GameResources/Resources.h>

namespace zr
{
	Scene::Scene()
		: quad(0, sf::FloatRect(0, 0, Window->getSize().x, Window->getSize().y))
		, GUI(new GUIOverlay) 
	{
		
	}


	Scene::~Scene()
	{
		removeAllObjects();
	}

	void Scene::update(sf::Time deltaTime)
	{
		if (focusedObjects.empty())
			for (int i = 0; i < drawableObjects.size(); i++)
				drawableObjects[i]->update(deltaTime);
		else
			for (int i = 0; i < focusedObjects.size(); i++)
				focusedObjects[i]->update(deltaTime);

		
		quad.clear();
		for (int i = 0; i < collidableObjects.size(); i++)
			quad.insert(collidableObjects[i]);
		
		std::vector<CollisionObject *> collisions;
		for (int i = 0; i < collidableObjects.size(); i++)
		{
			collisions.clear();
			quad.retrieve(collisions, collidableObjects[i]);
			for (int j = 0; j < collisions.size(); j++)
			{
				for (int k = 0; k < collidableObjects[i]->getPolygonCount(); k++)
				{
					for (int m = 0; m < collisions[j]->getPolygonCount(); m++)
					{
						if(collidableObjects[i] != collisions[j])
							if (collidableObjects[i]->collision(collisions[j], k, m))
							{
								collidableObjects[i]->runCollisionFunctions(collisions[j]);
							}
					}
				}
			}
		}

		GUI->update(deltaTime);
	
	}

	void Scene::handleEvent(sf::Event &e)
	{
		if (focusedObjects.empty())
			for (int i = 0; i < drawableObjects.size(); i++)
				drawableObjects[i]->handleEvent(e);

		else
			for (int i = 0; i < focusedObjects.size(); i++)
				focusedObjects[i]->handleEvent(e);

		GUI->handleEvent(e);
	}

	void Scene::addObject(sf::Drawable *obj)
	{
		if (find(drawableObjects.begin(), drawableObjects.end(), obj) == drawableObjects.end())
		{
			objects.push_back(obj);
			if (Drawable *d = dynamic_cast<Drawable *>(obj))
				drawableObjects.push_back(d);
		}
	}

	void Scene::addCollidableObject(CollisionObject *p)
	{
		//if (find(collidableObjects.begin(), collidableObjects.end(), p) == collidableObjects.end())
			collidableObjects.push_back(p);
	}

	void Scene::addFocusedObject(Drawable * obj)
	{
		addObject(obj);
		focusedObjects.push_back(obj);
	}

	void Scene::removeFocusFromObject(Drawable * obj)
	{
		auto j = std::find(focusedObjects.begin(), focusedObjects.end(), obj);
		focusedObjects.erase(j);
	}

	void Scene::deleteObject(sf::Drawable *c)
	{
		auto h = std::find(objects.begin(), objects.end(), c);
		auto i = std::find(drawableObjects.begin(), drawableObjects.end(), c);
		auto j = std::find(focusedObjects.begin(), focusedObjects.end(), c);
		delete *h;
		*h = NULL;
		objects.erase(h);
		drawableObjects.erase(i);
		focusedObjects.erase(j);
	}

	void Scene::deleteCollidableObject(CollisionObject *c)
	{
		auto i = std::find(collidableObjects.begin(), collidableObjects.end(), c);
		if (i != collidableObjects.end())
		{
			collidableObjects.erase(i);
		}
	}

	void Scene::replaceObject(sf::Drawable *c, sf::Drawable *t)
	{
		auto i = std::find(objects.begin(), objects.end(), c);
		delete *i;
		*i = t;
	}

	void Scene::removeAllObjects()
	{
		for (int i = drawableObjects.size() - 1; i >= 0; --i)
		{
			deleteObject(drawableObjects[i]);
		}
	}

	void Scene::addChildScene(Scene *s)
	{
		childScenes.push_back(s);
	}

	void Scene::goToChildScene(int index)
	{
		// Make sure the index is not out of bounds
		if(index < childScenes.size() && index >= 0)
		{ 
			childScenes[index]->parentScene = this;
			CurrentScene = childScenes[index];
		}
		else
			throw std::runtime_error("Scene::goToChildScene - Index out of bounds: " + index);
	}

	void Scene::goToParentScene()
	{
		if (parentScene)
		{
			CurrentScene = parentScene;
		}
		else std::cerr << "Pointer does not exist : goToParentScene" << std::endl;
	}

	void Scene::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		for (int i = 0; i < objects.size(); i++)
		{
			target.draw(*objects[i], states);
		}
		GUI->draw(target, states);
	}
}