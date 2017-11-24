#include "stdafx.h"
#include "Menu.h"

#include <iostream>

Menu::Menu(float width, float height)
{
	font.loadFromFile("Fonts/arial.ttf");

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Continue");
	menu[0].setPosition(sf::Vector2f(width / 2, height / (ITEMS_COUNT + 1) * 1));

	rcs[0].setFillColor(sf::Color::Black);
	rcs[0].setOrigin(0, -10);
	rcs[0].setPosition(sf::Vector2f(width / 2, height / (ITEMS_COUNT + 1) * 1));
	rcs[0].setSize(sf::Vector2f(120.f,22.f));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Options");
	menu[1].setPosition(sf::Vector2f(width / 2, height / (ITEMS_COUNT + 1) * 2));

	rcs[1].setFillColor(sf::Color::Black);
	rcs[1].setOrigin(0, -10);
	rcs[1].setPosition(sf::Vector2f(width / 2, height / (ITEMS_COUNT + 1) * 2));
	rcs[1].setSize(sf::Vector2f(110.f, 22.f));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Exit");
	menu[2].setPosition(sf::Vector2f(width / 2, height / (ITEMS_COUNT + 1) * 3));

	rcs[2].setFillColor(sf::Color::Black);
	rcs[2].setOrigin(0, -10);
	rcs[2].setPosition(sf::Vector2f(width / 2, height / (ITEMS_COUNT + 1) * 3));
	rcs[2].setSize(sf::Vector2f(54.f, 22.f));

	selectedItemIndex = 0;
}

void Menu::draw(sf::RenderWindow &window) const
{
	for (int i = 0; i < ITEMS_COUNT; i++)
	{
		window.draw(rcs[i]);
		window.draw(menu[i]);
	}
}

void Menu::moveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
	else {
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex = ITEMS_COUNT - 1;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Menu::moveDown()
{
	if (selectedItemIndex < ITEMS_COUNT - 1)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
	else {
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex = 0;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Menu::update(sf::Vector2f pos, float hegiht, sf::RenderWindow &window) {
	menu[0].setPosition(pos.x - 60, pos.y - hegiht / (ITEMS_COUNT * 2));
	menu[1].setPosition(pos.x - 55, pos.y);
	menu[2].setPosition(pos.x - 27, pos.y + hegiht / (ITEMS_COUNT * 2));

	rcs[0].setPosition(pos.x - 60, pos.y - hegiht / (ITEMS_COUNT * 2));
	rcs[1].setPosition(pos.x - 55, pos.y);
	rcs[2].setPosition(pos.x - 27, pos.y + hegiht / (ITEMS_COUNT * 2));

	//std::cout << "Mouse: "<< sf::Mouse::getPosition(window).x <<" "<< sf::Mouse::getPosition(window).y << std::endl;
	//std::cout << "rcs: " << rcs[1].getPosition().x << " " << rcs[1].getPosition().y << std::endl;

	if (rcs[0].getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
		setSelectedItem(0);
	else if (rcs[1].getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
		setSelectedItem(1);
	else if (rcs[2].getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
		setSelectedItem(2);
}

void Menu::setSelectedItem(unsigned short index)
{
	menu[selectedItemIndex].setFillColor(sf::Color::White);
	selectedItemIndex = index;
	menu[selectedItemIndex].setFillColor(sf::Color::Red);
}

Menu::~Menu()
{}
