#include <ZR/Sprite/StaticActor.h>
#include <ZR/GameResources/Resources.h>

namespace zr
{
	StaticActor::StaticActor()
		: CollisionObject()
		, Sprite()
	{
		//CurrentScene->addCollidableObject(this);
	}
	StaticActor::~StaticActor()
	{
	}
	void StaticActor::setScale(sf::Vector2f s)
	{
		Sprite::setScale(s);
		CollisionObject::setScale(s);
	}
	void StaticActor::setOrigin(sf::Vector2f f)
	{
		Sprite::setOrigin(f);
		CollisionObject::setOrigin(f);
	}
	void StaticActor::setRotation(float angle)
	{
		Sprite::setRotation(angle);
		CollisionObject::setRotation(angle);
	}
	void StaticActor::rotate(float angle)
	{
		Sprite::rotate(angle);
		CollisionObject::rotate(angle);
	}
	void StaticActor::setPosition(sf::Vector2f pos)
	{
		Sprite::setPosition(pos);
		CollisionObject::setPosition(pos);
	}
	sf::Vector2f StaticActor::getPosition()
	{
		return Sprite::getPosition();
	}
	sf::Vector2f StaticActor::getScale()
	{
		return Sprite::getScale();
	}
	float StaticActor::getRotation()
	{
		return Sprite::getRotation();
	}
	sf::Vector2f StaticActor::getOrigin()
	{
		return Sprite::getOrigin();
	}
}