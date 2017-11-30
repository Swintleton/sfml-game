#pragma once
#ifndef SFML_GRAPHICS_H
#define SFML_GRAPHICS_H
#include <SFML/Graphics.hpp>
#endif
#include <iostream>

static sf::Font font;
static sf::Texture texture_Wall_0;
static sf::Texture texture_Wall_1;

void load() {
	if (!font.loadFromFile("Fonts/arial.ttf")) {
		std::cout << "Error: can't load Fonts/arial.ttf" << std::endl;
	}
	if (!texture_Wall_0.loadFromFile("Textures/walls/wall0.bmp")) {
		std::cout << "Error: can't load Textures/walls/wall0.bmp" << std::endl;
	}
	if (!texture_Wall_1.loadFromFile("Textures/walls/wall1.bmp")) {
		std::cout << "Error: can't load Textures/walls/wall1.bmp" << std::endl;
	}
}
