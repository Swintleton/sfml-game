#pragma once
#include <SFML/Graphics.hpp>

class ScrollBar
{
public:
    sf::RectangleShape collisionRect;
	sf::RectangleShape rc;
    float value;

	ScrollBar();
    void draw(sf::RenderWindow &) const;
	void setBox(sf::Vector2f boxPos, sf::Vector2f boxSize);
	void setNormalColor();
	void setSelectedColor();
	void setPosition(float, float);
    void update(sf::RenderWindow &);
private:
    sf::Color selectedColor;
    sf::Color normalColor;

    float maxY;
    float minY;
};
