#pragma once
#include <SFML/Network.hpp>
#include <iterator>
#include "Globals.h"
#include "Tools.h"
#include "Communication_Code_List.h"
#include <regex>

#define PORT 53000
#define IPADDRESS "127.0.0.1"

sf::TcpSocket socket;

//------------------------------REQUESTS--------------------------------
void Send_Login_Request(std::string username, std::string password) {
	sf::Packet packet;
	packet << Login << username << password;
	socket.send(packet);
}

void Send_Player_Request() {
	sf::Packet packet;
	packet << Send_Player;
	socket.send(packet);
}

void Send_Wall_Request() {
	sf::Packet packet;
	packet << Send_Walls;
	socket.send(packet);
}

void Send_Item_Request() {
	sf::Packet packet;
	packet << Send_Items;
	socket.send(packet);
}

void Send_Online_Players_Request() {
	sf::Packet packet;
	packet << Send_Online_Players;
	socket.send(packet);
}

void Send_Daemon_Request() {
	sf::Packet packet;
	packet << Send_Daemons;
	socket.send(packet);
}

void Send_Safezone_Request() {
	sf::Packet packet;
	packet << Send_Safezones;
	socket.send(packet);
}

void Send_Regenerator_Request() {
	sf::Packet packet;
	packet << Send_Regenerators;
	socket.send(packet);
}

void Send_Respawn_Request() {
	sf::Packet packet;
	packet << Send_Respawn;
	socket.send(packet);
}

void Send_Move_Request() {
	sf::Packet packet;
	packet << Move_Player;
	packet << static_cast<sf::Int64>(player.collisionRect.getPosition().x);
	packet << static_cast<sf::Int64>(player.collisionRect.getPosition().y);
	packet << player.getDirection();
	socket.send(packet);
}

void Send_Attack_Request() {
	sf::Packet packet;
	packet << Attack_Player;
	socket.send(packet);
}

void Send_Grab_Request(Item *item) {
	sf::Packet packet;
	packet << Item_Grabbed;
	packet << item->id;
	socket.send(packet);
}

void Send_Release_Request(Item *item) {
	sf::Packet packet;
	packet << Item_Released;
	packet << item->id;
	packet << static_cast<sf::Int64>(item->collisionRect.getPosition().x);
	packet << static_cast<sf::Int64>(item->collisionRect.getPosition().y);
	socket.send(packet);
}

void Send_Take_Out_Request(Item *item) {
	sf::Packet packet;
	packet << Item_Take_Out;
	packet << item->id;
	packet << static_cast<sf::Int64>(item->collisionRect.getPosition().x);
	packet << static_cast<sf::Int64>(item->collisionRect.getPosition().y);
	socket.send(packet);
}

void Send_Insert_Request(Item *item) {
	sf::Packet packet;
	packet << Item_inInventory;
	packet << item->id;
	packet << static_cast<unsigned char>(item->inventoryPosition.x);
	packet << static_cast<unsigned char>(item->inventoryPosition.y);
	socket.send(packet);
}

void Send_Auto_Inserting_Request(Item *item) {
	sf::Packet packet;
	packet << Item_Auto_Insert;
	packet << item->id;
	packet << static_cast<unsigned char>(item->inventoryPosition.x);
	packet << static_cast<unsigned char>(item->inventoryPosition.y);
	socket.send(packet);
}

void Send_Repositioning_Request(Item *item) {
	sf::Packet packet;
	packet << Item_Repositioning;
	packet << item->id;
	packet << static_cast<unsigned char>(item->inventoryPosition.x);
	packet << static_cast<unsigned char>(item->inventoryPosition.y);
	socket.send(packet);
}

void Send_Message(std::string msg) {
	sf::Packet packet;
	packet << Chat_Message;
	packet << msg;
	socket.send(packet);
}

void Send_Running() {
	sf::Packet packet;
	packet << Running;
	socket.send(packet);
}

