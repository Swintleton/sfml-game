#include "stdafx.h"
#include "TextBox.h"

TextBox::TextBox(sf::Font &font, float posX, float posY)
	: selected(false)
{
	rc.setSize(sf::Vector2f(185, 26));
	rc.setFillColor(sf::Color::Black);
	rc.setPosition(posX, posY);

	text.setFillColor(sf::Color::White);
	text.setCharacterSize(14);
	text.setPosition(posX + 10, posY + 4);
	text.setFont(font);
}

void TextBox::draw(sf::RenderWindow &window) const {
	window.draw(rc);
	window.draw(text);
}

bool TextBox::update(sf::RenderWindow &window, sf::Event &event) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		//This textbox is selected by mouse?
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
		if (event.type == sf::Event::TextEntered) {
			//Ignore: nothing, enter, tab
			if (event.text.unicode == '\0' || event.text.unicode == 13 || event.text.unicode == '\t') {}
			//Backspace
			else if (event.text.unicode == 8) {
				input = input.substring(0, input.getSize() - 1);
				text.setString(input);
			}
			//Any other input
			else if (text.getLocalBounds().width < 160) {
				input += event.text.unicode;
				text.setString(input);
			}
		}
		rc.setFillColor(sf::Color::Red);
		return 1;
	}
	rc.setFillColor(sf::Color::Black);
	return 0;
}

std::string TextBox::getText() const {
	return input;
}

float TextBox::getWidth() const {
	return text.getLocalBounds().width;
}

void TextBox::setText(std::string txt) {
	input = txt;
	text.setString(txt);
}

void TextBox::setPosition(float x, float y) {
	rc.setPosition(x, y);
	text.setPosition(x, y);
}
