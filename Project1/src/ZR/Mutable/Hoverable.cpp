#include <ZR/Mutable/Hoverable.h>
#include <ZR/GameResources/Resources.h>

namespace zr
{
	Hoverable::Hoverable()
		: width(new float())
		, height(new float())
	{

	}


	Hoverable::~Hoverable()
	{

	}

	bool Hoverable::isHovering() const
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(*Window);
		sf::Vector2f pos = getPosition();
		return mousePos.x > pos.x && mousePos.y > pos.y && mousePos.x < pos.x + (*width * getScale().x) && mousePos.y < pos.y + (*height * getScale().y);
	}

	void Hoverable::runHoverFunctions()
	{
		if (isHovering())
		{
			for (int i = 0; i < hoverFunctions.size(); i++)
			{
				hoverFunctions.get(i)(this);
			}
		}
	}
}
