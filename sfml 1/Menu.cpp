#include "stdafx.h"
#include "Menu.h"

Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("Fonts/arial.ttf"))
	{}

	menu[0].setFont(font);
	//menu[0].setColor(sf::Color::Red);
	menu[0].setString("Play");
	menu[0].setPosition(sf::Vector2f(width / 2, height / (ITEMS_COUNT + 1) * 1));

	menu[1].setFont(font);
	//menu[1].setColor(sf::Color::White);
	menu[1].setString("Options");
	menu[1].setPosition(sf::Vector2f(width / 2, height / (ITEMS_COUNT + 1) * 2));

	menu[2].setFont(font);
	//menu[2].setColor(sf::Color::White);
	menu[2].setString("Exit");
	menu[2].setPosition(sf::Vector2f(width / 2, height / (ITEMS_COUNT + 1) * 3));
	selectedItemIndex = 0;
}

void Menu::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < ITEMS_COUNT; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::moveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		//menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex--;
		//menu[selectedItemIndex].setColor(sf::Color::Red);
	}
	else {
		//menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex = ITEMS_COUNT - 1;
		//menu[selectedItemIndex].setColor(sf::Color::Red);
	}
}

void Menu::moveDown()
{
	if (selectedItemIndex < ITEMS_COUNT - 1)
	{
		//menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex++;
		//menu[selectedItemIndex].setColor(sf::Color::Red);
	}
	else {
		//menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex = 0;
		//menu[selectedItemIndex].setColor(sf::Color::Red);
	}
}

void Menu::setSelectedItem(unsigned short index)
{
	//menu[selectedItemIndex].setColor(sf::Color::White);
	selectedItemIndex = index;
	//menu[selectedItemIndex].setColor(sf::Color::Red);
}

std::vector<float> Menu::getPosition(int index, sf::RenderWindow &window)
{
	std::vector<float> pos;
	if (index == 0)
		pos = { 400,150 };
	else if (index == 1)
		pos = { 400,300 };
	else if (index == 2)
		pos = { 400,450 };
	return pos;
}

Menu::~Menu()
{

}
