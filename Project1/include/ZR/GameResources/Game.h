//
//  Game.h
//
//
//  Created by Zachary Ross on 7/10/15.
//
//

#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <ZR/GameResources/Resources.h>

class Game
{
public:
	Game();
	void    run();

private:
	void    processEvents();
	void    update(sf::Time);
	void    render();
};

#endif
