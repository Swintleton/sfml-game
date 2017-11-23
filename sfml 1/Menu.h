#pragma once

#include <SFML/Graphics.hpp>

#define ITEMS_COUNT 3

class Menu
{
public:
	Menu(float, float);
	virtual ~Menu();

	void draw(sf::RenderWindow &);
	void moveUp();
	void moveDown();
	std::vector<float> getPosition(int, sf::RenderWindow &);
	void setSelectedItem(unsigned short index);
private:
	unsigned short selectedItemIndex;
	sf::Font font;
	sf::Text menu[ITEMS_COUNT];
};