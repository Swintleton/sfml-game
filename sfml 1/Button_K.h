#pragma once
#include <SFML/Graphics.hpp>

class Button_K
{
public:
	bool selected;
	bool visible;
	sf::RectangleShape rc;

	Button_K();
	Button_K(sf::Font &, float x, float y, std::string txt);
	bool update(sf::RenderWindow &);
	void draw(sf::RenderWindow &) const;

	float getWidth() const;
	bool isPressed(sf::RenderWindow &window, sf::Event &);
	void setFont(sf::Font &);
	void setPos(float x, float y);
	void setSize(float w, float h);
	void setText(std::string txt);
private:
	
	sf::Text text;
};
