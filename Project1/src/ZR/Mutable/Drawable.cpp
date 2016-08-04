#include <ZR/Mutable/Drawable.h>

namespace zr
{

	Drawable::Drawable()
	{
	}


	Drawable::~Drawable()
	{
	}

	void Drawable::update(sf::Time dT)
	{
		for (int i = 0; i < updateFunctions.size(); i++)
		{
			updateFunctions.get(i)(this, dT);
		}

		for (int i = 0; i < delayedFunctions.size(); i++)
		{
			delayedFunctions.get(i).second += dT;
			if (delayedFunctions.get(i).second.didReachEnd())
			{
				delayedFunctions.get(i).first(this, dT);
				delayedFunctions.get(i).second = sf::Time::Zero;
				delayedFunctions.deleteFunction(i);
			}
		}
	}

	void Drawable::handleEvent(sf::Event & e)
	{
		for (int i = 0; i < eventFunctions.size(); i++)
		{
			eventFunctions.get(i)(this, e);
		}
	}

}