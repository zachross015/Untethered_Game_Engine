#ifndef ANIMATION_H
#define ANIMATION_H
#include <ZR/Mutable/Drawable.h>
#include <ZR/Physics/PhysicsVariables.h>
#include <ZR/Physics/PhysicsObject.h>

namespace zr
{

	/////////////////////////////////////////////////////////////////////////////////
	// The purpose of this class is to simplify the process of animating a sprite
	// by providing methods that load a sprite sheet and determine the speed, frame
	// count, and y position of the sprite sheet that the animation begins at.
	//
	// Copyright © 2016 Zachary Ross. All rights reserved.
	/////////////////////////////////////////////////////////////////////////////////
	class Animation :
		public Drawable
	{
	public:
		//
		// Default Class Constructor
		//
		Animation();

		//
		// Default Class Deconstructor
		//
		~Animation();

		//
		// Function that starts the animation from the index that it is set to
		//
		void play();

		//
		// Function that stops the animation cycle and sets the index to 0
		//
		void stop();

		//
		// Function that sets the spritesheet image texture
		// @param texture is the spritesheet that the animation is set to
		//
		void setTextureImage(sf::Texture *texture);

		//
		// Function that sets the current position of the sprite
		// @param pos is the position that the sprite will be set to
		//
		void setPosition(sf::Vector2f pos) { s.setPosition(pos); }

		//
		// Function that gets the current position of the sprite
		// @result returns the current position
		//
		sf::Vector2f getPosition() { return s.getPosition(); }

		//
		// Function that sets the scale of the sprite
		// @param x sets the x value of the scale
		// @param y sets the y value of the scale
		//
		void setScale(sf::Vector2f f) { s.setScale(f); };

		//
		// Functions that gets the current scale of the sprite
		// @result returns the scale used by the sprite
		//
		sf::Vector2f getScale() { return s.getScale(); }

		//
		// Function that set the rotation of the sprite
		// @param angle sets the current angle of the sprite
		//
		void setRotation(float angle);

		//
		// Function that sets the rotation of the sprite relative to the current angle
		// @param angle sets the current angle of the sprite relative to the current angle
		//
		void rotate(float angle);

		//
		// Functions that sets the origin of the sprite. This is used
		// for determining all translation based changes to the sprite
		// @param f sets the coordinates to this vector
		//
		void setOrigin(sf::Vector2f f) { s.setOrigin(f); }

		//
		// Function that sets the texture size for each animation
		// frame on the spritesheet
		// @param size is the size of the texture (not the spritesheet)
		//
		void setImageSize(sf::Vector2f size) { animSize = size; }

		//
		// Function that gets the texture size for the animation
		// @result returns the size of the texture (not the spritesheet)
		//
		sf::Vector2f getImageSize() { return animSize; }

		//Set the y coordinate of the animation inside the spritesheet
		//It will be multiplied by the Y value of the image size

		//
		// Function that sets the rate at which the cycle animates (in milliseconds)
		// @param s is the speed for the animation to be set to
		//
		void setSpeed(int s) { speed = s; }

		//
		// Function that gets the rate at which the cycle animates (in milliseconds)
		// @param returns the speed for the animation
		//
		int getSpeed() { return speed; }

		//
		// Function that sets the amount of frames in the cycle
		// @param frm is the amount of frames
		//
		void setFrameCount(int frm) { frames = frm - 1; }

		//
		// Function that gets the amount of frames in the cycle
		// @result returns the amount of frames
		//
		int getFrameCount() { return frames; }

		//
		// Function sets whether or not the animation will loop
		// @param l is the boolean to determine whether or not it loops
		//
		void setLoop(bool l) { loop = l; }

		//
		// Function gets whether or not the animation will loop
		// @result returns the boolean to determine whether or not it loops
		//
		bool getLoop() { return loop; }

		//
		// Function that determines if the animation did reach the end
		// at least once, and is reset after stop() is called
		// @result returns if the animation did finish
		//
		bool didFinishAnimating() { return animationFinished; }

		//
		// Function that determines if the animation is playing
		// @result returns the animation's state
		//
		bool playing() { return isPlaying; }

		//
		// Function called every frame that is meant to handle frame based
		// movements and updates in translations.
		// @param dT is the delta time, or time between each frame.
		//
		virtual void update(sf::Time dT);

		//
		// Function called every frame that is meant to handle frame based
		// event occurences such as key presses or button presses
		// @param e is a reference to the event that has occurred
		//
		virtual void handleEvent(sf::Event &e);

		//
		// Function called every frame that is meant to handle frame based
		// drawing to the screen
		// @param target is a reference to the RenderWindow that sf::Drawable objects
		// are drawn to
		// @param states is the states that the RenderWindow contains
		//
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

		//
		// Function that loads all of the default settings and the image
		// texture used for the animation. This will set the speed,
		// Image Size, and Frame Count to the default settings.
		// The format is as follows for the filename: item_category NO EXTENSION
		// @param filename is the name of the file to load. The only accepted
		// format is category_subcategory
		//
		bool loadFromFile(std::string filename);
        
        //
        // Function that determines whether or not an animation contains
        // collision information
        // 
        bool hasBounds();
        
        //
        // Function that appends a collision object to the current bounds
        // held by the animation. Any bounds that exceed the frame count will not
        // be used.
        // @param p is the CollisionObject bounds to be used
        //
        void addAnimationBounds(CollisionObject p);
        
        //
        // Function that sets the animation bounds at a certain frame,
        // given the frame exists
        // @param index is the index of the frame to set the bounds to
        // @param p is a pointer to the physics object to set the polygon
        // bounds to
        //
        void setAnimationBoundsForFrame(int index, CollisionObject p);
        
        //
        // Function that sets the animation bounds for all frames. Any
        // frame that goes beyond the amount of frames in the animation
        // will never be reached. If the frame amount is too low, the
        // rest of the frames will be filled with null CollisionObjects
        // @param vp is the vector of physics objects to set the bounds
        // to
        //
        void setAllAnimationBounds(std::vector<CollisionObject> vp);
        
        //
        // Function that returns a pointer to the current PhysicsObject Being Used
        // @result returns a pointer to the current polygon
        //
        CollisionObject* getCurrentPolygon() { return currentPolygon; }
        
        //
        // Function that returns a reference of the vector of polygons
        // @result returns the reference to the vector
        //
        std::vector<CollisionObject>& getAllPolygons();
        
        void resetPolygon();
        
	protected:
		int currentIndex = 0;
		int speed = 0;
		bool isPlaying = false;
		bool loop = true;
		int frames = 3;
		sf::Texture *tImg;
		bool animationFinished = false;
		sf::Vector2f animSize = { 16,16 };
        CollisionObject *currentPolygon;
        std::vector<CollisionObject> polygonBounds;
        
	private:
		sf::Sprite s;
		float counter;
		
	};
}
#endif