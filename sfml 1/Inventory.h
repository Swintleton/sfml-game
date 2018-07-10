#pragma once
#include "Item.h"

#define inventoryX 10
#define inventoryY 10

class Inventory
{
public:
	bool freeSpace[10][10];
	std::vector<Item *> itemList;
	sf::RectangleShape collisionRect;

	bool visible;

	Inventory(sf::Vector2f);
	void draw(sf::RenderWindow &) const;
	unsigned char* positionToCell(sf::Vector2f);
	bool insert(Item *);
	bool insert(Item *, unsigned char*);
	bool repositioning(Item *, unsigned char*);
	void setTexture(sf::Texture &);
	void setPosition(sf::Vector2f);
	void setPosition(float, float);
	void setVisible(bool visibility);
	void takeOut(Item *);
	unsigned char update(sf::RenderWindow &window, sf::Vector2f);

	sf::Sprite sprite;
	bool OneItemisGrabbed;
	Item *grabbedItem;
};

