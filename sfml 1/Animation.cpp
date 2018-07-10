#include "stdafx.h"
#include "Animation.h"

Animation::Animation(float textureWidth, float textureHeight, unsigned short imageCount, float switchTime):
	textureWidth(textureWidth),textureHeight(textureHeight),switchTime(switchTime),imageCount(imageCount),currentImage(0),totalTime(0.f)
{}

void Animation::setImageCount(unsigned short _imageCount) {
	imageCount = _imageCount;
}

void Animation::setSwitchTime(float _switchTime) {
	switchTime = _switchTime;
}

bool Animation::update(sf::Uint8 direction, sf::Texture &texture, sf::Sprite &sprite, float &deltaTime)
{
	totalTime += deltaTime;
	if (totalTime >= switchTime) {
		totalTime -= switchTime;

		if (&texture != sprite.getTexture()) {
			sprite.setTexture(texture);
			currentImage = 0;
		}
		if (currentImage > imageCount)
			currentImage = 0;

		sprite.setTextureRect(sf::IntRect(textureWidth * currentImage, textureHeight * direction, textureWidth, textureHeight));
		++currentImage;
		return 1;
	}
	return 0;
}