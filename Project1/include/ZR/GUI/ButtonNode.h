#ifndef BUTTONNODE_H
#define BUTTONNODE_H

#include <ZR/GUI/TextBox.h>
#include <ZR/Mutable/Hoverable.h>
#include <ZR/Mutable/Clickable.h>

namespace zr
{
	/////////////////////////////////////////////////////////////////////////////////
	// The purpose of this class is to allow for Button based GUI elements.
	// All XML text is formatted as so : <button><style>words go</style><style>here</style></button>
	// **any text with in the <button> tag must be surrounded by a <style> tag**
	// GUI button attributes:
	//    pos, scale, orig, lw, lh, ha, va, bgcolor, olcolor, olthk, pad
	// GUI style attributes
	//	  font, color, size
	//
	//
	// Copyright © 2016 Zachary Ross. All rights reserved.
	/////////////////////////////////////////////////////////////////////////////////
	class ButtonNode : 
		public TextBox
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
		// Function that sets base attributes of any GUINode or derived class
		// based on passed information
		// @param elem is a pointer to the XMLElement being read from
		//
		void loadFromElement(tinyxml2::XMLElement *elem);

		virtual void update(sf::Time dt);
		virtual void handleEvent(sf::Event &e);

	protected:
		void adjustPositioning();
	private:
		sf::RectangleShape r;
		sf::FloatRect getRect(std::string s);

	};
}

#endif
