#include <ZR/Physics/ComplexPolygon.h>
#include <iostream>

namespace zr
{
	ComplexPolygon::ComplexPolygon()
	{
	}


	ComplexPolygon::~ComplexPolygon()
	{
	}

	sf::FloatRect ComplexPolygon::getLocalBounds()
	{
		float height = 0, width = 0;
		sf::ConvexShape *p;
		for (int i = 0; i < polygons.size(); i++)
		{
			p = &polygons[i];
			if (p->getLocalBounds().width > width) width = p->getLocalBounds().width;
			if (p->getLocalBounds().height > height) height = p->getLocalBounds().height;
		}
		p = 0;
		delete p;
		return sf::FloatRect({0,0,width,height });
	}

	sf::FloatRect ComplexPolygon::getGlobalBounds()
	{
		sf::FloatRect temp = getLocalBounds();

		temp.width *= polygons[0].getScale().x;
		temp.height *= polygons[0].getScale().y;

		temp.left += polygons[0].getPosition().x;
		temp.top += polygons[0].getPosition().y;
		
		return temp;
	}

	void ComplexPolygon::setScale(sf::Vector2f f)
	{
		for (int i = 0; i < polygons.size(); i++)
			polygons[i].setScale(f);
	}

	void ComplexPolygon::setPosition(sf::Vector2f f)
	{
		for (int i = 0; i < polygons.size(); i++)
			polygons[i].setPosition(f);
	}

	void ComplexPolygon::move(sf::Vector2f pos)
	{
		for (int i = 0; i < polygons.size(); i++)
			polygons[i].move(pos);
	}

	void ComplexPolygon::setOrigin(sf::Vector2f f)
	{
		for (int i = 0; i < polygons.size(); i++)
			polygons[i].setOrigin(f);
	}

	void ComplexPolygon::setRotation(float angle)
	{
		for (int i = 0; i < polygons.size(); i++)
			polygons[i].setRotation(angle);
	}

	void ComplexPolygon::rotate(float angle)
	{
		for (int i = 0; i < polygons.size(); i++)
			polygons[i].rotate(angle);
	}

	void ComplexPolygon::setFillColor(sf::Color r)
	{
		for (int i = 0; i < polygons.size(); i++)
			polygons[i].setFillColor(r);
	}

	sf::Color ComplexPolygon::getFillColor()
	{
		return polygons[0].getFillColor();
	}

	void ComplexPolygon::addPolygon(std::vector<sf::Vector2f> v)
	{
		polygons.push_back(sf::ConvexShape());
		setPolygonAtIndex(polygons.size() - 1, v);
	}

	void ComplexPolygon::setPolygonAtIndex(int index, std::vector<sf::Vector2f> v)
	{
		if (index > polygons.size()) throw std::runtime_error("ComplexPolygon::setPolygonAtIndex index out of bounds");
		polygons[index].setPointCount(v.size());
		for (int i = 0; i < polygons[index].getPointCount(); i++)
		{
			polygons[index].setPoint(i, v[i]);
		}
	}
}
