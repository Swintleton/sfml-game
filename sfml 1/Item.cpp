#include "stdafx.h"
#include "Item.h"

Item::Item(unsigned int _id, int _owner, unsigned short _type, bool _visible, bool _equipped, bool _grabbed, bool _inInventory, unsigned char inventoryPositionX, unsigned char inventoryPositionY, float x, float y, Resource &resource)
	: id(_id),owner(_owner), type(_type), visible(_visible), equipped(_equipped), grabbed(_grabbed), inInventory(_inInventory), inventoryPosition({inventoryPositionX, inventoryPositionY})
{
	name = " ";
	if (type == Dagger) {
		inventorySize = {1, 2};
		name = "Dagger";
		sprite.setTexture(resource.texture_Dagger);
	}
	else if (type == Short_Sword) {
		inventorySize = {1, 3};
		name = "Short Sword";
		sprite.setTexture(resource.texture_Short_Sword);
	}
	else if (type == Amulet_1) {
		inventorySize = { 1, 1 };
		name = "Amulet_1";
		sprite.setTexture(resource.texture_Amulet_1);
	}
	else if (type == Amulet_2) {
		inventorySize = { 1, 1 };
		name = "Amulet_2";
		sprite.setTexture(resource.texture_Amulet_2);
	}
	else if (type == Amulet_3) {
		inventorySize = { 1, 1 };
		name = "Amulet_3";
		sprite.setTexture(resource.texture_Amulet_3);
	}
	else if (type == Quilted_Armor) {
		inventorySize = { 2, 3 };
		name = "Quilted_Armor";
		sprite.setTexture(resource.texture_Quilted_Armor);
	}
	else if (type == Sash) {
		inventorySize = { 2, 1 };
		name = "Sash";
		sprite.setTexture(resource.texture_Sash);
	}
	else if (type == Boots) {
		inventorySize = { 2, 2 };
		name = "Boots";
		sprite.setTexture(resource.texture_Boots);
	}
	else if (type == Circlet) {
		inventorySize = { 2, 2 };
		name = "Circlet";
		sprite.setTexture(resource.texture_Circlet);
	}
	else if (type == Leather_Gloves) {
		inventorySize = { 2, 2 };
		name = "Leather_Gloves";
		sprite.setTexture(resource.texture_Leather_Gloves);
	}
	else if (type == Cap) {
		inventorySize = { 2, 2 };
		name = "Cap";
		sprite.setTexture(resource.texture_Cap);
	}
	else if (type == Ring_1) {
		inventorySize = { 1, 1 };
		name = "Ring_1";
		sprite.setTexture(resource.texture_Ring_1);
	}
	else if (type == Ring_2) {
		inventorySize = { 1, 1 };
		name = "Ring_2";
		sprite.setTexture(resource.texture_Ring_2);
	}
	else if (type == Ring_3) {
		inventorySize = { 1, 1 };
		name = "Ring_3";
		sprite.setTexture(resource.texture_Ring_3);
	}
	else if (type == Ring_4) {
		inventorySize = { 1, 1 };
		name = "Ring_4";
		sprite.setTexture(resource.texture_Ring_4);
	}
	else if (type == Ring_5) {
		inventorySize = { 1, 1 };
		name = "Ring_5";
		sprite.setTexture(resource.texture_Ring_5);
	}
	else {
		inventorySize = { 1, 1 };
	}

	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
	minusX = sprite.getLocalBounds().width / 2;
	minusY = sprite.getLocalBounds().height / 2;

	text.setFillColor(sf::Color::Color(80, 80, 80, 255));
	text.setFont(resource.font);
	text.setCharacterSize(13);
	text.setString(name);

	if (!inInventory && !grabbed && !equipped)
		collisionRect.setRotation(90);

	if(grabbed || inInventory)
		collisionRect.setSize(sf::Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().height));
	else{
		collisionRect.setSize(sf::Vector2f(sprite.getLocalBounds().height / inventorySize.y, text.getGlobalBounds().width));
		text.setPosition(collisionRect.getPosition().x - collisionRect.getLocalBounds().height, collisionRect.getPosition().y + 4);
	}

	collisionRect.setFillColor(sf::Color(0,0,0,150));
	collisionRect.setPosition(x, y);

	text.setPosition(x - collisionRect.getLocalBounds().height, y + 4);
}

void Item::draw(sf::RenderWindow &window) const {
	//Inside inventory appearance
	if (inInventory || grabbed) {
		window.draw(sprite);
		return;
	}
	//Outside inventory appearance
	window.draw(collisionRect);
	window.draw(text);
}

//Return values:
//0		-	Nothing happened
//1		-	Item Grabbed
//2		-	Item should be auto inserted into the inventory
unsigned char Item::update(sf::RenderWindow &window, bool inventoryVisible, sf::Vector2f playerPos) {
	if (!visible)
		return 0;

	if(!inInventory)
		//Distance between the player and the item position is larger than 200?
		if (std::sqrt(std::pow(std::abs(playerPos.x - collisionRect.getPosition().x), 2) + std::pow(std::abs(playerPos.y - collisionRect.getPosition().y), 2)) > 200)
			return 0;

	sf::Vector2f MouseClick = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	if (!grabbed && inventoryVisible && collisionRect.getGlobalBounds().contains(MouseClick)) {
		//Grabb item
		grabbed = true;
		return 1;
	}

	else if (!grabbed && !inventoryVisible && collisionRect.getGlobalBounds().contains(MouseClick)) {
		//Auto insert to the inventory
		return 2;
	}
	return 0;
}

void Item::setGroundPosition() {
	collisionRect.setRotation(90);
	collisionRect.setSize(sf::Vector2f(sprite.getLocalBounds().height / inventorySize.y, text.getLocalBounds().width));
	text.setPosition(collisionRect.getPosition().x - collisionRect.getLocalBounds().height, collisionRect.getPosition().y + 4);
}

void Item::setNonGroundPosition() {
	collisionRect.setRotation(0);
	collisionRect.setSize(sf::Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().height));
}

void Item::setPosition(float x, float y) {
	collisionRect.setPosition(x, y);
	sprite.setPosition(x + sprite.getLocalBounds().width / 2, y + sprite.getLocalBounds().height / 2);
	text.setPosition(x - collisionRect.getLocalBounds().height, y + 4);
}

void Item::setPosition(sf::Vector2f pos) {
	collisionRect.setPosition(pos);
	sprite.setPosition(pos.x + sprite.getLocalBounds().width / 2, pos.y + sprite.getLocalBounds().height / 2);
	text.setPosition(pos.x - collisionRect.getLocalBounds().height, pos.y + 4);
}