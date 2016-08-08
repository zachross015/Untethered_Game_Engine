#include <ZR/GUI/ButtonNode.h>
#include <ZR/GameResources/Resources.h>
#include <sstream>

namespace zr
{
	ButtonNode::ButtonNode()
	{
	}
	ButtonNode::~ButtonNode()
	{
	}

	void ButtonNode::setText(std::string str)
	{
		text.clear();
		tinyxml2::XMLDocument doc;
		tinyxml2::XMLElement *elem;
		doc.Parse(str.c_str());
		elem = doc.FirstChildElement("button");
		loadFromElement(elem);
	}
	void ButtonNode::setPosition(sf::Vector2f f)
	{
		TextBox::setPosition(f);
		Hoverable::setPosition(f);
		Clickable::setPosition(f);
		adjustPositioning();
	}
	void ButtonNode::setScale(sf::Vector2f f)
	{
		TextBox::setScale(f);
		Hoverable::setScale(f);
		Clickable::setScale(f);
		adjustPositioning();
	}

	void ButtonNode::loadFromElement(tinyxml2::XMLElement * elem)
	{
		TextBox::loadFromElement(elem);
		setPosition(Transformable::getPosition());
		setScale(Transformable::getScale());
		TextBox::setOrigin(Transformable::getOrigin());
		adjustPositioning();
	}

	void ButtonNode::update(sf::Time dt)
	{
		runClickFunctions();
		runHoverFunctions();
	}
	void ButtonNode::handleEvent(sf::Event & e)
	{
	}

	void ButtonNode::adjustPositioning()
	{
		sf::Vector2f paddingTotal{padding.left + padding.width, padding.top + padding.height};
		TextBox::adjustPositioning();
		Hoverable::setSize(TextNode::getSize() + paddingTotal);
		Clickable::setSize(TextNode::getSize() + paddingTotal);
	}
	sf::FloatRect ButtonNode::getRect(std::string str)
	{
		return sf::FloatRect();
	}
}