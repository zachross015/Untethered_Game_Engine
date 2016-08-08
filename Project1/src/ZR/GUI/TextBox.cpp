#include <ZR/GUI/TextBox.h>
#include <iostream>

namespace zr
{
	TextBox::TextBox()
	{
	}
	TextBox::~TextBox()
	{
	}
	void TextBox::setText(std::string str)
	{
		text.clear();
		tinyxml2::XMLDocument doc;
		tinyxml2::XMLElement *elem;
		doc.Parse(str.c_str());
		elem = doc.FirstChildElement("textbox");
		loadFromElement(elem);
	}
	void TextBox::setPosition(sf::Vector2f f)
	{
		r.setPosition({ f.x, f.y + (getSpaceSize() / 2) });
		TextNode::setPosition(r.getPosition());
		adjustPositioning();
	}
	void TextBox::setScale(sf::Vector2f f)
	{
		r.setScale(f);
		TextNode::setScale(r.getScale());
		adjustPositioning();
	}
	void TextBox::setOrigin(sf::Vector2f f)
	{
		r.setOrigin(f);
		TextNode::setOrigin({ padding.left - f.x, padding.top - f.y });
		adjustPositioning();
	}

	sf::Vector2f TextBox::getPosition()
	{
		return r.getPosition();
	}

	sf::Vector2f TextBox::getScale()
	{
		return r.getScale();
	}

	sf::Vector2f TextBox::getOrigin()
	{
		return r.getOrigin();
	}

	void TextBox::setSpaceSize(float size)
	{
		TextNode::setSpaceSize(size);
		adjustPositioning();
	}

	void TextBox::setLineHeight(float size)
	{
		TextNode::setLineHeight(size);
		adjustPositioning();
	}

	void TextBox::setBackgroundColor(sf::Color c)
	{
		r.setFillColor(c);
	}
	void TextBox::setPadding(sf::FloatRect rect)
	{
		padding = rect;
		TextNode::setOrigin({ padding.left - Transformable::getOrigin().x, padding.top - Transformable::getOrigin().y});
		adjustPositioning();
	}
	void TextBox::setOutlineColor(sf::Color c)
	{
		r.setOutlineColor(c);
	}
	void TextBox::setOutlineThickness(float f)
	{
		r.setOutlineThickness(f);
	}
	void TextBox::loadFromElement(tinyxml2::XMLElement * e)
	{
		e->GetDocument()->PrintError();
		TextNode::loadFromElement(e);
		if (e->Attribute("bgcolor"))
			setBackgroundColor(getColor(e->Attribute("bgcolor")));
		if (e->Attribute("olcolor")) //Outline color
			setOutlineColor(getColor(e->Attribute("olcolor")));
		if (e->Attribute("olthk")) //Outline thickness
			setOutlineThickness(std::stof(e->Attribute("olthk")));
		if (e->Attribute("pad"))
			setPadding(getRect(e->Attribute("pad")));
		setPosition(Transformable::getPosition());
		setScale(Transformable::getScale());
		setOrigin(Transformable::getOrigin());
	}
	void TextBox::update(sf::Time dt)
	{
	}
	void TextBox::handleEvent(sf::Event & e)
	{
	}
	void TextBox::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(r);
		TextNode::draw(target, states);
	}
	void TextBox::adjustPositioning()
	{
		sf::Vector2f paddingTotal{ padding.left + padding.width, padding.top + padding.height };
		r.setSize(TextNode::getSize() + paddingTotal);
	}
	sf::FloatRect TextBox::getRect(std::string str)
	{
		std::string f1 = str.substr(str.find(",") + 1);
		std::string f2 = f1.substr(f1.find(",") + 1);
		std::string f3 = str.substr(0, f2.length());
		sf::Vector2f c1 = getCoords(f3);
		sf::Vector2f c2 = getCoords(f2);
		return sf::FloatRect({c1.x, c1.y, c2.x, c2.y});
	}
}