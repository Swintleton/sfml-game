#include "stdafx.h"
#include "ScrollBar.h"
#include <iostream>

ScrollBar::ScrollBar()
{
	normalColor = sf::Color(50, 50, 150);
	selectedColor = sf::Color(10, 10, 100);

	rc.setFillColor(normalColor);
	rc.setSize(sf::Vector2f(15, 40));
	rc.setOrigin(rc.getLocalBounds().width / 2, rc.getLocalBounds().height / 2);
	collisionRect.setOrigin(collisionRect.getLocalBounds().width / 2, collisionRect.getLocalBounds().height / 2);
}

void ScrollBar::draw(sf::RenderWindow &window) const
{
    window.draw(rc);
}

void ScrollBar::setBox(sf::Vector2f _boxPos, sf::Vector2f _boxSize) {
	collisionRect.setSize(sf::Vector2f(rc.getLocalBounds().width * 8, _boxSize.y * 2));
	collisionRect.setOrigin(collisionRect.getLocalBounds().width / 2, collisionRect.getLocalBounds().height / 2);

	maxY = _boxPos.y + rc.getLocalBounds().height / 2;
	minY = _boxPos.y + _boxSize.y - rc.getLocalBounds().height / 2;
}

void ScrollBar::setNormalColor() {
	rc.setFillColor(normalColor);
}

void ScrollBar::setSelectedColor() {
	rc.setFillColor(selectedColor);
}

void ScrollBar::setPosition(float x, float y) {
	rc.setPosition(x, y - rc.getLocalBounds().height / 2);
	collisionRect.setPosition(x, y - rc.getLocalBounds().height / 2);
}

void ScrollBar::update(sf::RenderWindow &window){
	sf::Vector2f mousePos = { (float)sf::Mouse::getPosition(window).x - window.getSize().x / 2, (float)sf::Mouse::getPosition(window).y - window.getSize().y / 2 };

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && collisionRect.getGlobalBounds().contains(mousePos)){
        sf::Vector2f oldPos = rc.getPosition();
        rc.setPosition(rc.getPosition().x, mousePos.y);
        collisionRect.setPosition(rc.getPosition().x, mousePos.y);

        if(rc.getPosition().y < maxY){
            //Upper border
            rc.setPosition(oldPos.x, maxY);
            collisionRect.setPosition(oldPos.x, maxY);
            return;
        }
        if(rc.getPosition().y > minY){
            //Downer border
            rc.setPosition(oldPos.x, minY);
            collisionRect.setPosition(oldPos.x, minY);
            return;
        }
		rc.setFillColor(selectedColor);
		value = (rc.getPosition().y - maxY) / (minY - maxY);
    }
	else
		rc.setFillColor(normalColor);
}
