#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H
#include <ZR/Physics/CollisionObject.h>
namespace zr
{
	class PhysicsObject :
		public CollisionObject,
		public PhysicsVariables
	{
	public:
		PhysicsObject();
		~PhysicsObject();

		virtual void update(sf::Time dT);
	};
}
#endif

