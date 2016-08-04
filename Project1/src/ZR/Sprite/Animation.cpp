#include <ZR/Sprite/Animation.h>
#include <iostream>
#include <fstream>

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
        bool bounded;
        // Gets the pathname up to the file
        std::string path = filename.substr(0, filename.find('_'));
        
        // Gets the name of the file
        std::string file = filename.substr(filename.find_last_of("/") + 1);
        if (file.find(".png") == std::string::npos)
            tImg->loadFromFile(path + "/" + file + ".png");
        else
            tImg->loadFromFile(path + "/" + file);
        std::ifstream in;
        in.open(path + "/" + file + ".txt");
        if (!in.fail())
        {
            in >> frames;
            in >> animSize.x;
            in >> animSize.y;
            in >> speed;
            in >> bounded;
            
            if(bounded)
            {
                for (int i = 0; i <= frames; i++)
                {
                    PhysicsObject obj;
                    std::vector<sf::Vector2f> points;
                    std::string input;
                    in >> input; //Skip the first instance of the word polygon
                    while (input != "end") //Prevents the loop from occurring in the case that the first input is has no polygon
                    {
                        in >> input;
                        do
                        {
                            sf::Vector2f value;
                            value.x = std::stof(input);
                            in >> value.y;
                            points.push_back(value);
                            in >> input;
                        
                        
                        } while (input != "polygon" && input != "end");
                        obj.addPolygon(points);
                        points.clear();
                    }
                    addAnimationBounds(obj);
                }
            }
            
        }
        else
            return false;
        in.close();
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