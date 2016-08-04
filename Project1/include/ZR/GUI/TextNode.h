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
<<<<<<< HEAD
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
=======
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
>>>>>>> bb321ad0b06d6f43796b5507de6de175ce3159b4
	};

	struct Line
	{
		std::vector<sf::Text *> groups;
		sf::Vector2f maxSize = { 0,0 };
	};

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
		void setTextColor(sf::Color c);

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
		void setLineWrap(LineWrap::Type l);

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
		void setPosition(sf::Vector2f f);

		//
		//
		//
		void setScale(sf::Vector2f f);

		//
		//
		//
		void setOrigin(sf::Vector2f f);

		virtual void update(sf::Time dt);
		virtual void handleEvent(sf::Event &e);
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	private:
		std::vector<sf::Text*> text;
		std::vector<Line*> lines;
		Settings s;
		float spaceSize = 20;
		float lineWidth = 0;
		void configureLines();
		void adjustPositioning();
		
		
	};
}

#endif

