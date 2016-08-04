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
		
		virtual void update (sf::Time dt);
		virtual void handleEvent (sf::Event &e);
		virtual void draw (sf::RenderTarget &target, sf::RenderStates states) const;

	private:
		std::vector<GUINode *> guiElements;
	};
}
#endif

