#pragma once
#include "MenuItem.h"
#include "Globals.h"

const unsigned short ITEMS_COUNT = 3;

class Menu
{
public:
	Menu(float, float, sf::Font &font);

	void draw(sf::RenderWindow &) const;
	void moveUp();
	void moveDown();
	sf::Uint8 update(sf::RenderWindow &);
	void updatePos(sf::Vector2f, float);
	void setSelectedItem(sf::Uint8);

	bool visible;
private:
	sf::Uint8 selectedItemIndex;

	std::vector<MenuItem> menu;
};