void Send_Walking() {
	sf::Packet packet;
	packet << Walking;
	socket.send(packet);
}
//----------------------------------------------------------------------
//------------------------------SET-------------------------------------
void move_Player(sf::Packet &packet) {
	sf::Int64 x = player.collisionRect.getPosition().x;
	sf::Int64 y = player.collisionRect.getPosition().y;
	packet >> x >> y;

	globalMutex.lock();
	player.setPosition(x, y);
	globalMutex.unlock();
}

void move_Online_Player(sf::Packet &packet) {
	unsigned int id = 0;
	sf::Int64 x = 0, y = 0;
	sf::Uint8 direction = 0;
	packet >> id >> x >> y >> direction;

	for (Online_Player *op : OPlayers) {
		//Find which one moved
		if (op->id == id) {
			globalMutex.lock();
			//Do animation
			op->doMove = true;
			//Set new position
			op->setPosition(x, y);
			op->setDirection(direction);
			globalMutex.unlock();
			return;
		}
	}
}

void move_Daemon(sf::Packet &packet) {
	unsigned int id;
	sf::Int64 x = 0, y = 0;
	sf::Uint8 direction = 0;
	packet >> id >> x >> y >> direction;

	for (Daemon *d : daemons)
		//Find which one moved
		if (d->id == id) {
			globalMutex.lock();
			//Do animation
			d->doMove = true;
			//Set new position
			d->setPosition(x, y);
			d->setDirection(direction);
			globalMutex.unlock();
		}
}

void attack_Online_Player(sf::Packet &packet) {
	unsigned int id;
	packet >> id;

	for (Online_Player *op : OPlayers)
		//Find which one attacked
		if (op->id == id) {
			//Do animation
			globalMutex.lock();
			op->doAttack = true;
			globalMutex.unlock();
		}
}

void attack_Daemon(sf::Packet &packet) {
	unsigned int id;
	packet >> id;

	for (Daemon *d : daemons)
		//Find which one attacked
		if (d->id == id) {
			//Do animation
			d->doAttack = true;
		}
}

void die_Player(sf::Packet &packet) {
	unsigned int id;
	packet >> id;

	//You died?
	if (id == player.id) {
		player.dead = true;
		player.doDie = true;
		dieMessage.visible = true;

		player.sprite.setOrigin(64, 64);
		player.animation.textureWidth = 128;
		player.animation.textureHeight = 128;
		return;
	}

	for (Online_Player *op : OPlayers) {
		if (op->id == id) {
			op->dead = true;
			op->doDie = true;

			op->sprite.setOrigin(64, 64);
			op->animation.textureWidth = 128;
			op->animation.textureHeight = 128;
			return;
		}
	}
}

void die_Daemon(sf::Packet &packet) {
	unsigned int id;
	packet >> id;

	for(Daemon *d : daemons)
		if (d->id == id) {
			globalMutex.lock();
			d->dead = true;
			d->doDie = true;
			globalMutex.unlock();
		}
}

void delete_Daemon(sf::Packet &packet) {
	unsigned int id;
	packet >> id;

	for (Daemon *d : daemons) 
		if (d->id == id) {
			globalMutex.lock();
			daemons.erase(std::remove(daemons.begin(), daemons.end(), d), daemons.end());
			globalMutex.unlock();
		}
}

void damage_Taken_Player(sf::Packet &packet) {
	unsigned int id = 0;
	sf::Int64 dmg = 0;
	packet >> id >> dmg;

	//You are the one who hitted?
	if (player.id == id) {
		player.decreaseHealthBy(dmg);
		player.doBeenHit = true;
		return;
	}

	for (Online_Player *op : OPlayers)
		//Find which one taken damage
		if (op->id == id) {
			op->decreaseHealthBy(dmg);
			op->doBeenHit = true;
			return;
		}
}

void damage_Taken_Daemon(sf::Packet &packet) {
	unsigned int id = 0;
	sf::Int64 dmg = 0;
	packet >> id >> dmg;

	for (Daemon *d : daemons)
		//Find which one taken damage
		if (d->id == id) {
			d->decreaseHealthBy(dmg);
			d->doBeenHit = true;
			return;
		}
}

