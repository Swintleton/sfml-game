#include "stdafx.h"
#include "MessageBox.h"

MessageBox::MessageBox()
	: selected(false), sendMsg(""), send(false)
{
	normalColor = sf::Color(0, 0, 0, 200);
	selectedColor = sf::Color(50, 50, 150, 200);

	rc.setSize(sf::Vector2f(250, 26));
	rc.setFillColor(normalColor);

	text.setFillColor(sf::Color::White);
	text.setCharacterSize(14);
}

void MessageBox::setFont(sf::Font &font) {
	text.setFont(font);
}

void MessageBox::setPosition(float x, float y) {
	rc.setPosition(x, y);
	text.setPosition(x + 10, y + 4);
}

void MessageBox::draw(sf::RenderWindow &window) const {
	window.draw(rc);
	window.draw(text);
}

bool MessageBox::update(sf::RenderWindow &window, sf::Event &event) {
	send = false;
	sf::Vector2f mousePos = { (float)sf::Mouse::getPosition(window).x - window.getSize().x / 2, (float)sf::Mouse::getPosition(window).y - window.getSize().y / 2 };
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && rc.getGlobalBounds().contains(mousePos)) {
		selected = true;
		rc.setFillColor(selectedColor);
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || event.text.unicode == sf::Keyboard::Tab) {
		selected = false;
		rc.setFillColor(normalColor);
	}

	if (selected) {
		if (event.type == sf::Event::TextEntered) {
			if (event.text.unicode == 13 && !input.isEmpty()) {
				strcpy_s(sendMsg, static_cast<std::string>(input).c_str());
				send = true;
				input = "";
				text.setString("");
			}
			if (event.text.unicode == 8) {
				input = input.substring(0, input.getSize() - 1);
				text.setString(input);
			}
			else if (event.text.unicode == '\0' || event.text.unicode == 13 || event.text.unicode == 27) {
				return send;
			}
			else if (text.getLocalBounds().width < 220) {
				input += event.text.unicode;
				text.setString(input);
			}
		}
	}
	return send;
}
