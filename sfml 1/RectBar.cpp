#include "stdafx.h"
#include "RectBar.h"

RectBar::RectBar(float x, float y)
{
	collisionRect.setPosition(x, y);
	collisionRect.setSize(sf::Vector2f(70, 10));

	border.setPosition(x, y);
	border.setSize(sf::Vector2f(70, 10));

	//effect.setPosition(x, y);
	//effect.setRadius(50);

	text.setString("");
}

void RectBar::draw(sf::RenderWindow &window) const {
	window.draw(collisionRect);
	//window.draw(border);
	//window.draw(effect);
	window.draw(text);
}

void RectBar::setFont(sf::Font &font) {
	text.setFont(font);
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(11);
	text.setPosition(collisionRect.getPosition().x + collisionRect.getLocalBounds().width / 2 - text.getLocalBounds().width / 2, collisionRect.getPosition().y + collisionRect.getLocalBounds().height / 2 - text.getLocalBounds().height);
}

void RectBar::setPosition(float x, float y) {
	collisionRect.setPosition(x, y);
	//border.setPosition(x, y);
	//effect.setPosition(x, y);
	text.setPosition(collisionRect.getPosition().x + collisionRect.getLocalBounds().width / 2 - text.getLocalBounds().width / 2, collisionRect.getPosition().y + collisionRect.getLocalBounds().height / 2 - text.getLocalBounds().height);
}

void RectBar::setSize(float x, float y) {
	collisionRect.setSize(sf::Vector2f(x, y));
	border.setSize(sf::Vector2f(x, y));
}

void RectBar::setText(float value) {
	std::string txt = std::to_string(static_cast<long>(value));
	text.setString(txt);
	if(txt.size() > 0)
		text.setPosition(collisionRect.getPosition().x + 35 - txt.size(), collisionRect.getPosition().y - 2);
	else
		text.setPosition(collisionRect.getPosition().x + 35 - txt.size()+1, collisionRect.getPosition().y - 2);
}

void RectBar::setText(std::string txt) {
	text.setString(txt);
	text.setPosition(collisionRect.getPosition().x + collisionRect.getLocalBounds().width / 2 - text.getLocalBounds().width / 2, collisionRect.getPosition().y + collisionRect.getLocalBounds().height / 2 - text.getLocalBounds().height);
}

void RectBar::setTexture(sf::Texture &Texture) {
	collisionRect.setTexture(&Texture);
	collisionRect.setTextureRect(sf::IntRect(0, 0, 70, 10));
}

void RectBar::setBorderTexture(sf::Texture &Texture) {
	border.setTexture(&Texture);
}

void RectBar::setEffectTexture(sf::Texture &Texture) {
	//effect.setTexture(&Texture);
}

void RectBar::setValue(float x) {
	collisionRect.setTextureRect(sf::IntRect(0.7f * (100 - x), 0, 70, 10));
}