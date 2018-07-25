#include "stdafx.h"
#include "Inventory.h"

Inventory::Inventory(sf::Vector2f pos)
{
	for (unsigned short i = 0; i < inventoryY; ++i) {
		for (unsigned short j = 0; j < inventoryX; ++j) {
			freeSpace[j][i] = 1;
		}
	}
	sprite.setPosition(pos);
	collisionRect.setPosition(pos);
	visible = false;
}

void Inventory::draw(sf::RenderWindow &window) const {
	window.draw(sprite);
}

bool Inventory::insert(Item &item) {
	sf::Vector2i size(item.inventorySize);
	unsigned char untilY = (int)(inventoryY - size.y / 2 + 0.5);
	unsigned char untilX = (int)(inventoryX - size.x / 2 + 0.5);

	unsigned char freespacePos[2] = { 11, 11 };

	//Search for a free positions
	for (unsigned char y = 0; y <= untilY; ++y) {
		for (unsigned char x = 0; x <= untilX; ++x) {
			//Try to insert the item
			if (freeSpace[x][y]) {
				freespacePos[0] = x;
				freespacePos[1] = y;
				if (insert(item, freespacePos)) {
					return true;
				}
			}
		}
	}
	return false;
}

bool Inventory::insert(Item &item, unsigned char *FreespacePos) {
	unsigned char itemSizeX = item.inventorySize.x, itemSizeY = item.inventorySize.y;

	//The entire item fits in the inventory?
	if (FreespacePos[0] + itemSizeX > inventoryX || FreespacePos[1] + itemSizeY > inventoryY)
		return false;

	//At the position the space is free?
	for (unsigned char y = FreespacePos[1]; y < FreespacePos[1] + itemSizeY; ++y)
		for (unsigned char x = FreespacePos[0]; x < FreespacePos[0] + itemSizeX; ++x)
			if (!freeSpace[x][y])
				return false;

	//Captured inventory space set to false
	for (unsigned char y = FreespacePos[1]; y < FreespacePos[1] + itemSizeY; ++y)
		for (unsigned char x = FreespacePos[0]; x < FreespacePos[0] + itemSizeX; ++x)
			freeSpace[x][y] = false;

	//Item Add ItemList
	item.inventoryPosition.x = FreespacePos[0];
	item.inventoryPosition.y = FreespacePos[1];
	item.inInventory = true;
	item.grabbed = false;
	item.collisionRect.setRotation(0);
	OneItemisGrabbed = false;
	item.setPosition(collisionRect.getPosition().x + 2 + item.inventoryPosition.x * 26 + item.inventoryPosition.x * 3, collisionRect.getPosition().y + 2 + item.inventoryPosition.y * 25 + item.inventoryPosition.y * 3);
	itemList.push_back(&item);
	return true;
}

unsigned char* Inventory::positionToCell(sf::Vector2f pos) {
	sf::Vector2f basePos(collisionRect.getPosition());
	sf::RectangleShape cellRC;
	cellRC.setSize(sf::Vector2f(30, 25));	//One Cell is 26 x 25
	pos.y -= grabbedItem->minusY;

	unsigned char cell[2] = { inventoryX, inventoryY };

	for (unsigned char cellY = 0; cellY < inventoryY; ++cellY)
		for (unsigned char cellX = 0; cellX < inventoryX; ++cellX) {
			cellRC.setPosition(basePos.x + cellX * 26 + cellX * 3 + 2, basePos.y + cellY * 25 + cellY * 3 + 2);
			if (cellRC.getGlobalBounds().contains(pos)) {
				cell[0] = cellX;
				cell[1] = cellY;
				return cell;
			}
		}

	return cell;
}

bool Inventory::repositioning(Item &item, unsigned char *FreespacePos) {
	unsigned char itemSizeX = item.inventorySize.x, itemSizeY = item.inventorySize.y;

	//The entire item fits in the inventory?
	if (FreespacePos[0] + itemSizeX > inventoryX || FreespacePos[1] + itemSizeY > inventoryY)
		return false;

	//Free up last position space
	for (unsigned char y = item.inventoryPosition.y; y < item.inventoryPosition.y + itemSizeY; ++y)
		for (unsigned char x = item.inventoryPosition.x; x < item.inventoryPosition.x + itemSizeX; ++x)
			freeSpace[x][y] = true;

	//At the position the space is free?
	for (unsigned char y = FreespacePos[1]; y < FreespacePos[1] + itemSizeY; ++y)
		for (unsigned char x = FreespacePos[0]; x < FreespacePos[0] + itemSizeX; ++x)
			if (!freeSpace[x][y])
				return false;

	//Captured inventory space set to false
	for (unsigned char y = FreespacePos[1]; y < FreespacePos[1] + itemSizeY; ++y)
		for (unsigned char x = FreespacePos[0]; x < FreespacePos[0] + itemSizeX; ++x)
			freeSpace[x][y] = false;

	//Set new item position
	item.inventoryPosition.x = FreespacePos[0];
	item.inventoryPosition.y = FreespacePos[1];
	item.grabbed = false;
	OneItemisGrabbed = false;
	item.setPosition(collisionRect.getPosition().x + 2 + item.inventoryPosition.x * 26 + item.inventoryPosition.x * 3, collisionRect.getPosition().y + 2 + item.inventoryPosition.y * 25 + item.inventoryPosition.y * 3);
	return true;
}

