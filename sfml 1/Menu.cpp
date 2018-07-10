#include "stdafx.h"
#include "Menu.h"
#include <iostream>

Menu::Menu(float width, float height, sf::Font &font) : selectedItemIndex(0), visible(false)
{
	menu.push_back(MenuItem(sf::Vector2f(width / 2, height / (ITEMS_COUNT) * 1), sf::Vector2f(120.f, 22.f), font, "Continue"));
	menu.push_back(MenuItem(sf::Vector2f(width / 2, height / (ITEMS_COUNT) * 2), sf::Vector2f(110.f, 22.f), font, "Options"));
	menu.push_back(MenuItem(sf::Vector2f(width / 2, height / (ITEMS_COUNT) * 3), sf::Vector2f(54.f, 22.f), font, "Exit"));

	setSelectedItem(0);
}

void Menu::draw(sf::RenderWindow &window) const {
	for (MenuItem const &mi : menu)
		mi.draw(window);
}

void Menu::moveUp() {
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setColor(sf::Color::Red);
	}
	else {
		menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex = ITEMS_COUNT - 1;
		menu[selectedItemIndex].setColor(sf::Color::Red);
	}
}

void Menu::moveDown() {
	if (selectedItemIndex < ITEMS_COUNT - 1)
	{
		menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setColor(sf::Color::Red);
	}
	else {
		menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex = 0;
		menu[selectedItemIndex].setColor(sf::Color::Red);
	}
}

bool Menu::update(sf::RenderWindow &window)
{
	//SELECTIONS
	sf::Vector2f MousePos(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

	if (menu[0].rc.getGlobalBounds().contains(MousePos)) {
		setSelectedItem(0);
	}
	else if (menu[1].rc.getGlobalBounds().contains(MousePos)) {
		setSelectedItem(1);
	}
	else if (menu[2].rc.getGlobalBounds().contains(MousePos)) {
		setSelectedItem(2);
	}

	//EVENTS
	if ((!sf::Mouse::isButtonPressed(sf::Mouse::Left) || !menu[selectedItemIndex].rc.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		return 0;

	//Continue
	if (selectedItemIndex == 0) {
		visible = false;
		return 1;
	}
	//Options
	if (selectedItemIndex == 1) {
		return 1;
	}
	//Exit
	if (selectedItemIndex == 2) {
		globalMutex.lock();
		quit = true;
		globalMutex.unlock();
		window.close();
		return 1;
	}
}

void Menu::updatePos(sf::Vector2f pos, float height) {
	menu[0].setPosition(pos.x - 60, pos.y - height / (ITEMS_COUNT * 2));
	menu[1].setPosition(pos.x - 55, pos.y);
	menu[2].setPosition(pos.x - 27, pos.y + height / (ITEMS_COUNT * 2));
}

void Menu::setSelectedItem(sf::Uint8 index) {
	menu[selectedItemIndex].setColor(sf::Color::White);
	selectedItemIndex = index;
	menu[selectedItemIndex].setColor(sf::Color::Red);
}
