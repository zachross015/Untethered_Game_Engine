<<<<<<< HEAD
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

=======
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

>>>>>>> bb321ad0b06d6f43796b5507de6de175ce3159b4
		virtual void update(sf::Time dt) = 0;
		virtual void handleEvent(sf::Event &e) = 0;
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;
	private:
	};
}

#endif
