#ifndef GUINODE_H
#define GUINODE_H

#include <SFML/Graphics.hpp>
#include <ZR/Mutable/Drawable.h>

namespace zr
{

	class GUINode : public sf::Transformable, public Drawable
	{
	public:
		GUINode();
		~GUINode();

		virtual void update(sf::Time dt) = 0;
		virtual void handleEvent(sf::Event &e) = 0;
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;
	private:
	};
}

#endif
