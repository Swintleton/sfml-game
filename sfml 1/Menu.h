#pragma once
#include "MenuItem.h"

#define ITEMS_COUNT 3

class Menu
{
public:
	Menu(float, float, sf::Font &font);

	void draw(sf::RenderWindow &) const;
	void moveUp();
	void moveDown();
	void update(sf::RenderWindow &, sf::Event &);
	void updatePos(sf::Vector2f, float);
	void setSelectedItem(unsigned short index);

	bool visible;
private:
	unsigned short selectedItemIndex;

	std::vector<MenuItem> menu;
};