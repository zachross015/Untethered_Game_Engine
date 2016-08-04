#include <ZR/GUI/GUIOverlay.h>


namespace zr
{
	GUIOverlay::GUIOverlay()
	{
	}


	GUIOverlay::~GUIOverlay()
	{
	}

	void GUIOverlay::addNode(GUINode *g)
	{
		guiElements.push_back(g);
	}
	
	void GUIOverlay::draw(sf::RenderTarget &targets, sf::RenderStates states) const
	{
		for(int i = 0; i < guiElements.size(); i++)
			guiElements[i]->draw(targets,states);
	}

	void GUIOverlay::update(sf::Time t)
	{
		for(int i = 0; i < guiElements.size(); i++)
			guiElements[i]->update(t);	
	}

	void GUIOverlay::handleEvent(sf::Event &e)
	{
		for(int i = 0; i < guiElements.size(); i++)
			guiElements[i]->handleEvent(e);
	}
}
