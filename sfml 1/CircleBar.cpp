#include "stdafx.h"
#include "CircleBar.h"

CircleBar::CircleBar(float x, float y)
{
	collisionCircle.setPosition(x, y);
	collisionCircle.setRadius(50);

	border.setPosition(x, y);
	border.setRadius(50);

	effect.setPosition(x, y);
	effect.setRadius(50);
}

void CircleBar::draw(sf::RenderWindow &window) const {
	window.draw(collisionCircle);
	window.draw(border);
	window.draw(effect);
	window.draw(text);
}

bool CircleBar::hovered(sf::RenderWindow &window) {
	sf::Vector2f mousePos = { (float)sf::Mouse::getPosition(window).x - window.getSize().x / 2, (float)sf::Mouse::getPosition(window).y - window.getSize().y / 2 };
	if (collisionCircle.getGlobalBounds().contains(mousePos))
		return true;
	return false;
}

void CircleBar::setFont(sf::Font &font) {
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(14);
	text.setPosition(collisionCircle.getPosition().x + collisionCircle.getLocalBounds().width / 2 - text.getLocalBounds().width / 2, collisionCircle.getPosition().y + collisionCircle.getLocalBounds().height / 2 - text.getLocalBounds().height);
	text.setFont(font);
}

void CircleBar::setPosition(float x, float y) {
	collisionCircle.setPosition(x, y);
	border.setPosition(x, y);
	effect.setPosition(x, y);
	text.setPosition(collisionCircle.getPosition().x + collisionCircle.getLocalBounds().width / 2 - text.getLocalBounds().width / 2, collisionCircle.getPosition().y + collisionCircle.getLocalBounds().height / 2 - text.getLocalBounds().height);
}

void CircleBar::setPosition(sf::Vector2f &pos) {
	collisionCircle.setPosition(pos.x, pos.y);
	border.setPosition(pos.x, pos.y);
	effect.setPosition(pos.x, pos.y);
	text.setPosition(collisionCircle.getPosition().x + collisionCircle.getLocalBounds().width / 2 - text.getLocalBounds().width / 2, collisionCircle.getPosition().y + collisionCircle.getLocalBounds().height / 2 - text.getLocalBounds().height);
}

void CircleBar::setRadius(float r) {
	collisionCircle.setRadius(r);
	border.setRadius(r);
	effect.setRadius(r);
}

void CircleBar::setText(float value) {
	text.setString(std::to_string(static_cast<long long>(value)));
	text.setPosition(collisionCircle.getPosition().x + collisionCircle.getLocalBounds().width / 2 - text.getLocalBounds().width / 2, collisionCircle.getPosition().y + collisionCircle.getLocalBounds().height / 2 - text.getLocalBounds().height);
}

void CircleBar::setText(std::string txt) {
	text.setString(txt);
	text.setPosition(collisionCircle.getPosition().x + collisionCircle.getLocalBounds().width / 2 - text.getLocalBounds().width / 2, collisionCircle.getPosition().y + collisionCircle.getLocalBounds().height / 2 - text.getLocalBounds().height);
}

void CircleBar::setTexture(sf::Texture &Texture) {
	Texture.setSmooth(true);
	collisionCircle.setTexture(&Texture);
	collisionCircle.setTextureRect(sf::IntRect(50, 101, 100, 100));
}

void CircleBar::setBorderTexture(sf::Texture &Texture) {
	Texture.setSmooth(true);
	border.setTexture(&Texture);
}

void CircleBar::setEffectTexture(sf::Texture &Texture) {
	Texture.setSmooth(true);
	effect.setTexture(&Texture);
}

void CircleBar::setSize(float r) {
	collisionCircle.setRadius(r);
	border.setRadius(r);
	effect.setRadius(r);
}

void CircleBar::setValue(float y) {
	collisionCircle.setTextureRect(sf::IntRect(50, y+1, 100, 100));
}