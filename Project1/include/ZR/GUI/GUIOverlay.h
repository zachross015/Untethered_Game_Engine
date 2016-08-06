#ifndef GUIOVERLAY_H
#define GUIOVERLAY_H

#include <ZR/GUI/GUINode.h>

namespace zr
{
	class GUIOverlay : public Drawable
	{
	public:
		GUIOverlay();
		~GUIOverlay();
		
		//
		// Function that adds a node to the list of nodes used in the
		// GUIOverlay
		// @param g is a pointer to the GUINode to be added
		//
		void addNode(GUINode *g);

		//
		// Function that loads a GUIOverlay from an XML file
		// parses the file and creates elements used in the GUI
		// @param filename is the name of the file to load from
		//
		bool loadFromFile(std::string filename);
		
		virtual void update (sf::Time dt);
		virtual void handleEvent (sf::Event &e);
		virtual void draw (sf::RenderTarget &target, sf::RenderStates states) const;

	private:
		std::vector<GUINode *> guiElements;
	};
}
#endif

