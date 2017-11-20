#pragma once
#include <SFML\Graphics.hpp>

class Animation
{
public:
	Animation(float, float, unsigned short, float);

	void update(unsigned int, sf::Texture &, sf::Sprite &, float &);
	
	~Animation(void);
private:
	unsigned short textureWidth;
	unsigned short textureHeight;
	unsigned short imageCount;

	unsigned short currentImage;

	float switchTime;
	float totalTime;
};