void Inventory::setTexture(sf::Texture &texture) {
	sprite.setTexture(texture);
	collisionRect.setSize(static_cast<sf::Vector2f>(texture.getSize()));
}

void Inventory::setPosition(sf::Vector2f pos) {
	collisionRect.setPosition(pos);
	sprite.setPosition(pos);

	for (Item *item : itemList)
		if (item->inInventory && !item->grabbed)
			item->setPosition(collisionRect.getPosition().x + 2 + item->inventoryPosition.x * 26 + item->inventoryPosition.x * 3, collisionRect.getPosition().y + 2 + item->inventoryPosition.y * 25 + item->inventoryPosition.y * 3);
}

void Inventory::setPosition(float x, float y) {
	collisionRect.setPosition(x, y);
	sprite.setPosition(x, y);

	for (Item *item : itemList)
		if (item->inInventory && !item->grabbed)
			item->setPosition(collisionRect.getPosition().x + 2 + item->inventoryPosition.x * 26 + item->inventoryPosition.x * 3, collisionRect.getPosition().y + 2 + item->inventoryPosition.y * 25 + item->inventoryPosition.y * 3);
}

void Inventory::setVisible(bool visibility) {
	visible = visibility;
	for (Item *item : itemList) 
		item->visible = visibility;
}

void Inventory::takeOut(Item &item) {
	item.grabbed = false;
	OneItemisGrabbed = false;
	item.inInventory = false;

	for (unsigned char y = item.inventoryPosition.y; y < item.inventoryPosition.y + item.inventorySize.y; ++y)
		for (unsigned char x = item.inventoryPosition.x; x < item.inventoryPosition.x + item.inventorySize.x; ++x)
			freeSpace[x][y] = true;

	for(unsigned int i = 0; i < itemList.size(); ++i)
		if (itemList[i]->id == item.id) {
			itemList.erase(itemList.begin() + i);
			return;
		}
}

//returns:
//0		-	nothing happend
//1		-	item taked out
//2		-	item released
//3		-	item inserted
//4		-	item repositioned
unsigned char Inventory::update(sf::RenderWindow &window, sf::Vector2f playerPos) {
	if (!OneItemisGrabbed)
		return 0;

	sf::Vector2f MouseClick = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	//Click happened outside the inventory
	if (!collisionRect.getGlobalBounds().contains(MouseClick)) {
		MouseClick.x -= grabbedItem->minusX;
		MouseClick.y -= grabbedItem->minusY;

		//Distance between the player and the mouse position is larger than 200?
		if (std::sqrt(std::pow(std::abs(playerPos.x - MouseClick.x), 2) + std::pow(std::abs(playerPos.y - MouseClick.y), 2)) > 200) {
			return 0;
		}

		//Set item "ground" position
		grabbedItem->setPosition(MouseClick.x + grabbedItem->collisionRect.getLocalBounds().height * 0.7, MouseClick.y + grabbedItem->collisionRect.getLocalBounds().height / 2);
		grabbedItem->setGroundPosition();

		grabbedItem->owner = -1;

		if (grabbedItem->inInventory) {
			takeOut(*grabbedItem);
			return 1;
		}
		else {
			OneItemisGrabbed = false;
			grabbedItem->grabbed = false;
			return 2;
		}
	}

	//Click happened inside the inventory

	//Item was not in the inventory before grabbing
	if (!grabbedItem->inInventory) {
		//Insert new item into the inventory
		if (insert(*grabbedItem, positionToCell(MouseClick))) {
			return 3;
		}
	}

	//Repositioning inventory item
	if (repositioning(*grabbedItem, positionToCell(MouseClick))) {
		return 4;
	}
	return 0;
}