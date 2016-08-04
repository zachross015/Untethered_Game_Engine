#include <ZR/Sprite/Animation.h>
#include <iostream>
#include <fstream>
#include <tinyxml2.h>
#include <sstream>

namespace zr
{
	Animation::Animation()
		:tImg(new sf::Texture())
		, s(*tImg)
	{
		s.setTextureRect(sf::IntRect(currentIndex * animSize.x, 0, animSize.x, animSize.y));
		speed = 1000;
        currentPolygon = new CollisionObject();
	}


	Animation::~Animation()
	{
	}

	void Animation::play()
	{
		isPlaying = true;
	}

	void Animation::stop()
	{
		isPlaying = false;
		currentIndex = 0;
	}

	void Animation::setTextureImage(sf::Texture *t)
	{
		tImg = t;
	}

	void Animation::setRotation(float angle)
	{
		s.setRotation(angle);
	}

	void Animation::rotate(float angle)
	{
		s.rotate(angle);
	}

	void Animation::update(sf::Time dT)
	{
		Drawable::update(dT);

		if (isPlaying)
		{
			counter += dT.asMilliseconds();
			if (counter > speed) 
			{ 
				currentIndex++; 
				if (currentIndex == getFrameCount())
				{
					currentIndex = 0;
					animationFinished = true;
					if (!loop) stop();
				}
				counter = 0;
			}

		}
		s.setTextureRect(sf::IntRect(currentIndex * animSize.x, 0, animSize.x, animSize.y));
        if(hasBounds())
        {
            if(currentPolygon != &polygonBounds[currentIndex])
            {
                *currentPolygon = polygonBounds[currentIndex];
                currentPolygon->setPosition(s.getPosition());
                currentPolygon->setRotation(s.getRotation());
                currentPolygon->setOrigin(s.getOrigin());
                currentPolygon->setScale(s.getScale());
            }
            
        }
	}

	void Animation::handleEvent(sf::Event & e)
	{
		Drawable::handleEvent(e);
	}

	void Animation::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(s, states);
	}

	bool Animation::loadFromFile(std::string filename)
	{
		tinyxml2::XMLDocument doc;

		// Gets the pathname up to the file
		std::string path = filename.substr(0, filename.find('_'));

		// Gets the name of the file
		std::string file = filename.substr(filename.find_last_of("/") + 1);

		tImg->loadFromFile(path + "/" + file + ".png");
		doc.LoadFile((path + "/" + file + ".xml").c_str());
		frames = std::stoi(doc.FirstChildElement("frames")->GetText());
		animSize.x = std::stof(doc.FirstChildElement("width")->GetText());
		animSize.y = std::stof(doc.FirstChildElement("height")->GetText());
		speed = std::stoi(doc.FirstChildElement("speed")->GetText());
		tinyxml2::XMLElement *elem = doc.FirstChildElement("collision_data");
		tinyxml2::XMLElement *e2 = elem->FirstChildElement("frame");
		while (e2)
		{
			tinyxml2::XMLElement *e3 = e2->FirstChildElement("polygon");
			PhysicsObject obj;
			std::vector<sf::Vector2f> points;
			while (e3) //Prevents the loop from occurring in the case that the first input is has no polygon
			{
				std::istringstream iss(e3->GetText());
				std::string input;
				while (std::getline(iss, input, ' '))
				{
					sf::Vector2f value;
					value.x = std::stof(input);
					std::getline(iss, input, ' ');
					value.y = std::stof(input);
					points.push_back(value);
				}
				obj.addPolygon(points);
				points.clear();
				e3 = e3->NextSiblingElement("polygon");
			}
			addAnimationBounds(obj);
			e2 = e2->NextSiblingElement("frame");
		}
		return true;
	}

    void Animation::resetPolygon()
    {
        currentPolygon = new CollisionObject();
    }
    
    void Animation::addAnimationBounds(CollisionObject p)
    {
        polygonBounds.push_back(p);
    }
    
    void Animation::setAnimationBoundsForFrame(int index, CollisionObject p)
    {
        if (index > frames)
            throw std::runtime_error("Animation::setAnimationBoundsForFrame - index exceeds frames");
        else
            polygonBounds[index] = p;
    }
    void Animation::setAllAnimationBounds(std::vector<CollisionObject> vp)
    {
        polygonBounds = vp;
    }
    
    bool Animation::hasBounds()
    {
        return polygonBounds.size() > 0;
    }
}