#pragma once
#include "MenuItem.h"
#include "Globals.h"

#define ITEMS_COUNT 3

class Menu
{
public:
	Menu(float, float, sf::Font &font);

	void draw(sf::RenderWindow &) const;
	void moveUp();
	void moveDown();
	bool update(sf::RenderWindow &);
	void updatePos(sf::Vector2f, float);
	void setSelectedItem(sf::Uint8);

	bool visible;
private:
	sf::Uint8 selectedItemIndex;

	std::vector<MenuItem> menu;
};