#include "stdafx.h"
#include "Menu.h"
#include <iostream>

Menu::Menu(float width, float height, sf::Font &font) : selectedItemIndex(0),visible(false)
{
	menu.push_back(MenuItem(sf::Vector2f(width / 2, height / (ITEMS_COUNT) * 1), sf::Vector2f(120.f, 22.f), font, "Continue"));
	menu.push_back(MenuItem(sf::Vector2f(width / 2, height / (ITEMS_COUNT) * 2), sf::Vector2f(110.f, 22.f), font, "Options" ));
	menu.push_back(MenuItem(sf::Vector2f(width / 2, height / (ITEMS_COUNT) * 3), sf::Vector2f(54.f , 22.f), font, "Exit"    ));

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

void Menu::update(sf::Vector2f pos, float height, sf::RenderWindow &window, sf::Event &event)
{
//----------------------------------------MENU ITEMS REPOSITIONING---------------------------------------------
	menu[0].update(pos.x - 60, pos.y - height / (ITEMS_COUNT * 2));
	menu[1].update(pos.x - 55, pos.y);
	menu[2].update(pos.x - 27, pos.y + height / (ITEMS_COUNT * 2));
//-------------------------------------------------------------------------------------------------------------
//----------------------------------------MENU ITEMS EVENTS & SELECTIONS----------------------------------------
	if      (selectedItemIndex == 0 && (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Return))) {
		visible = false;
	}
	else if (selectedItemIndex == 1 && (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Return))) {

	}
	else if (selectedItemIndex == 2 && (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Return))) {
		window.close();
	}
	else if (sf::Mouse::getPosition(window).x > (window.getSize().x / 2 - menu[0].rc.getSize().x) && sf::Mouse::getPosition(window).x < (window.getSize().x / 2 + menu[0].rc.getSize().x) && sf::Mouse::getPosition(window).y <= (window.getSize().y / (ITEMS_COUNT)        + menu[0].rc.getSize().y * 1.5f) && sf::Mouse::getPosition(window).y >      (window.getSize().y / (ITEMS_COUNT))) {
		setSelectedItem(0);
	}
	else if (sf::Mouse::getPosition(window).x > (window.getSize().x / 2 - menu[1].rc.getSize().x) && sf::Mouse::getPosition(window).x < (window.getSize().x / 2 + menu[1].rc.getSize().x) && sf::Mouse::getPosition(window).y <= (window.getSize().y / 2                    + menu[1].rc.getSize().y * 1.5f) && sf::Mouse::getPosition(window).y >      (window.getSize().y / 2)) {
		setSelectedItem(1);
	}
	else if (sf::Mouse::getPosition(window).x > (window.getSize().x / 2 - menu[2].rc.getSize().x) && sf::Mouse::getPosition(window).x < (window.getSize().x / 2 + menu[2].rc.getSize().x) && sf::Mouse::getPosition(window).y <= 2 * (window.getSize().y / (ITEMS_COUNT)    + menu[2].rc.getSize().y * 1.5f) && sf::Mouse::getPosition(window).y > 2 *  (window.getSize().y / (ITEMS_COUNT))) {
		setSelectedItem(2);
	}
//-------------------------------------------------------------------------------------------------------------
}

void Menu::setSelectedItem(unsigned short index) {
	menu[selectedItemIndex].setColor(sf::Color::White);
	selectedItemIndex = index;
	menu[selectedItemIndex].setColor(sf::Color::Red);
}
