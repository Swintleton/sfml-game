#include "stdafx.h"
#include "Button_K.h"

Button_K::Button_K()
{
	rc.setSize(sf::Vector2f(55, 26));
	rc.setFillColor(sf::Color::Black);
	rc.setPosition(0, 0);

	text.setFillColor(sf::Color::White);
	text.setCharacterSize(14);
	text.setPosition(10, 4);
}

Button_K::Button_K(sf::Font &font, float posX, float posY, std::string txt)
	: selected(false)
{
	rc.setSize(sf::Vector2f(55, 26));
	rc.setFillColor(sf::Color::Black);
	rc.setPosition(posX, posY);

	text.setFillColor(sf::Color::White);
	text.setCharacterSize(14);
	text.setPosition(posX + 10, posY + 4);
	text.setFont(font);
	text.setString(txt);
}

bool Button_K::update(sf::RenderWindow &window) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		//This Button is selected by mouse?
		if(rc.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
			selected = true;
		//Lost selection by mouse?
		else {
			selected = false;
			rc.setFillColor(sf::Color::Black);
			return 0;
		}
	}
	if (selected) {
		rc.setFillColor(sf::Color::Red);
		return 1;
	}
	rc.setFillColor(sf::Color::Black);
	return 0;
}

bool Button_K::isPressed(sf::RenderWindow &window, sf::Event &event) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && rc.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))) || (event.type == sf::Event::TextEntered && event.text.unicode == 13))
		return true;
	return false;
}

float Button_K::getWidth() const {
	return text.getLocalBounds().width;
}

void Button_K::draw(sf::RenderWindow &window) const {
	window.draw(rc);
	window.draw(text);
}

void Button_K::setFont(sf::Font &font) {
	text.setFont(font);
}

void Button_K::setPos(float x, float y) {
	rc.setPosition(x, y);
	text.setPosition(x + 10, y + 4);
}

void Button_K::setSize(float w, float h) {
	rc.setSize(sf::Vector2f(w, h));
}

void Button_K::setText(std::string txt) {
	text.setString(txt);
}
