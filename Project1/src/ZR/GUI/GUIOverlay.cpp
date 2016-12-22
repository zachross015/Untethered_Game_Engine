#include <ZR/GUI/GUIOverlay.h>
#include <tinyxml2.h>
#include <ZR/GUI/ButtonNode.h>


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

	void GUIOverlay::removeNode(GUINode * g)
	{
		guiElements.erase(std::remove(guiElements.begin(), guiElements.end(), g), guiElements.end());
	}
	
	void GUIOverlay::draw(sf::RenderTarget &targets, sf::RenderStates states) const
	{
		for(int i = 0; i < guiElements.size(); i++)
			guiElements[i]->draw(targets,states);
	}

	bool GUIOverlay::loadFromFile(std::string filename)
	{
		tinyxml2::XMLDocument doc;
		tinyxml2::XMLElement *e;
		doc.LoadFile(filename.c_str());

		e = doc.FirstChildElement("text");
		while (e)
		{
			TextNode *tn = new TextNode();
			tn->loadFromElement(e);
			addNode(tn);
			e = e->NextSiblingElement("text");
			tn = 0;
			delete tn;
		}

		doc.PrintError();
		e = doc.FirstChildElement("textbox");
		while (e)
		{
			TextBox *tn = new TextBox();
			tn->loadFromElement(e);
			addNode(tn);
			e = e->NextSiblingElement("textbox");
			tn = 0;
			delete tn;
		}

		e = doc.FirstChildElement("button");
		while(e)
		{
			ButtonNode *bn = new ButtonNode();
			bn->loadFromElement(e);
			addNode(bn);
			e = e->NextSiblingElement("button");
			bn = 0;
			delete bn;
		}

		return true;
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
