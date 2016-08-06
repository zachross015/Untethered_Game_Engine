#ifndef BUTTONNODE_H
#define BUTTONNODE_H

#include <ZR/GUI/TextNode.h>
#include <ZR/Mutable/Hoverable.h>
#include <ZR/Mutable/Clickable.h>

namespace zr
{
	class ButtonNode : 
		public TextNode
		, public Hoverable
		, public Clickable
	{
	public:
		ButtonNode();
		~ButtonNode();

		//
		//
		//
		void setText(std::string str);

		//
		//
		//
		void setPosition(sf::Vector2f f);

		//
		//
		//
		void setScale(sf::Vector2f f);

		//
		//
		//
		void setOrigin(sf::Vector2f f);

		//
		//
		//
		sf::Vector2f getPosition();

		//
		//
		//
		sf::Vector2f getScale();

		//
		//
		//
		sf::Vector2f getOrigin();

		//
		//
		//
		void setSpaceSize(float size);

		//
		//
		//
		void setLineHeight(float size);

		//
		//
		//
		void setBackgroundColor(sf::Color c);

		//
		//
		//
		void setPadding(sf::FloatRect rect);

		//
		//
		//
		void setOutlineColor(sf::Color c);

		//
		//
		//
		void setOutlineThickness(float f);

		//
		// Function that sets base attributes of any GUINode or derived class
		// based on passed information
		// @param elem is a pointer to the XMLElement being read from
		//
		void loadFromElement(tinyxml2::XMLElement *elem);

		virtual void update(sf::Time dt);
		virtual void handleEvent(sf::Event &e);
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	protected:
		void adjustPositioning();
	private:
		sf::RectangleShape r;
		sf::FloatRect padding = { 0,0,0,0 };
		sf::FloatRect getRect(std::string);

	};
}

#endif
