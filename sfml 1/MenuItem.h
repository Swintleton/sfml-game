#pragma once
#include <SFML/Graphics.hpp>

class MenuItem
{
public:
	MenuItem(sf::Vector2f, sf::Vector2f, sf::Font &, char*);
	void draw(sf::RenderWindow &) const;
	void setColor(const sf::Color);
	void setPosition(float, float);
	sf::RectangleShape rc;
private:
	sf::Text text;
};
