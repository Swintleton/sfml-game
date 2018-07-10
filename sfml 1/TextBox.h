#pragma once
#include <SFML/Graphics.hpp>

class TextBox
{
public:
	TextBox(sf::Font &, float, float);
	void draw(sf::RenderWindow &) const;
	bool update(sf::RenderWindow &, sf::Event &);

	std::string getText() const;
	float getWidth() const;

	void setText(std::string);
	void setPosition(float, float);

	bool selected;
	sf::RectangleShape rc;
private:
	sf::String input;
	sf::Text text;
};
