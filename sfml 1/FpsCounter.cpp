#include "stdafx.h"
#include "FpsCounter.h"

FpsCounter::FpsCounter()
	:deltaTime(0), frameCount(0), visible(false)
{
	text.setFillColor(sf::Color::White);
	text.setString("");
	text.setCharacterSize(14);
}

void FpsCounter::draw(sf::RenderWindow &window) const {
	window.draw(text);
}

float FpsCounter::getFPS(void) {
	return frameCount;
}

void FpsCounter::setFont(sf::Font &font) {
	text.setFont(font);
}

void FpsCounter::setPosition(float x, float y) {
	text.setPosition(x, y);
}

void FpsCounter::setPosition(sf::Vector2f pos) {
	text.setPosition(pos.x, pos.y);
}

void FpsCounter::update(float time) {
	++frameCount;
	deltaTime += time;
	if (deltaTime >= 1) {
		text.setString(std::to_string(frameCount));
		deltaTime -= 1;
		frameCount = 0;
	}
}