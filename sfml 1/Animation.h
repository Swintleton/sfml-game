#pragma once
#include <SFML\Graphics.hpp>

class Animation
{
public:
	unsigned short textureWidth;
	unsigned short textureHeight;

	Animation(float textureWidth, float textureHeight, unsigned short imageCount, float switchTime);
	void setImageCount(unsigned short);
	void setSwitchTime(float);
	bool update(sf::Uint8, sf::Texture &, sf::Sprite &, float &);
private:
	unsigned short imageCount;
	unsigned short currentImage;
	float switchTime;
	float totalTime;
};
