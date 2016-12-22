#include <ZR\Sprite\Actor.h>
#include <iostream>
#include <ZR\Scene.h>

extern zr::Scene *CurrentScene;

namespace zr
{
	

	Actor::Actor()
	: CollisionObject()
	, currentBounds(new CollisionObject*[1])
	{
	}


	Actor::~Actor()
	{
	}

	void Actor::update(sf::Time dT)
	{
		if (type == Movement::ConstAccl)
		{
			velocity += acceleration;
			if (velocity.x > 0.f) velocity.x -= (friction);
			else if (velocity.x < 0.f) velocity.x += (friction);
			if (velocity.y > 0.f) velocity.y -= (friction);
			else if (velocity.y < 0.f) velocity.y += (friction);

			if (velocity.y > -friction && velocity.y < friction) velocity.y = 0;
			if (velocity.x > -friction && velocity.x < friction) velocity.x = 0;
		}

		move(velocity * dT.asSeconds());

		Drawable::update(dT);
		if (currentAnimation)
		{
			currentAnimation->setPosition(Transformable::getPosition());
			currentAnimation->setRotation(Transformable::getRotation());
			currentAnimation->setOrigin(Transformable::getOrigin());
			currentAnimation->setScale(Transformable::getScale());
			currentAnimation->update(dT);
			if (currentBounds)
			{
				if(*currentBounds)
					CollisionObject::makeCopy(*currentBounds);
			}
		}
	}

	void Actor::handleEvent(sf::Event & e)
	{
		Drawable::handleEvent(e);
	}

	void Actor::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		if (currentAnimation)
		{
			target.draw(*currentAnimation, states);
		}
	}

	void Actor::addAnimation(std::string identifier, Animation *anim)
	{
		if (anim->hasBounds())
			anim->resetPolygon();
		animations.insert(std::pair<std::string, Animation *>(identifier, new Animation(*anim)));
		if (!currentAnimation)
			setCurrentAnimation(identifier);
	}

	void Actor::setCurrentAnimation(std::string s)
	{
		CurrentScene->deleteCollidableObject(this);
		currentAnimation = animations[s];
		currentAnimation->play();

		if (currentAnimation->hasBounds())
		{
			*currentBounds = currentAnimation->getCurrentPolygon();
			CurrentScene->addCollidableObject(this);
		}
		else
		{
			*currentBounds = nullptr;
		}
	}

	void Actor::setScale(sf::Vector2f f)
	{
		Transformable::setScale(f);
		for (std::map<std::string, Animation *>::iterator a = animations.begin(); a != animations.end(); a++)
		{
            a->second->setScale(f);
		}
	}

	void Actor::setOrigin(sf::Vector2f f)
	{
        Transformable::setOrigin(f);
		for (std::map<std::string, Animation *>::iterator a = animations.begin(); a != animations.end(); a++)
		{
            a->second->setOrigin(f);
		}
	}

	void Actor::setRotation(float angle)
	{
        Transformable::setRotation(angle);
		for (std::map<std::string, Animation *>::iterator a = animations.begin(); a != animations.end(); a++)
		{
            a->second->setRotation(angle);
		}
	}

	void Actor::rotate(float angle)
	{
        Transformable::rotate(angle);
		for (std::map<std::string, Animation *>::iterator a = animations.begin(); a != animations.end(); a++)
		{
            a->second->rotate(angle);
		}
	}


	void Actor::setPosition(sf::Vector2f posi)
	{
        if (previousPos != Transformable::getPosition())previousPos = Transformable::getPosition();
		Transformable::setPosition(posi);
		for (std::map<std::string, Animation *>::iterator a = animations.begin(); a != animations.end(); a++)
		{
			a->second->setPosition(posi);
		}
	}

	void Actor::goToPreviousPosition()
	{
		setPosition(previousPos);
	}

	void Actor::move(sf::Vector2f pos)
	{
		setPosition(Transformable::getPosition() + pos);
	}
	void Actor::setMovementSpeed(sf::Vector2f amt)
	{
		if (type == Movement::ConstAccl)
			acceleration = amt;
		else if (type == Movement::ConstVel)
			velocity = amt;
	}
	void Actor::setMovementType(Movement::Type t)
	{
		type = t;
	}
	sf::Vector2f Actor::getPosition()
	{
		return Transformable::getPosition();
	}
	sf::Vector2f Actor::getScale()
	{
		return Transformable::getScale();
	}
	float Actor::getRotation()
	{
		return Transformable::getRotation();
	}
	sf::Vector2f Actor::getOrigin()
	{
		return Transformable::getOrigin();
	}
	sf::Vector2f Actor::getMovementSpeed()
	{
		if (type == Movement::ConstAccl)
			return acceleration;
		else if (type == Movement::ConstVel)
			return velocity;
		return{ 0,0 };
	}
}
