#include <ZR/GUI/TextNode.h>
#include <ZR/GameResources/Resources.h>
namespace zr
{
	void TextNode::setText(std::string str)
	{
		text.clear();
		tinyxml2::XMLDocument doc;
		tinyxml2::XMLElement *elem;
		doc.Parse(str.c_str());
		elem = doc.FirstChildElement("style");
		sf::Text *t;
		while (elem)
		{
			t = new sf::Text();

			// Set specified font
			if (elem->BoolAttribute("font"))
				t->setFont(Fonts.get(elem->Attribute("font")));
			else
				(t->setFont(Fonts.get("default")));

			// Set specified color
			//if (elem->BoolAttribute("color"))
			//	t.setFillColor(sf::Color::White);
			//else
			//	t.setFillColor(sf::Color::White);

			// Set specified size
			if (elem->BoolAttribute("size"))
				t->setCharacterSize(std::stoi(elem->Attribute("size")));
			else
				t->setCharacterSize(30);

			t->setString(elem->GetText());

			text.push_back(t);
			elem = elem->NextSiblingElement("style");
		}

		adjustPositioning();
		t = 0;
		delete t;
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
		adjustPositioning();
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

	void TextNode::setLineWrap(LineWrap::Type l)
	{
		s.lw = l;
		adjustPositioning();
	}

	void TextNode::setSpaceSize(float size)
	{
		spaceSize = size;
	}

	float TextNode::getSpaceSize()
	{
		return spaceSize;
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

	void TextNode::update(sf::Time dt)
	{
	}

	void TextNode::handleEvent(sf::Event & e)
	{
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

				if (s.va == VerticalAlign::Top)
					pos.y += (line->maxSize.y - t->getGlobalBounds().height) / 2;
				else if(s.va == VerticalAlign::Middle)
					pos.y += line->maxSize.y - t->getGlobalBounds().height;
				else if(s.va == VerticalAlign::Bottom)
					pos.y += (line->maxSize.y - t->getGlobalBounds().height) * 1.5;

				
				if (s.ha == HorizantalAlign::Middle)
					pos.x += (lineWidth - line->maxSize.x)/2;
				else if (s.ha == HorizantalAlign::Right)
					pos.x += (lineWidth - line->maxSize.x);

				x += t->getGlobalBounds().width;
				t->setPosition(pos);
			}
			y += line->maxSize.y + spaceSize;
			line = 0;
			delete line;

		}
	}
<<<<<<< HEAD
}
=======
}
>>>>>>> bb321ad0b06d6f43796b5507de6de175ce3159b4
