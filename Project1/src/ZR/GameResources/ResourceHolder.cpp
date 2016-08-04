//
//  ResourceHolder.cpp
//  New Game
//
//  Created by Zachary Ross on 9/18/15.
//  Copyright (c) 2015 Zachary Ross. All rights reserved.
//

#include <ZR/GameResources/ResourceHolder.h>
#include <ZR/Sprite/Animation.h>
#include <SFML/Audio.hpp>

zr::ResourceHolder<sf::Font, std::string> Fonts;
zr::ResourceHolder<sf::Texture, std::string> Textures;
zr::ResourceHolder<sf::Image, std::string> Images;
zr::ResourceHolder<sf::SoundBuffer, std::string> Sounds;
zr::ResourceHolder<zr::Animation, std::string> Animations;