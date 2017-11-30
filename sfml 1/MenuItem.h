#pragma once
#ifndef SFML_GRAPHICS_H
#define SFML_GRAPHICS_H
#include <SFML/Graphics.hpp>
#endif

class MenuItem
{
public:
	MenuItem(sf::Vector2f, sf::Vector2f, sf::Font &, char*);
	void draw(sf::RenderWindow &) const;
	void update(float, float);
	void setColor(const sf::Color);

	sf::RectangleShape rc;
private:
	sf::Text text;
};
