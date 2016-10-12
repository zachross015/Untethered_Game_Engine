#include <ZR/GUI/TextNode.h>
#include <ZR/GameResources/Resources.h>
#include <SFML/Graphics/Text.hpp>
#include <sstream>
namespace zr
{
	void TextNode::setText(std::string str)
	{
		text.clear();
		tinyxml2::XMLDocument doc;
		tinyxml2::XMLElement *elem;
		doc.Parse(str.c_str());
		elem = doc.FirstChildElement("text");
		loadFromElement(elem);
	}

	void TextNode::setLineWidth(float width)
	{
		lineWidth = width;
		adjustPositioning();
	}

	void TextNode::setFont(sf::Font f)
	{
		for (int i = 0; i < text.size(); i++)
			text[i]->setFont(f);
		adjustPositioning();
	}

	void TextNode::setCharacterSize(int size)
	{
		for (int i = 0; i < text.size(); i++)
			text[i]->setCharacterSize(size);
		adjustPositioning();
	}

	void TextNode::setTextColor(sf::Color c)
	{
		for (int i = 0; i < text.size(); i++)
			text[i]->setColor(c);
	}

	void TextNode::setHorizantalAlign(HorizantalAlign::Type h)
	{
		s.ha = h;
		adjustPositioning();
	}

	void TextNode::setVerticalAlign(VerticalAlign::Type v)
	{
		s.va = v;
		adjustPositioning();
	}

	void TextNode::setSpaceSize(float size)
	{
		spaceSize = size;
		adjustPositioning();
	}

	float TextNode::getSpaceSize()
	{
		return spaceSize;
	}

	void TextNode::setLineHeight(float size)
	{
		lineHeight = size;
		adjustPositioning();
	}

	float TextNode::getLineHeight()
	{
		return lineHeight;
	}

	void TextNode::setPosition(sf::Vector2f f)
	{
		Transformable::setPosition(f);
		adjustPositioning();
	}

	void TextNode::setScale(sf::Vector2f f)
	{
		Transformable::setScale(f);
		for (int i = 0; i < text.size(); i++)
			text[i]->setScale(f);
		adjustPositioning();
	}

	void TextNode::setOrigin(sf::Vector2f f)
	{
		Transformable::setOrigin(f);
		adjustPositioning();
	}

	sf::Vector2f TextNode::getSize()
	{
		float height = -lineHeight;
		for (int i = 0; i < lines.size(); i++)
			height += lines[i]->maxSize.y + lineHeight;
		return sf::Vector2f(lineWidth,height);
	}

	void TextNode::loadFromElement(tinyxml2::XMLElement * e)
	{
		if (!e) throw std::runtime_error("TextNode::loadFromElement - unable to read element. Check syntax");
		if (e->Attribute("pos"))
			setPosition(getCoords(e->Attribute("pos"))); //Position
		if (e->Attribute("scale"))
			setScale(getCoords(e->Attribute("scale"))); //Scale
		if (e->Attribute("orig"))
			setOrigin(getCoords(e->Attribute("orig"))); //Origin
		if (e->Attribute("lw"))
			setLineWidth(std::stof(e->Attribute("lw"))); //Line Width
		if (e->Attribute("lh"))
			setLineHeight(std::stof(e->Attribute("lh"))); //Line Height
		if (e->Attribute("ha")) //Horizantal Alignment
		{
			std::string str = e->Attribute("ha");
			if (str == "left")
				s.ha = HorizantalAlign::Left;
			else if (str == "middle")
				s.ha = HorizantalAlign::Middle;
			else if (str == "right")
				s.ha = HorizantalAlign::Right;
		}
		if (e->Attribute("va")) //Vertical Alignment
		{
			std::string str = e->Attribute("va");
			if (str == "top")
				s.va = VerticalAlign::Top;
			else if (str == "middle")
				s.va = VerticalAlign::Middle;
			else if (str == "bottom")
				s.va = VerticalAlign::Bottom;
		}
		if (e->Attribute("ss")) //Space Size
			setSpaceSize(std::stof(e->Attribute("ss")));

		tinyxml2::XMLElement *elem = e->FirstChildElement("style");
		sf::Text *t;
		sf::Text *space = new sf::Text();
		space->setString(" ");
		space->setFont(Fonts.get("default"));
		space->setColor(sf::Color::Black);
		space->setCharacterSize(spaceSize);
		while (elem)
		{
			std::istringstream ss(elem->GetText());
			std::string token;
			while (std::getline(ss, token, ' '))
			{
				t = new sf::Text();

				// Set specified font
				if (elem->Attribute("font"))
					(t->setFont(Fonts.get(elem->Attribute("font"))));
				else
					(t->setFont(Fonts.get("default")));

				// Set specified color
				if (elem->Attribute("color"))
					t->setColor(getColor(elem->Attribute("color")));
				else
					t->setColor(sf::Color::White);


				// Set specified size
				if (elem->Attribute("size"))
					t->setCharacterSize(std::stoi(elem->Attribute("size")));
				else
					t->setCharacterSize(30);

				t->setString(token);
				text.push_back(t);
				text.push_back(space);
			}
			elem = elem->NextSiblingElement("style");
		}

		adjustPositioning();
		t = 0;
		delete t;
	}