void healed_Player(sf::Packet &packet) {
	unsigned int id = 0;
	sf::Int64 heal = 0;
	packet >> id >> heal;

	//You are the one who healed?
	if (player.id == id) {
		player.increaseHealthBy(heal);
		return;
	}

	for (Online_Player *op : OPlayers)
		//Find which one take the heal
		if (op->id == id) {
			op->increaseHealthBy(heal);
			return;
		}
}

void Online_Player_Running(sf::Packet &packet) {
	unsigned int id = 0;
	packet >> id;

	for (Online_Player *op : OPlayers)
		if (op->id == id)
			op->setRunning(true);
}

void Online_Player_Walking(sf::Packet &packet) {
	unsigned int id = 0;
	packet >> id;

	for (Online_Player *op : OPlayers)
		if (op->id == id)
			op->setRunning(false);
}

void update_Item_Grabbed(sf::Packet &packet) {
	unsigned int id = 0;
	unsigned int owner = 0;
	packet >> id >> owner;

	for (Item *item : items) {
		//Find which one to update
		if (item->id == id) {
			//Set new grabbed
			globalMutex.lock();
			//If you grabbed
			if (owner == player.id) {
				item->setNonGroundPosition();
				item->grabbed = true;
				if (inventory.OneItemisGrabbed) {
					//This is a problem
				}
				inventory.OneItemisGrabbed = true;
				inventory.grabbedItem = item;
			}
			item->owner = owner;
			globalMutex.unlock();
			break;
		}
	}
}

void update_Item_Released(sf::Packet &packet) {
	unsigned int id = 0;
	sf::Int64 x = 0, y = 0;
	packet >> id >> x >> y;

	for (Item *item : items) {
		if (item->id == id) {
			//Set new grabbed
			globalMutex.lock();
			item->owner = -1;
			item->inInventory = false;
			item->equipped = false;
			item->grabbed = false;
			item->setPosition(x, y);
			globalMutex.unlock();
			break;
		}
	}
}

void item_Grabbing_Failed(sf::Packet &packet) {
	unsigned int id = 0;
	sf::Int64 x = 0, y = 0;
	packet >> id >> x >> y;

	for (Item *item : items) {
		if (item->id == id) {
			globalMutex.lock();
			item->grabbed = false;
			inventory.OneItemisGrabbed = false;
			item->owner = -1;
			item->collisionRect.setRotation(90);
			item->setPosition(x, y);
			globalMutex.unlock();
			break;
		}
	}
}

void item_Inserting_Failed(sf::Packet &packet) {
	unsigned int id = 0;
	packet >> id;

	for (Item *item : items) {
		if (item->id == id) {
			globalMutex.lock();
			inventory.takeOut(item);
			item->grabbed = true;
			inventory.OneItemisGrabbed = true;
			globalMutex.unlock();
			break;
		}
	}
}

void Item_Auto_Inserting_Failed(sf::Packet &packet) {
	unsigned int id = 0;
	sf::Int64 x = 0, y = 0;
	packet >> id >> x >> y;

	for (Item *item : items) {
		if (item->id == id) {
			globalMutex.lock();
			inventory.takeOut(item);
			item->setGroundPosition();
			item->setPosition(x, y);
			item->owner = -1;
			item->visible = true;
			globalMutex.unlock();
			break;
		}
	}
}

void item_Releasing_Failed(sf::Packet &packet) {
	unsigned int id = 0;
	packet >> id;

	for (Item *item : items) {
		if (item->id == id) {
			globalMutex.lock();
			item->grabbed = true;
			inventory.OneItemisGrabbed = true;
			item->owner = player.id;
			globalMutex.unlock();
			break;
		}
	}
}

