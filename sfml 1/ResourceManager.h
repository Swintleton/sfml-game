#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

struct Resource
{
	//font
	sf::Font font;

	//player
	sf::Texture texture_Player_Stopped;
	sf::Texture texture_Player_Walking;
	sf::Texture texture_Player_Combat_Attack;
	sf::Texture texture_Player_Combat_Been_Hit;
	sf::Texture texture_Player_Combat_Die;
	sf::Texture texture_Player_Combat_Running;
	sf::Texture texture_Player_Combat_Stopped;
	sf::Texture texture_Player_Combat_Walking;

	//Circle Bars
	sf::Texture texture_Player_Health_Bar;
	sf::Texture texture_Player_Mana_Bar;
	sf::Texture texture_Circle_Bar_Border;
	sf::Texture texture_Circle_Bar_Effect;

	//Rectangle Bars
	sf::Texture texture_Rect_Health_Bar;
	sf::Texture texture_Rect_Mana_Bar;

	//inventory
	sf::Texture texture_Inventory;

	//items
	//amulets
	sf::Texture texture_Amulet_1;
	sf::Texture texture_Amulet_2;
	sf::Texture texture_Amulet_3;
	//armours
	sf::Texture texture_Quilted_Armor;
	//belts
	sf::Texture texture_Sash;
	//boots
	sf::Texture texture_Boots;
	//circlets
	sf::Texture texture_Circlet;
	//gloves
	sf::Texture texture_Leather_Gloves;
	//helms
	sf::Texture texture_Cap;
	//rings
	sf::Texture texture_Ring_1;
	sf::Texture texture_Ring_2;
	sf::Texture texture_Ring_3;
	sf::Texture texture_Ring_4;
	sf::Texture texture_Ring_5;
	//shields
	sf::Texture texture_Buckler;
	//weapons
	sf::Texture texture_Dagger;
	sf::Texture texture_Short_Sword;

	//walls
	sf::Texture texture_Wall_0;
	sf::Texture texture_Wall_1;

	//environment
	sf::Texture texture_ground;
	sf::Texture texture_grass;
	sf::Texture texture_footway;

	//mobs/daemon
	sf::Texture texture_Daemon_Attack;
	sf::Texture texture_Daemon_Been_Hit;
	sf::Texture texture_Daemon_Die;
	sf::Texture texture_Daemon_Running;
	sf::Texture texture_Daemon_Spawn;
	sf::Texture texture_Daemon_Stopped;
	sf::Texture texture_Daemon_Walking;

	//empty
	sf::Texture texture_Empty;

	//Sounds:
	//player
	sf::SoundBuffer sound_walking;
	sf::SoundBuffer sound_running;
	sf::SoundBuffer sound_swing;
};

