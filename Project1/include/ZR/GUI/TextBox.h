#ifndef TEXTBOX_H
#define TEXTBOX_H
#include <ZR/GUI/TextNode.h>

namespace zr
{
	/////////////////////////////////////////////////////////////////////////////////
	// The purpose of this class is to allow for TextBox based GUI elements.
	// All XML text is formatted as so : <textbox><style>words go</style><style>here</style></textbox>
	// **any text with in the <button> tag must be surrounded by a <style> tag**
	// GUI button attributes:
	//    pos, scale, orig, lw, lh, ha, va, bgcolor, olcolor, olthk, pad
	// GUI style attributes
	//	  font, color, size
	//
	//
	// Copyright © 2016 Zachary Ross. All rights reserved.
	/////////////////////////////////////////////////////////////////////////////////
	class TextBox : public TextNode
	{
	public:
		TextBox();
		~TextBox();

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
		sf::FloatRect padding = { 0,0,0,0 };
	private:
		sf::RectangleShape r;
		sf::FloatRect getRect(std::string s);
	};
}

#endif
