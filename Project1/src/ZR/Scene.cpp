#include <ZR/Scene.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ZR/GameResources/Resources.h>
#include <ZR/Sprite/StaticActor.h>

namespace zr
{
	Scene::Scene(std::string sn)
		: quad(0, sf::FloatRect(0, 0, Window->getSize().x, Window->getSize().y))
		, GUI(new GUIOverlay) 
		, name(sn)
	{
		loadScene();
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
		if (find(objects.begin(), objects.end(), obj) == objects.end())
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
		childScenes.insert(std::make_pair(s->getSceneName(),s));
	}

	void Scene::loadChildScene(std::string sceneName)
	{
		// Make sure the index is not out of bounds
		if(childScenes[sceneName])
		{ 
			childScenes[sceneName]->parentScene = this;
			CurrentScene = childScenes[sceneName];
		}
		else
			throw std::runtime_error("Scene::goToChildScene - Scene does not exist: " + sceneName);
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

	std::string Scene::getSceneName()
	{
		return name;
	}

	void Scene::loadScene()
	{
		if (!loaded)
		{
			loaded = true;
			std::ifstream s;
			s.open("data/sd/" + name + "/resources.dat");
			if (!s.fail())
			{
				while (!s.eof())
				{
					std::string type, name, path;
					s >> type >> name >> path;
					if (type == "Texture")
						Textures.load(name, path);
					else if (type == "Font")
						Fonts.load(name, path);
					else if (type == "Sound")
						Sounds.load(name, path);
					else if (type == "Animation")
						Animations.load(name, path);
				}
			}
			else
			{
				throw std::runtime_error("Game::loadResources - failed to open resource file");
			}
			s.close();
			if (!GUI) GUI = new GUIOverlay();
			GUI->loadFromFile("data/sd/" + name + "/gui.dat");

			tinyxml2::XMLDocument doc;
			tinyxml2::XMLElement *elem;
			doc.LoadFile(("data/sd/" + name + "/objects.dat").c_str());
			// Load static objects
			elem = doc.FirstChildElement("s_object");
			while (elem)
			{
				loadObject(elem);
				elem = elem->NextSiblingElement("s_object");
			}
			
		}
	}

	void Scene::loadObject(tinyxml2::XMLElement *e)
	{
		zr::StaticActor *s = new zr::StaticActor();
		tinyxml2::XMLElement *child;
		if (child = e->FirstChildElement("collision_data"))
		{
			child = child->FirstChildElement("polygon");
			CollisionObject obj;
			std::vector<sf::Vector2f> points;
			while (child) //Prevents the loop from occurring in the case that the first input is has no polygon
			{
				std::istringstream iss(child->GetText());
				std::string input;
				while (std::getline(iss, input, ' '))
				{
					sf::Vector2f value;
					value.x = std::stof(input);
					std::getline(iss, input, ' ');
					value.y = std::stof(input);
					points.push_back(value);
				}
				obj.addPolygon(points);
				points.clear();
				s->makeCopy(&obj);
				child = child->NextSiblingElement("polygon");
			}
		}
		if(child = e->FirstChildElement("texture"))
			s->setTexture(Textures.get(child->GetText()));
		if(child = e->FirstChildElement("pos"))
			s->setPosition(getCoords(child->GetText()));
		if(child = e->FirstChildElement("scale"))
			s->setScale(getCoords(child->GetText()));
		if(child = e->FirstChildElement("origin"))
			s->setOrigin(getCoords(child->GetText()));
		if(child = e->FirstChildElement("rotation"))
			s->setRotation(std::stof(child->GetText()));
		addObject(s);
		addCollidableObject(s);
		s = 0;
		delete s;
	}

	sf::Vector2f Scene::getCoords(std::string str)
	{
		std::string s(str);
		s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
		for (int i = 0; i < s.length(); i++)
		{
			if (isupper(s[i]))
				s[i] = tolower(s[i]);
		}
		s.erase(std::remove(s.begin(), s.end(), '('), s.end());
		s.erase(std::remove(s.begin(), s.end(), ')'), s.end());
		return sf::Vector2f({ std::stof(s.substr(0,s.find(','))),std::stof(s.substr(s.find(',') + 1)) });
	}
	
}