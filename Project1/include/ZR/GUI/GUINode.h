#ifndef GUINODE_H
#define GUINODE_H

#include <SFML/Graphics.hpp>
#include <ZR/Mutable/Drawable.h>
#include <tinyxml2.h>

namespace zr
{

	class GUINode : public sf::Transformable, public Drawable
	{
	public:
		GUINode();
		~GUINode();

		//
		// Function that sets base attributes of any GUINode or derived class
		// based on passed information
		// @param elem is a pointer to the XMLElement being read from
		//
		virtual void loadFromElement(tinyxml2::XMLElement *elem) = 0;

		virtual void update(sf::Time dt) = 0;
		virtual void handleEvent(sf::Event &e) = 0;
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;
	protected:
		sf::Vector2f getCoords(std::string);
	private:
	};
}

#endif