void item_Takeing_Out_Failed(sf::Packet &packet) {
	unsigned int id = 0;
	unsigned char cell[2] = {0, 0};
	packet >> id >> cell[0] >> cell[1];

	for (Item *item : items) {
		if (item->id == id) {
			globalMutex.lock();
			item->grabbed = true;
			inventory.OneItemisGrabbed = true;
			inventory.insert(item, cell);
			item->owner = player.id;
			globalMutex.unlock();
			break;
		}
	}
}

void item_Repositioning_Failed(sf::Packet &packet) {
	unsigned int id = 0;
	unsigned char cell[2] = { 0, 0 };
	packet >> id >> cell[0] >> cell[0];

	for (Item *item : items) {
		if (item->id == id) {
			globalMutex.lock();
			inventory.takeOut(item);
			inventory.insert(item, cell);
			globalMutex.unlock();
			break;
		}
	}
}

void add_Online_Player(sf::Packet &packet) {
	unsigned int id = 0;
	char name[20];
	bool dead = false;
	bool running = false;
	sf::Int64 speed = 100;
	sf::Int64 attackSpeed = 63;
	sf::Int64 maxHealth = 10;
	sf::Int64 health = 10;
	sf::Int64 maxMana = 10;
	sf::Int64 mana = 10;
	sf::Int64 x = 0, y = 0;
	sf::Uint8 direction = 0;

	float attackspeed = 0.63f;

	globalMutex.lock();
	if (packet >> id >> name >> dead >> running >> speed >> attackSpeed >> maxHealth >> health >> maxMana >> mana >> x >> y >> direction) {
		attackspeed = (float)attackSpeed / 100 - 0.21f;
		OPlayers.push_back(new Online_Player(id, name, dead, running, speed, attackspeed, maxHealth, health, maxMana, mana, x, y, direction, resource.texture_Player_Stopped, resource.texture_Player_Walking, resource.texture_Player_Combat_Attack, resource.texture_Player_Combat_Been_Hit, resource.texture_Player_Combat_Die, resource.texture_Player_Combat_Running, resource.texture_Player_Combat_Stopped, resource.texture_Player_Combat_Walking, resource.texture_Rect_Health_Bar, resource.texture_Rect_Mana_Bar, resource.font, resource.texture_Empty));
	}
	globalMutex.unlock();
}

void add_Item(sf::Packet &packet) {
	unsigned int id = 0;
	int owner = 0;
	unsigned short type = 0;
	bool visible = true;
	bool equipped = false;
	bool grabbed = false;
	bool inInventory = false;
	unsigned char inventoryPositionX = 0;
	unsigned char inventoryPositionY = 0;
	sf::Int64 x = 0, y = 0;

	globalMutex.lock();
	if (packet >> id >> owner >> type >> visible >> equipped >> grabbed >> inInventory >> inventoryPositionX >> inventoryPositionY >> x >> y) 
		items.push_back(new Item(id, owner, type, visible, equipped, grabbed, inInventory, inventoryPositionX, inventoryPositionY, (float)x, (float)y, resource));
	globalMutex.unlock();

	//Put your item into your inventory
	if (items.back()->owner == player.id)
		inventory.itemList.push_back(items.back());
}

bool delete_Online_Player(sf::Packet &packet) {
	unsigned int id = 0;
	packet >> id;

	for (Online_Player *op : OPlayers) {
		if (op->id == id) {
			globalMutex.lock();
			OPlayers.erase(std::remove(OPlayers.begin(), OPlayers.end(), op), OPlayers.end());
			globalMutex.unlock();
			return true;
		}
	}
	return false;
}

