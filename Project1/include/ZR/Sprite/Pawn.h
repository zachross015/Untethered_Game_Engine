#ifndef PAWN_H
#define PAWN_H
#include <ZR/Sprite/Actor.h>

namespace zr
{
	class Pawn :
		public Actor
	{
	public:
		Pawn();
		~Pawn();

		virtual void update(sf::Time dT);
		virtual void handleEvent(sf::Event &e);
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	private:
		bool upPressed = false, downPressed = false, leftPressed = false, rightPressed = false;
	};
}
#endif