#ifndef COUNTER_H
#define COUNTER_H
#include <SFML/Graphics.hpp>

namespace zr
{
	/////////////////////////////////////////////////////////////////////////////////
	// The purpose for this struct is to provide
	// a place to organize a Timer, which will be given an end time
	// and will count every frame until it reaches the end. Once it reaches the end,
	// didReachEnd() will return true.
	// THIS MUST BE INCREMENTED IN AN UPDATE FUNCTION
	//
	// Copyright © 2016 Zachary Ross. All rights reserved.
	/////////////////////////////////////////////////////////////////////////////////
	struct Counter : public sf::Time
	{
		//
		// Default struct constructor
		// @param t sets the end point of time
		//
		Counter(sf::Time t) : Time(sf::Time::Zero), end(t) {}

		//
		// Variable used for determining when the counter
		// will end
		//
		Time end;

		//
		// Function for determining if the timer did reach
		// the end
		// @result returns if the timer reached the end
		//
		bool didReachEnd() { return asMilliseconds() >= end.asMilliseconds(); }
	};
}
#endif