void respawn_Player(sf::Packet &packet) {
	unsigned int id = 0;
	float health = 0;
	float mana = 0;
	sf::Uint64 x = 0, y = 0;

	if (packet >> id >> health >> mana >> x >> y) {
		//You are the one who respawning?
		if (id == player.id) {
			player.dead = false;
			dieMessage.visible = false;
			respawn_Button.selected = false;

			player.setHealth(health);
			player.setMana(mana);
			sf::Vector2f playerOLDPos = player.collisionRect.getPosition();
			player.setPosition(x, y);

			player.sprite.setOrigin(48, 48);
			player.animation.textureWidth = 96;
			player.animation.textureHeight = 96;

			//Set "fixed" positions
			if (inventory.visible)
				inventory.setPosition(player.getSprite().getPosition().x + 80, player.getSprite().getPosition().y);
			return;
		}
		for (Online_Player *op : OPlayers) {
			if (op->id == id) {
				op->dead = false;
				op->setHealth(health);
				op->setMana(mana);
				op->setPosition(x, y);

				op->sprite.setOrigin(48, 48);
				op->animation.textureWidth = 96;
				op->animation.textureHeight = 96;
				return;
			}
		}
	}

}

void create_Player(sf::Packet &packet) {
	unsigned int id = 0;
	char name[20];
	bool dead = false;
	bool running = false;
	sf::Int64 speed = 100;
	sf::Int64 attackSpeed = 84;
	sf::Int64 maxHealth = 10;
	sf::Int64 health = 10;
	sf::Int64 maxMana = 10;
	sf::Int64 mana = 10;
	sf::Int64 x = 0, y = 0;
	sf::Uint8 direction = 0;

	float attackspeed = 0.63f;

	packet >> id >> name >> dead >> running >> speed >> attackSpeed >> maxHealth >> health >> maxMana >> mana >> x >> y >> direction;

	attackspeed = (float)attackSpeed / 100 - 0.21f;

	globalMutex.lock();
	player.id = id;
	strncpy_s(player.name, name, 20);
	player.dead = dead;
	player.setRunning(running);
	player.setSpeed(speed);
	player.setAttackSpeed(attackspeed);
	player.setMaxHealth(maxHealth);
	player.setHealth(health);
	player.setMaxMana(maxMana);
	player.setMana(mana);
	player.setPosition(x, y);
	player.setDirection(direction);
	globalMutex.unlock();

	messageBox.setPosition(player.getSprite().getPosition().x - 390, player.getSprite().getPosition().y + 165);
	messageList.setPosition(player.getSprite().getPosition().x - 390, player.getSprite().getPosition().y - 40);
	fpsCounter.setPosition(player.collisionRect.getPosition());
}

void create_Walls(sf::Packet &packet) {
	globalMutex.lock();
	walls.clear();
	playerBeforeWall.clear();
	playerBehindWall.clear();
	globalMutex.unlock();

	walls.reserve(sizeof(Wall) * (packet.getDataSize() / 21));
	playerBeforeWall.reserve(sizeof(playerBeforeWall) * (packet.getDataSize() / 20));
	playerBehindWall.reserve(sizeof(playerBehindWall) * (packet.getDataSize() / 20));

	for (unsigned int i = 2; i < packet.getDataSize(); i += 21) {
		unsigned int id = 0;
		sf::Int64 x = 0, y = 0;
		sf::Uint8 direction = 0;
		packet >> id >> x >> y >> direction;

		if (direction == 4)
			walls.emplace_back(new Wall(id, resource.texture_Wall_1, x, y, direction));

		else if (direction == 7)
			walls.emplace_back(new Wall(id, resource.texture_Wall_0, x, y, direction));

		playerBeforeWall.emplace_back(sf::Vector2f(walls.back()->collisionRect.getPosition().x, walls.back()->collisionRect.getPosition().y + 50));
		playerBehindWall.emplace_back(walls.back()->collisionRect.getPosition());
	}
}

