#include <ZR/GUI/ButtonNode.h>

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
		TextNode::setText(str);
		adjustPositioning();
	}
	void ButtonNode::setPosition(sf::Vector2f f)
	{
		r.setPosition({ f.x, f.y + (getSpaceSize()/2) });
		TextNode::setPosition({ f.x + padding.left, f.y + padding.top });
		adjustPositioning();
	}
	void ButtonNode::setScale(sf::Vector2f f)
	{
		r.setScale(f);
		padding = { padding.left * f.x, padding.top * f.y, padding.width * f.x, padding.height * f.y };
		TextNode::setScale(f);
		adjustPositioning();
	}
	void ButtonNode::setOrigin(sf::Vector2f f)
	{
		r.setOrigin(f);
		r.setOrigin({ f.x + padding.left, f.y + padding.top });
		adjustPositioning();
	}

	sf::Vector2f ButtonNode::getPosition()
	{
		return r.getPosition();
	}

	sf::Vector2f ButtonNode::getScale()
	{
		return r.getScale();
	}

	sf::Vector2f ButtonNode::getOrigin()
	{
		return r.getOrigin();
	}

	void ButtonNode::setSpaceSize(float size)
	{
		TextNode::setSpaceSize(size);
		adjustPositioning();
	}

	void ButtonNode::setLineHeight(float size)
	{
		TextNode::setLineHeight(size);
	}

	void ButtonNode::setBackgroundColor(sf::Color c)
	{
		r.setFillColor(c);
	}
	void ButtonNode::setPadding(sf::FloatRect rect)
	{
		padding = rect;
	}
	void ButtonNode::setOutlineColor(sf::Color c)
	{
		r.setOutlineColor(c);
	}
	void ButtonNode::setOutlineThickness(float f)
	{
		r.setOutlineThickness(f);
	}
	void ButtonNode::update(sf::Time dt)
	{
	}
	void ButtonNode::handleEvent(sf::Event & e)
	{
	}
	void ButtonNode::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(r);
		TextNode::draw(target, states);
	}
	void ButtonNode::adjustPositioning()
	{
		sf::Vector2f paddingTotal{padding.left + padding.width, padding.top + padding.height};
		TextNode::adjustPositioning();
		r.setSize(TextNode::getSize() + paddingTotal);
	}
}