	void TextNode::update(sf::Time dt)
	{
		Drawable::update(dt);
	}

	void TextNode::handleEvent(sf::Event & e)
	{
		Drawable::handleEvent(e);
	}

	void TextNode::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		for (int i = 0; i < text.size(); i++)
			target.draw(*text[i]);
	}

	void TextNode::configureLines()
	{
		for (int i = 0; i < lines.size(); i++)
			delete lines[i];
		lines.clear();
		Line *l = new Line();
		for (int i = 0; i < text.size(); i++)
		{
			sf::Text *t = text[i];
			if (t->getString() == " ") t->setCharacterSize(spaceSize);
			if (l->maxSize.x + t->getGlobalBounds().width > (lineWidth * getScale().x))
			{
				lines.push_back(l);
				l = new Line();
				l->groups.push_back(t);
				l->maxSize.x += t->getGlobalBounds().width;
				l->maxSize.y = t->getGlobalBounds().height;
			}
			else
			{
				l->groups.push_back(t);
				l->maxSize.x += t->getGlobalBounds().width;
				if (t->getGlobalBounds().height > l->maxSize.y)
					l->maxSize.y = t->getGlobalBounds().height;
			}
		}
		lines.push_back(l);
		l = 0;
		delete l;
	}

	void TextNode::adjustPositioning()
	{
		configureLines();
		float y = 0;
		for (int i = 0; i < lines.size(); i++)
		{
			float x = 0;
			Line *line = lines[i];
			for (int j = 0; j < line->groups.size(); j++)
			{
				sf::Vector2f pos = {x+Transformable::getPosition().x,y+Transformable::getPosition().y};
				sf::Text *t = line->groups[j];

				//if (s.va == VerticalAlign::Top)
				//pos.y += line->maxSize.y - t->getGlobalBounds().height;
				//else if(s.va == VerticalAlign::Middle)
					//pos.y += (line->maxSize.y );
				//else if(s.va == VerticalAlign::Bottom)
					//pos.y += (line->maxSize.y - t->getGlobalBounds().height) * 1.5;

				
				if (s.ha == HorizantalAlign::Middle)
					pos.x += (lineWidth - line->maxSize.x)/2;
				else if (s.ha == HorizantalAlign::Right)
					pos.x += (lineWidth - line->maxSize.x);

				x += t->getGlobalBounds().width;
				t->setPosition(pos);
			}
			if (i != lines.size() - 1)
				y += lineHeight;
			y += line->maxSize.y;
			line = 0;
			delete line;

		}
	}
	sf::Color TextNode::getColor(std::string s)
	{
		s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
		for (int i = 0; i < s.length(); i++)
		{
			if (isupper(s[i]))
				s[i] = tolower(s[i]);
		}
		if (s == "red") return sf::Color::Red;
		else if (s == "blue") return sf::Color::Blue;
		else if (s == "black") return sf::Color::Black;
		else if (s == "green") return sf::Color::Green;
		else if (s == "white") return sf::Color::White;
		else if (s == "yellow") return sf::Color::Yellow;
		else if (s == "magenta") return sf::Color::Magenta;
		else if (s == "cyan") return sf::Color::Cyan;
		else
		{
			s = s.substr(s.find("("));
			s.erase(std::remove(s.begin(), s.end(), '('), s.end());
			s.erase(std::remove(s.begin(), s.end(), ')'), s.end());
			std::istringstream ss(s);
			std::string token;
			std::vector<std::string> tokens;
			float r, g, b, a = 255;
			while (std::getline(ss, token, ','))
				tokens.push_back(token);
			r = std::stof(tokens[0]);
			g = std::stof(tokens[1]);
			b = std::stof(tokens[2]);
			if (tokens.size() >= 4) a = std::stof(tokens[3]);
			return sf::Color(r, g, b, a);

		}
		return sf::Color::White;
	}
}