void create_Online_Players(sf::Packet &packet) {
	globalMutex.lock();
	OPlayers.clear();
	globalMutex.unlock();

	unsigned int id = 1;
	char name[20];
	bool dead = false;
	bool running = false;
	sf::Int64 speed = 100;
	sf::Int64 attackSpeed = 63;
	sf::Int64 maxHealth = 10;
	sf::Int64 health = 10;
	sf::Int64 maxMana = 10;
	sf::Int64 mana = 10;
	sf::Int64 x = 0, y = 0;
	sf::Uint8 direction = 0;

	OPlayers.reserve(sizeof(OPlayers) * (packet.getDataSize() / 91));

	float attackspeed = 0.63f;

	while (packet >> id >> name >> dead >> running >> speed >> attackSpeed >> maxHealth >> health >> maxMana >> mana >> x >> y >> direction) {
		attackspeed = (float)attackSpeed / 100 - 0.21f;
		OPlayers.emplace_back(new Online_Player(id, name, dead, running, speed, attackspeed, maxHealth, health, maxMana, mana, x, y, direction, resource.texture_Player_Stopped, resource.texture_Player_Walking, resource.texture_Player_Combat_Attack, resource.texture_Player_Combat_Been_Hit, resource.texture_Player_Combat_Die, resource.texture_Player_Combat_Running, resource.texture_Player_Combat_Stopped, resource.texture_Player_Combat_Walking, resource.texture_Rect_Health_Bar, resource.texture_Rect_Mana_Bar, resource.font, resource.texture_Empty));
	}
}

void create_Items(sf::Packet &packet) {
	globalMutex.lock();
	items.clear();
	globalMutex.unlock();

	unsigned int id = 0;
	int owner = 0;
	unsigned short type = 0;
	bool visible = true;
	bool equipped = false;
	bool grabbed = false;
	bool inInventory = false;
	unsigned char inventoryPositionX = 0;
	unsigned char inventoryPositionY = 0;
	sf::Int64 x = 0, y = 0;

	items.reserve(sizeof(Item) * (packet.getDataSize() / 32));

	while (packet >> id >> owner >> type >> visible >> equipped >> grabbed >> inInventory >> inventoryPositionX >> inventoryPositionY >> x >> y) {
		items.emplace_back(new Item(id, owner, type, visible, equipped, grabbed, inInventory, inventoryPositionX, inventoryPositionY, (float)x, (float)y, resource));
	}

	//Put your items into your inventory
	for (Item *item : items)
		if (item->owner == player.id)
			inventory.itemList.push_back(item);
}

void create_Daemons(sf::Packet &packet){
	globalMutex.lock();
	daemons.clear();
	globalMutex.unlock();

	unsigned int id = 0;
	bool dead = false;
	bool running = false;
	sf::Int64 speed = 100;
	sf::Int64 attackSpeed = 63;
	sf::Int64 maxHealth = 10;
	sf::Int64 health = 10;
	sf::Int64 maxMana = 10;
	sf::Int64 mana = 10;
	sf::Int64 x = 0, y = 0;
	sf::Uint8 direction = 0;

	daemons.reserve(sizeof(Daemon) * (packet.getDataSize() / 71));

	float attackspeed = 0.63f;

	while (packet >> id >> dead >> running >> speed >> attackSpeed >> maxHealth >> health >> maxMana >> mana >> x >> y >> direction) {
		attackspeed = (float)attackSpeed / 100;
		daemons.emplace_back(new Daemon(id, dead, running, speed, attackspeed, maxHealth, health, maxMana, mana, x, y, direction, resource.texture_Daemon_Attack, resource.texture_Daemon_Been_Hit, resource.texture_Daemon_Die, resource.texture_Daemon_Running, resource.texture_Daemon_Spawn, resource.texture_Daemon_Stopped, resource.texture_Daemon_Walking, resource.texture_Rect_Health_Bar, resource.texture_Rect_Mana_Bar, resource.font, resource.texture_Empty));
	}
}

void create_Safezones(sf::Packet &packet) {
	globalMutex.lock();
	safezones.clear();
	globalMutex.unlock();

	unsigned int id = 0;
	sf::Int64 x = 0;
	sf::Int64 y = 0;
	sf::Int64 w = 0;
	sf::Int64 h = 0;
	bool active = true;

	safezones.reserve(sizeof(Safezone) * (packet.getDataSize() / 29));

	while (packet >> id >> x >> y >> w >> h >> active) {
		safezones.emplace_back(new Safezone(id, x, y, w, h, active));
	}
}

