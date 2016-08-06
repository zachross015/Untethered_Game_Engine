#include <ZR/Mutable/Clickable.h>
#include <ZR/GameResources/Resources.h>

namespace zr
{
	Clickable::Clickable()
	{

	}


	Clickable::~Clickable()
	{

	}

	bool Clickable::clickedInBounds()
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(*Window);
		sf::Vector2f pos = getPosition();
		return mousePos.x > pos.x && mousePos.y > pos.y && mousePos.x < pos.x + (width * getScale().x) && mousePos.y < pos.y + (height * getScale().y) && sf::Mouse::isButtonPressed(sf::Mouse::Left);
	}

	void Clickable::runClickFunctions()
	{
		if (clickedInBounds())
		{
			for (int i = 0; i < clickFunctions.size(); i++)
			{
				clickFunctions.get(i)(this);
			}
		}
	}
}