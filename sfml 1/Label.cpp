#include "stdafx.h"
#include "Label.h"

Label::Label() : visible(false)
{
	rc.setPosition(0, 0);
	rc.setFillColor(sf::Color(0, 0, 0, 100));
	rc.setSize(sf::Vector2f(100, 50));
}

Label::Label(sf::Font &font, float x, float y, float w, float h, std::string txt = "")
	:visible(false)
{
	rc.setPosition(x, y);
	rc.setSize(sf::Vector2f(w, h));
	rc.setFillColor(sf::Color(0, 0, 0, 100));
	text.setFont(font);
	text.setString(txt);
	text.setPosition(x+2, y+2);
}

void Label::draw(sf::RenderWindow &window) const
{
	window.draw(rc);
	window.draw(text);
}

void Label::setFont(sf::Font &font) {
	text.setFont(font);
}

void Label::setPos(float x, float y) {
	//If new pos is smaller then the current then - else +
	float xDif = rc.getPosition().x - x;
	float yDif = rc.getPosition().y - y;

	if (xDif <= 0) {
		rc.setPosition(rc.getPosition().x - xDif, rc.getPosition().y);
		text.setPosition(rc.getPosition().x - xDif, text.getPosition().y);
	}
	else {
		rc.setPosition(rc.getPosition().x + xDif, rc.getPosition().y);
		text.setPosition(rc.getPosition().x + xDif, text.getPosition().y);
	}
	if (yDif <= 0) {
		rc.setPosition(rc.getPosition().x, rc.getPosition().y - yDif);
		text.setPosition(text.getPosition().x, rc.getPosition().y - yDif);
	}
	else {
		rc.setPosition(rc.getPosition().x, rc.getPosition().y + yDif);
		text.setPosition(text.getPosition().x, rc.getPosition().y + yDif);
	}
}

void Label::setSize(float w, float h) {
	rc.setSize(sf::Vector2f(w, h));
}

void Label::setText(std::string txt) {
	text.setString(txt);
}

void Label::setTextPos(float x, float y) {
	text.setPosition(x, y);
}