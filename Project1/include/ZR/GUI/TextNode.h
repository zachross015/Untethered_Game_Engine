#ifndef TEXTNODE_H
#define TEXTNODE_H

#include <ZR/GUI/GUINode.h>
#include <tinyxml2.h>

namespace zr
{
	namespace HorizantalAlign
	{
		enum Type
		{
			Left,
			Middle,
			Right
		};
		
	}

	namespace VerticalAlign
	{
		enum Type
		{
			Top,
			Middle,
			Bottom
		};
	}

	namespace LineWrap
	{
		enum Type
		{
			WordWrap,
			CharacterWrap
		};
	}

	struct Settings
	{
		HorizantalAlign::Type ha;
		VerticalAlign::Type va;
		LineWrap::Type lw;
	};

	struct Line
	{
		std::vector<sf::Text *> groups;
		sf::Vector2f maxSize = { 0,0 };
	};

	/////////////////////////////////////////////////////////////////////////////////
	// The purpose of this class is to allow for Text based GUI elements.
	// All XML text is formatted as so : <text><style>words go</style><style>here</style></text>
	// **any text with in the <text> tag must be surrounded by a <style> tag**
	// GUI text attributes:
	//    pos, scale, orig, lw, lh, ha, va
	// GUI style attributes
	//	  font, color, size
	//
	//
	// Copyright © 2016 Zachary Ross. All rights reserved.
	/////////////////////////////////////////////////////////////////////////////////
	class TextNode : public GUINode
	{
	public:
		
		//
		// Function that allows for fully formatted text to be made.
		// Text entered into this will be run through an XML parse and certain keywords
		// will allow for different parts of a string to be Mutated. Example is two words
		// in the same string will be a different color or font
		// @param str is the plain string or xml string to be used
		//
		void setText(std::string str);

		//
		// Function that sets the maximum line width for the text
		// @param width is the maximum width for the line
		//
		void setLineWidth(float width);

		//
		//
		//
		void setFont(sf::Font f);

		//
		//
		//
		void setCharacterSize(int size);

		//
		//
		//
		void setColor(sf::Color c);

		//
		//
		//
		void setHorizantalAlign(HorizantalAlign::Type h);

		//
		//
		//
		void setVerticalAlign(VerticalAlign::Type v);

		//
		//
		//
		void setSpaceSize(float size);

		//
		//
		//
		float getSpaceSize();

		//
		//
		//
		void setLineHeight(float size);

		//
		//
		//
		float getLineHeight();

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
		sf::Vector2f getSize();

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
		float spaceSize = 20;
		float lineHeight = 10;
		std::vector<sf::Text*> text;
		sf::Color getColor(std::string s);
	private:
		
		std::vector<Line*> lines;
		Settings s;
		float lineWidth = 0;
		void configureLines();
		
		
		
	};
}

#endif