void create_Regenertors(sf::Packet &packet) {
	globalMutex.lock();
	regenerators.clear();
	globalMutex.unlock();

	unsigned int id = 0;
	sf::Int64 x = 0;
	sf::Int64 y = 0;
	sf::Int64 w = 0;
	sf::Int64 h = 0;
	bool active = true;
	sf::Uint8 type = 0;

	regenerators.reserve(sizeof(Regenerator) * (packet.getDataSize() / 30));

	while (packet >> id >> x >> y >> w >> h >> active >> type) {
		regenerators.emplace_back(new Regenerator(id, x, y, w, h, active, type));
	}
}

//----------------------------------------------------------------------
void command_interpretation(sf::Packet &packet) {
	unsigned short command;
	packet >> command;

	if (command == Move_Player) {
		move_Player(packet);
	}
	else if(command == Online_Player_Moved) {
		move_Online_Player(packet);
	}
	else if (command == Daemon_Moved) {
		move_Daemon(packet);
	}
	else if (command == Damage_Taken_Player) {
		damage_Taken_Player(packet);
	}
	else if (command == Damage_Taken_Daemon) {
		damage_Taken_Daemon(packet);
	}
	else if (command == Healed_Player) {
		healed_Player(packet);
	}
	else if (command == Online_Player_Deleted) {
		delete_Online_Player(packet);
	}
	else if (command == Attack_Player) {
		attack_Online_Player(packet);
	}
	else if (command == Attack_Daemon) {
		attack_Daemon(packet);
	}
	else if (command == Die_Player) {
		die_Player(packet);
	}
	else if (command == Die_Daemon) {
		die_Daemon(packet);
	}
	else if (command == Daemon_Deleted) {
		delete_Daemon(packet);
	}
	else if (command == Running) {
		Online_Player_Running(packet);
	}
	else if (command == Walking) {
		Online_Player_Walking(packet);
	}
	else if (command == Item_Grabbed) {
		update_Item_Grabbed(packet);
	}
	else if (command == Item_Grabbing_Failed) {
		item_Grabbing_Failed(packet);
	}
	else if (command == Item_Released) {
		update_Item_Released(packet);
	}
	else if (command == Item_Releasing_Failed) {
		item_Releasing_Failed(packet);
	}
	else if (command == Item_inInventory_Failed) {
		item_Inserting_Failed(packet);
	}
	else if (command == Item_Auto_Insert) {
		Item_Auto_Inserting_Failed(packet);
	}
	else if (command == Item_Takeing_Out_Failed) {
		item_Takeing_Out_Failed(packet);
	}
	else if (command == Item_Repositioning_Failed) {
		item_Repositioning_Failed(packet);
	}
	else if (command == Chat_Message) {
		char msg[277];
		packet >> msg;
		messageList.addMessage(msg);
	}
	else if (command == Login) {
		globalMutex.lock();
		login = true;
		globalMutex.unlock();
		std::cout << "Login successfull." << std::endl;
	}
	else if (command == Login_failed) {
		std::cout << "Incorrect username or password." << std::endl;
	}
	else if (command == Already_logged_in) {
		std::cout << "Username already logged in." << std::endl;
	}
	else if (command == Kicked_out) {
		globalMutex.lock();
		quit = true;
		login = false;
		globalMutex.unlock();
		std::cout << "You have been kicked out from the server!" << std::endl;
	}
	//Sends
	else if (command == Send_Player) {
		create_Player(packet);
	}
	else if (command == Send_Walls) {
		create_Walls(packet);
	}
	else if (command == Send_Online_Players) {
		create_Online_Players(packet);
	}
	else if (command == Send_Online_Player) {
		add_Online_Player(packet);
	}
	else if (command == Send_Item) {
		add_Item(packet);
	}
	else if (command == Send_Items) {
		create_Items(packet);
	}
	else if (command == Send_Daemons) {
		create_Daemons(packet);
	}
	else if (command == Send_Safezones) {
		create_Safezones(packet);
	}
	else if (command == Send_Regenerators) {
		create_Regenertors(packet);
	}
	else if (command == Send_Respawn) {
		respawn_Player(packet);
	}
}

