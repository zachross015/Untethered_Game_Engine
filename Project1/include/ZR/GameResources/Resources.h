#ifndef RESOURCES_H
#define RESOURCES_H
#include <ZR/GameResources/ResourceHolder.h>
#include <ZR/Scene.h>
#include <ZR/Sprite/Actor.h>

extern sf::RenderWindow *Window;
extern zr::ResourceHolder<sf::Font, std::string> Fonts;
extern zr::ResourceHolder<sf::Texture, std::string> Textures;
extern zr::ResourceHolder<sf::Image, std::string> Images;
extern zr::ResourceHolder<sf::SoundBuffer, std::string> Sounds;
extern zr::ResourceHolder<zr::Animation, std::string> Animations;
extern zr::Scene *CurrentScene;

#endif