static void Load_Graphics_Elements(Resource &resource)
{
	//font
	if (!resource.font.loadFromFile("Fonts/arial.ttf")) {
		std::cout << "Error: can't load Fonts/arial.ttf" << std::endl;
	}

	//player
	if (!resource.texture_Player_Stopped.loadFromFile("Textures/player/stopped.bmp")) {
		std::cout << "Error: can't load Textures/stopped/stopped.bmp" << std::endl;
	}
	if (!resource.texture_Player_Walking.loadFromFile("Textures/player/walking.bmp")) {
		std::cout << "Error: can't load Textures/walking/walking.bmp" << std::endl;
	}
	if (!resource.texture_Player_Combat_Attack.loadFromFile("Textures/player/combat_attack.bmp")) {
		std::cout << "Error: can't load Textures/player/combat_attack.bmp" << std::endl;
	}
	if (!resource.texture_Player_Combat_Been_Hit.loadFromFile("Textures/player/combat_been_hit.bmp")) {
		std::cout << "Error: can't load Textures/player/combat_been_hit.bmp" << std::endl;
	}
	if (!resource.texture_Player_Combat_Die.loadFromFile("Textures/player/combat_die.bmp")) {
		std::cout << "Error: can't load Textures/player/combat_die.bmp" << std::endl;
	}
	if (!resource.texture_Player_Combat_Running.loadFromFile("Textures/player/combat_running.bmp")) {
		std::cout << "Error: can't load Textures/player/combat_running.bmp" << std::endl;
	}
	if (!resource.texture_Player_Combat_Stopped.loadFromFile("Textures/player/combat_stopped.bmp")) {
		std::cout << "Error: can't load Textures/player/combat_stopped.bmp" << std::endl;
	}
	if (!resource.texture_Player_Combat_Walking.loadFromFile("Textures/player/combat_walking.bmp")) {
		std::cout << "Error: can't load Textures/player/combat_walking.bmp" << std::endl;
	}

	//circle bars
	if (!resource.texture_Player_Health_Bar.loadFromFile("Textures/bars/healthBar.png")) {
		std::cout << "Error: can't load Textures/bars/healthBar.png" << std::endl;
	}
	if (!resource.texture_Player_Mana_Bar.loadFromFile("Textures/bars/manaBar.png")) {
		std::cout << "Error: can't load Textures/bars/manaBar.png" << std::endl;
	}
	if (!resource.texture_Circle_Bar_Border.loadFromFile("Textures/bars/circleBarBorder.png")) {
		std::cout << "Error: can't load Textures/bars/circleBarBorder.png" << std::endl;
	}
	if (!resource.texture_Circle_Bar_Effect.loadFromFile("Textures/bars/circleBarEffect.png")) {
		std::cout << "Error: can't load Textures/bars/circleBarEffect.png" << std::endl;
	}

	//rectangle bars
	if (!resource.texture_Rect_Health_Bar.loadFromFile("Textures/bars/rectHealthBar.png")) {
		std::cout << "Error: can't load Textures/bars/rectHealthBar.png" << std::endl;
	}
	if (!resource.texture_Rect_Mana_Bar.loadFromFile("Textures/bars/rectManaBar.png")) {
		std::cout << "Error: can't load Textures/bars/rectManaBar.png" << std::endl;
	}

	//inventory
	if (!resource.texture_Inventory.loadFromFile("Textures/inventory.gif")) {
		std::cout << "Error: can't load Textures/inventory.gif" << std::endl;
	}

	//items
	//amulets
	if (!resource.texture_Amulet_1.loadFromFile("Textures/items/amulets/Amulet_1.gif")) {
		std::cout << "Error: can't load Textures/items/amulets/Amulet_1.gif" << std::endl;
	}
	if (!resource.texture_Amulet_2.loadFromFile("Textures/items/amulets/Amulet_2.gif")) {
		std::cout << "Error: can't load Textures/items/amulets/Amulet_2.gif" << std::endl;
	}
	if (!resource.texture_Amulet_3.loadFromFile("Textures/items/amulets/Amulet_3.gif")) {
		std::cout << "Error: can't load Textures/items/amulets/Amulet_3.gif" << std::endl;
	}
	//armours
	if (!resource.texture_Quilted_Armor.loadFromFile("Textures/items/armours/armours/Quilted_Armor.gif")) {
		std::cout << "Error: can't load Textures/items/armours/armours/Quilted_Armor.gif" << std::endl;
	}
	//belts
	if (!resource.texture_Sash.loadFromFile("Textures/items/armours/belts/Sash.gif")) {
		std::cout << "Error: can't load Textures/items/armours/belts/Sash.gif" << std::endl;
	}
	//boots
	if (!resource.texture_Boots.loadFromFile("Textures/items/armours/boots/Boots.gif")) {
		std::cout << "Error: can't load Textures/items/armours/boots/Boots.gif" << std::endl;
	}
	//circlets
	if (!resource.texture_Circlet.loadFromFile("Textures/items/armours/circlets/Circlet.gif")) {
		std::cout << "Error: can't load Textures/items/armours/circlets/Circlet.gif" << std::endl;
	}
	//gloves
	if (!resource.texture_Leather_Gloves.loadFromFile("Textures/items/armours/gloves/Leather_Gloves.gif")) {
		std::cout << "Error: can't load Textures/items/armours/gloves/Leather_Gloves.gif" << std::endl;
	}
	//helms
	if (!resource.texture_Cap.loadFromFile("Textures/items/armours/helms/Cap.gif")) {
		std::cout << "Error: can't load Textures/items/armours/helms/Cap.gif" << std::endl;
	}
	//rings
	if (!resource.texture_Ring_1.loadFromFile("Textures/items/armours/rings/Ring_1.gif")) {
		std::cout << "Error: can't load Textures/items/armours/rings/Ring_1.gif" << std::endl;
	}
	if (!resource.texture_Ring_2.loadFromFile("Textures/items/armours/rings/Ring_2.gif")) {
		std::cout << "Error: can't load Textures/items/armours/rings/Ring_2.gif" << std::endl;
	}
	if (!resource.texture_Ring_3.loadFromFile("Textures/items/armours/rings/Ring_3.gif")) {
		std::cout << "Error: can't load Textures/items/armours/rings/Ring_3.gif" << std::endl;
	}
	if (!resource.texture_Ring_4.loadFromFile("Textures/items/armours/rings/Ring_4.gif")) {
		std::cout << "Error: can't load Textures/items/armours/rings/Ring_4.gif" << std::endl;
	}
	if (!resource.texture_Ring_5.loadFromFile("Textures/items/armours/rings/Ring_5.gif")) {
		std::cout << "Error: can't load Textures/items/armours/rings/Ring_5.gif" << std::endl;
	}
	//shields
	if (!resource.texture_Buckler.loadFromFile("Textures/items/shields/Buckler.gif")) {
		std::cout << "Error: can't load Textures/items/shields/Buckler.gif" << std::endl;
	}
	//weapons
	if (!resource.texture_Dagger.loadFromFile("Textures/items/weapons/daggers/Dagger.gif")) {
		std::cout << "Error: can't load Textures/items/weapons/daggers/Dagger.gif" << std::endl;
	}
	if (!resource.texture_Short_Sword.loadFromFile("Textures/items/weapons/swords/Short_Sword.gif")) {
		std::cout << "Error: can't load Textures/items/weapons/swords/Short_Sword.gif" << std::endl;
	}

	//walls
	if (!resource.texture_Wall_0.loadFromFile("Textures/walls/wall0.bmp")) {
		std::cout << "Error: can't load Textures/walls/wall0.bmp" << std::endl;
	}
	if (!resource.texture_Wall_1.loadFromFile("Textures/walls/wall1.bmp")) {
		std::cout << "Error: can't load Textures/walls/wall1.bmp" << std::endl;
	}

	//environment
	if (!resource.texture_ground.loadFromFile("Textures/environment/ground.png")) {
		std::cout << "Error: can't load Textures/environment/ground.png" << std::endl;
	}
	if (!resource.texture_grass.loadFromFile("Textures/environment/grass.png")) {
		std::cout << "Error: can't load Textures/environment/grass.png" << std::endl;
	}
	if (!resource.texture_footway.loadFromFile("Textures/environment/footway.png")) {
		std::cout << "Error: can't load Textures/environment/footway.png" << std::endl;
	}

	//mobs/daemon
	if (!resource.texture_Daemon_Attack.loadFromFile("Textures/mobs/daemon/attack.bmp")) {
		std::cout << "Error: can't load Textures/mobs/daemon/attack.bmp" << std::endl;
	}
	if (!resource.texture_Daemon_Been_Hit.loadFromFile("Textures/mobs/daemon/been_hit.bmp")) {
		std::cout << "Error: can't load Textures/mobs/daemon/been_hit.bmp" << std::endl;
	}
	if (!resource.texture_Daemon_Die.loadFromFile("Textures/mobs/daemon/die.bmp")) {
		std::cout << "Error: can't load Textures/mobs/daemon/die.bmp" << std::endl;
	}
	if (!resource.texture_Daemon_Running.loadFromFile("Textures/mobs/daemon/running.bmp")) {
		std::cout << "Error: can't load Textures/mobs/daemon/running.bmp" << std::endl;
	}
	if (!resource.texture_Daemon_Spawn.loadFromFile("Textures/mobs/daemon/spawn.bmp")) {
		std::cout << "Error: can't load Textures/mobs/daemon/spawn.bmp" << std::endl;
	}
	if (!resource.texture_Daemon_Stopped.loadFromFile("Textures/mobs/daemon/stopped.bmp")) {
		std::cout << "Error: can't load Textures/mobs/daemon/stopped.bmp" << std::endl;
	}
	if (!resource.texture_Daemon_Walking.loadFromFile("Textures/mobs/daemon/walking.bmp")) {
		std::cout << "Error: can't load Textures/mobs/daemon/walking.bmp" << std::endl;
	}

	//empty
	if (!resource.texture_Empty.loadFromFile("Textures/empty.png")) {
		std::cout << "Error: can't load Textures/empty.png" << std::endl;
	}

	//Sounds:
	//player
	if (!resource.sound_walking.loadFromFile("Sounds/player/walking.ogg")) {
		std::cout << "Error: can't load Sounds/player/walking.ogg" << std::endl;
	}
	if (!resource.sound_running.loadFromFile("Sounds/player/running.ogg")) {
		std::cout << "Error: can't load Sounds/player/running.ogg" << std::endl;
	}
	if (!resource.sound_swing.loadFromFile("Sounds/player/swing.ogg")) {
		std::cout << "Error: can't load Sounds/player/swing.ogg" << std::endl;
	}
}