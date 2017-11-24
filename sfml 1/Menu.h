#pragma once

#include <SFML/Graphics.hpp>

#define ITEMS_COUNT 3

class Menu
{
public:
	Menu(float, float);
	virtual ~Menu();

	void draw(sf::RenderWindow &) const;
	void moveUp();
	void moveDown();
	void update(sf::Vector2f, float, sf::RenderWindow &);
	void setSelectedItem(unsigned short index);
private:
	unsigned short selectedItemIndex;
	sf::Font font;
	sf::Text menu[ITEMS_COUNT];
	sf::RectangleShape rcs[ITEMS_COUNT];
};