#include <ZR/Physics/CollisionObject.h>
#include <iostream>
#include <cmath>

namespace zr
{
	sf::Vector2f multiply(sf::Vector2f a, sf::Vector2f b)
	{
		return{ a.x * b.x, a.y * b.y };
	}

	CollisionObject::CollisionObject()
	{
	}


	CollisionObject::CollisionObject(CollisionObject *other)
	{
		ComplexPolygon::polygons = other->polygons;
		setPosition(other->getPosition());
		setScale(other->getScale());
		setOrigin(other->getOrigin());
		setRotation(other->getRotation());
		
	}

	CollisionObject::~CollisionObject()
	{
		ComplexPolygon::~ComplexPolygon();
	}

	bool CollisionObject::simpleCollision(CollisionObject *x)
	{
		Range x1, y1, x2, y2;
		x1.min = getGlobalBounds().left;
		x1.max = getGlobalBounds().width;
		y1.min = getGlobalBounds().top;
		y1.max = getGlobalBounds().height;
		x2.min = x->getGlobalBounds().left;
		x2.max = x->getGlobalBounds().width;
		y2.min = x->getGlobalBounds().top;
		y2.max = x->getGlobalBounds().height;

		return (x1.overlaps(x2) && y1.overlaps(y2));
	}

	bool CollisionObject::collision(CollisionObject *o, int index, int index2)
	{

		sf::ConvexShape *shape = &polygons[index];
		sf::ConvexShape *shape2 = &o->polygons[index2];
		for (int i = 0; i < shape->getPointCount(); i++)
		{
			sf::Vector2f axis = dir(shape, i);
			axis = perp(axis);
			Range r1 = projection(shape, axis);
			Range r2 = o->projection(shape2, axis);
			if (!overlap(r1, r2)) return false;
		}

		for (int i = 0; i < shape2->getPointCount(); i++)
		{
			sf::Vector2f axis = o->dir(shape2, i);
			axis = o->perp(axis);
			Range r1 = projection(shape, axis);
			Range r2 = o->projection(shape2, axis);
			if (!overlap(r1, r2)) return false;
		}
		return true;
	}

	void CollisionObject::runCollisionFunctions(CollisionObject *other)
	{
		for (int i = 0; i < collisionFunctions.size(); i++)
		{
			collisionFunctions.get(i)(this, other);
		}
	}

	void CollisionObject::setScale(sf::Vector2f f)
	{
		Transformable::setScale(f);
		ComplexPolygon::setScale(f);
	}

	void CollisionObject::setPosition(sf::Vector2f f)
	{
		Transformable::setPosition(f);
		ComplexPolygon::setPosition(f);

	}

	void CollisionObject::move(sf::Vector2f pos)
	{
		Transformable::move(pos);
		ComplexPolygon::move(pos);
	}

	void CollisionObject::setOrigin(sf::Vector2f f)
	{
		Transformable::setOrigin(f);
		ComplexPolygon::setOrigin(f);
	}

	void CollisionObject::setRotation(float angle)
	{
		Transformable::setRotation(angle);
		ComplexPolygon::setRotation(angle);
	}
	void CollisionObject::rotate(float angle)
	{
		Transformable::rotate(angle);
		ComplexPolygon::rotate(angle);
	}

	sf::FloatRect CollisionObject::getLocalBounds()
	{
		return ComplexPolygon::getLocalBounds();
	}

	sf::FloatRect CollisionObject::getGlobalBounds()
	{
		return ComplexPolygon::getGlobalBounds();
	}

	void CollisionObject::addPolygon(std::vector<sf::Vector2f> v)
	{
		polygons.push_back(sf::ConvexShape());
		setPolygonAtIndex(polygons.size() - 1, v);
	}

	void CollisionObject::setPolygonAtIndex(int index, std::vector<sf::Vector2f> v)
	{
		ComplexPolygon::setPolygonAtIndex(index, v);
		setScale(getScale());
		setPosition(getPosition());
		setRotation(getRotation());
	}

	void CollisionObject::makeCopy(CollisionObject *other)
	{
		ComplexPolygon::polygons = other->polygons;
		setPosition(other->getPosition());
		setScale(other->getScale());
		setOrigin(other->getOrigin());
		setRotation(other->getRotation());
	}

	sf::Vector2f CollisionObject::dir(sf::ConvexShape *s, int point)
	{
		sf::Vector2f p1, p2;
		p1 = s->getPoint(point);
		p2 = s->getPoint(point + 1 == s->getPointCount() ? 0 : point + 1);
		float xSlope = (p2.x - p1.x);
		float ySlope = (p2.y - p1.y);
		return getPointRotation({ xSlope,ySlope });
	}

	float CollisionObject::dot(sf::Vector2f a, sf::Vector2f b)
	{
		return a.x * b.x + a.y * b.y;

	}

	sf::Vector2f CollisionObject::normalize(sf::Vector2f v)
	{
		float mag = (std::sqrt(v.x * v.x + v.y * v.y));
		return sf::Vector2f(v.x / mag, v.y / mag);
	}

	sf::Vector2f CollisionObject::perp(sf::Vector2f v)
	{

		return sf::Vector2f(v.y, -v.x);
	}

	Range CollisionObject::projection(sf::ConvexShape *s, sf::Vector2f axis)
	{
		Range r;
		axis = normalize(axis);
		float xCoord = (s->getPoint(0).x * getScale().x);
		float yCoord = (s->getPoint(0).y * getScale().x);
		r.min = dot(getPointRotation({ xCoord, yCoord }) + getPosition(), axis);
		r.max = r.min;
		for (int i = 0; i < s->getPointCount(); i++)
		{
			xCoord = (s->getPoint(i).x * getScale().x);
			yCoord = (s->getPoint(i).y * getScale().x);
			float proj = dot(getPointRotation({ xCoord, yCoord }) + getPosition(), axis);
			if (proj < r.min) r.min = proj;
			if (proj > r.max) r.max = proj;
		}
		return r;
	}

	bool CollisionObject::contains(float n, Range r)
	{
		float a = r.min, b = r.max;
		if (b < a) { a = b; b = r.min; }
		return (n >= a && n <= b);
	}

	bool CollisionObject::overlap(Range r1, Range r2)
	{
		if (contains(r1.min, r2)) return true;
		if (contains(r1.max, r2)) return true;
		if (contains(r2.min, r1)) return true;
		if (contains(r2.max, r1)) return true;
		return false;
	}

	sf::Vector2f CollisionObject::getPointRotation(sf::Vector2f point)
	{
		float sinVal = std::sin(-getRotationInRadians());
		float cosVal = std::cos(-getRotationInRadians());
		float x = (point.x * cosVal + point.y * sinVal);
		float y = point.x * -sinVal + point.y * cosVal;
		return sf::Vector2f(x, y);
	}
}
