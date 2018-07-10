#include "stdafx.h"
#include "MessageList.h"

MessageList::MessageList()
	: selected(false), visibleUntil(11), scrollBar()
{
	normalColor = sf::Color(80, 80, 80, 200);
	selectedColor = sf::Color(50, 50, 150, 200);

	rc.setSize(sf::Vector2f(250, 200));
	rc.setFillColor(normalColor);

	text.setFillColor(sf::Color::White);
	text.setCharacterSize(14);
}

void MessageList::addMessage(char *msg) {
	messages.push_back(msg);
	std::string input = "";
	unsigned int i = 0;

	//If there are more messages, than visible
	if (messages.size() > visibleUntil)
		i = messages.size() - visibleUntil;

	for (; i < messages.size(); ++i) {
		input += messages[i];
		if (i + 1<messages.size())
			input += "\n";
	}

	text.setString(input);
	if (messages.size() < visibleUntil + 1)
		text.setPosition(text.getPosition().x, text.getPosition().y - 16);
}

void MessageList::draw(sf::RenderWindow &window) const {
	window.draw(rc);
	window.draw(text);
	scrollBar.draw(window);
}

void MessageList::setFont(sf::Font &font) {
	text.setFont(font);
}

void MessageList::setPosition(float x, float y) {
	rc.setPosition(x, y);
	if(messages.size() < visibleUntil)
		text.setPosition(x + 5, y + (193 - messages.size() * 16));
	else
		text.setPosition(x + 5, y + (193 - visibleUntil * 16));
	scrollBar.setPosition(x + rc.getLocalBounds().width, y + rc.getLocalBounds().height);
	scrollBar.setBox(rc.getPosition(), rc.getSize());
}

void MessageList::update(sf::RenderWindow &window, sf::Uint32 pressedKey) {
	sf::Vector2f mousePos = { (float)sf::Mouse::getPosition(window).x - window.getSize().x / 2, (float)sf::Mouse::getPosition(window).y - window.getSize().y / 2 };
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && rc.getGlobalBounds().contains(mousePos)) {
		selected = true;
		rc.setFillColor(selectedColor);
		scrollBar.update(window);
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || pressedKey == sf::Keyboard::Tab) {
		selected = false;
		rc.setFillColor(normalColor);
		scrollBar.setNormalColor();
	}
}