bool Command(std::string command) {
	////////////////////////////////////////////////////////////
	//	CHAT COMMANDS:
	//
	//	/exit			-	Exit
	////////////////////////////////////////////////////////////

	if (regex_match(command, std::regex("\/help", std::regex_constants::icase))) {
		std::cout << "/help                      -	List commands" << std::endl;
		std::cout << "/List Inventory            -	List Inventory" << std::endl;
		return true;
	}
	else if (regex_match(command, std::regex("\/List Inventory", std::regex_constants::icase))) {
		std::cout << player.name << " inventory:" << std::endl;
		std::cout << "--------------------------------------------------" << std::endl;

		for (Item *item : items)
			if (item->owner == player.id) {
				std::cout << "ID: " << item->id << std::endl;
				std::cout << "Type: " << item->type << std::endl;
				std::cout << "Name: " << item->name << std::endl;
			}

		std::cout << std::endl;

		for (int y = 0; y < inventoryY; ++y) {
			for (int x = 0; x < inventoryX; ++x)
				std::cout << inventory.freeSpace[x][y] << ' ';
			std::cout << std::endl;
		}
		std::cout << "--------------------------------------------------" << std::endl;
		return true;
	}

	return false;
}

void Receive_Packets(void)
{
	while (!quit)
	{
		//Receive Message
		sf::Packet packetReceive;
		if (socket.receive(packetReceive) == sf::Socket::Done) {
			command_interpretation(packetReceive);
		}
		else if (socket.receive(packetReceive) == sf::Socket::Disconnected) {
			globalMutex.lock();
			quit = true;
			login = false;
			socket.disconnect();
			globalMutex.unlock();
		}
	}
}

void Send_Message(void)
{
	while (!quit) {
		sf::Packet packet;
		std::cout << CurrentTime() << "Me: ";
		std::string s;
		getline(std::cin, s);

		if (!Command(s) && s != "\n") {
			packet << Chat_Message << s;
			socket.send(packet);
		}
	}
}

bool Connect()
{
	std::cout << "Connecting to the server..." << std::endl;
	bool connected = false;
	short connection_try = 5;
	for (int i = 0; i < connection_try && !connected; ++i) {
		connected = socket.connect(IPADDRESS, PORT, sf::seconds(3.f)) == sf::Socket::Done;
		if(!connected)
			std::cout << "Connection failed..." << std::endl;
	}

	if (!connected)
	{
		std::cout << "Can not connect to the server" << std::endl;
		return 0;
	}

	std::cout << "Connected\n";
	return 1;
}

void Clear_Game(void) {
	for (unsigned int i = 0; i < walls.size(); ++i)
		delete walls[i];

	for (unsigned int i = 0; i < items.size(); ++i)
		delete items[i];

	for (unsigned int i = 0; i < OPlayers.size(); ++i)
		delete OPlayers[i];

	for (unsigned int i = 0; i < daemons.size(); ++i)
		delete daemons[i];

	walls.clear();
	items.clear();
	OPlayers.clear();
	daemons.clear();
}

void Delete(sf::Thread *thread_Receive) {
	if (thread_Receive)
	{
		thread_Receive->terminate();
		delete thread_Receive;
	}

	unsigned int i = 0;

	for (i = 0; i < walls.size(); ++i)
		delete walls[i];

	for (i = 0; i < safezones.size(); ++i)
		delete safezones[i];

	for (i = 0; i < regenerators.size(); ++i)
		delete regenerators[i];

	for (i = 0; i < items.size(); ++i)
		delete items[i];

	for (i = 0; i < OPlayers.size(); ++i)
		delete OPlayers[i];

	for (i = 0; i < daemons.size(); ++i)
		delete daemons[i];
}