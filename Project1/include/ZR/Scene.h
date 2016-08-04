#ifndef SCENE_H
#define SCENE_H
#include <ZR/Mutable/Drawable.h>
#include <ZR/Physics/PhysicsObject.h>
#include <ZR/QuadTree.h>
#include <ZR/GUI/GUIOverlay.h>
#include <vector>

namespace zr
{
	class Scene : public Drawable
	{
	public:
		Scene();
		~Scene();

		virtual void update(sf::Time deltaTime);
		virtual void handleEvent(sf::Event &e);

		//Adds any drawable object to the drawableObjects array to be drawn to the screen
		virtual void addObject(sf::Drawable *);

		virtual void addCollidableObject(CollisionObject *p);

		//
		// Function that adds an object to drawableObjects and focusedObjects.
		// If there is any focused objects, only the focused ones will be updated.
		// @param obj is a pointer to the object being added to the focused objects vector
		//
		virtual void addFocusedObject(Drawable *obj);

		//
		// Function that removes the object from the focused objects vector, allowing for it
		// still to be used in the drawable objects but just removing the focus
		// @param obj is a pointer to the object being removed
		//
		virtual void removeFocusFromObject(Drawable *obj);

		virtual void deleteObject(sf::Drawable *);
		void deleteCollidableObject(CollisionObject *c);
		//Replaces the first object with the second one
		virtual void replaceObject(sf::Drawable *, sf::Drawable *);
		virtual void removeAllObjects();

		//
		// Function that adds a child scene to the current vector
		// of child scenes
		// @param s is a pointer to the scene to be added
		//
		void addChildScene(Scene *s);

		//
		// Function that sets the current scene to the child at the index gived.
		// The function will also set the parent scene of the child to this object.
		// @param index is the index of the child for the current scene to be
		// set to
		//
		void goToChildScene(int index);

		//
		// Function that sets the current scene to the parent scene
		// of the current scene
		//
		void goToParentScene();

		GUIOverlay *GUI;


	private:
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
		Scene *parentScene;
		QuadTree quad;
		std::vector<Scene *> childScenes;
		std::vector<sf::Drawable *> objects;
		std::vector<Drawable *> drawableObjects;
		std::vector<Drawable *> focusedObjects;
		std::vector<CollisionObject *> collidableObjects;
	};
}
#endif