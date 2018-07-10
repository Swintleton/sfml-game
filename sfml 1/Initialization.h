#pragma once

//Set default values
void init(sf::RenderWindow &window, sf::View &view, sf::View &view2) {
	//Send requests
	Send_Player_Request();
	Send_Wall_Request();
	Send_Item_Request();
	Send_Online_Players_Request();
	Send_Daemon_Request();
	Send_Safezone_Request();
	Send_Regenerator_Request();

	//Player set textures & sounds
	player.setStoppedTexture(resource.texture_Player_Stopped);
	player.setWalkingTexture(resource.texture_Player_Walking);
	player.setCombat_Attack(resource.texture_Player_Combat_Attack);
	player.setCombat_Been_Hit(resource.texture_Player_Combat_Been_Hit);
	player.setCombat_Die(resource.texture_Player_Combat_Die);
	player.setCombat_Running(resource.texture_Player_Combat_Running);
	player.setCombat_Stopped(resource.texture_Player_Combat_Stopped);
	player.setCombat_Walking(resource.texture_Player_Combat_Walking);

	//Healt & Mana bars
	window.setView(view2);
	player.setHealthBarTexture(resource.texture_Player_Health_Bar);
	player.healthBar.setBorderTexture(resource.texture_Circle_Bar_Border);
	player.healthBar.setEffectTexture(resource.texture_Circle_Bar_Effect);
	player.healthBar.setFont(resource.font);
	sf::Vector2f pos = { view2.getSize().x * 0.06f - view2.getSize().x * 0.5f,  abs(player.healthBar.collisionCircle.getRadius() * 2 - view2.getSize().y / 2) };
	player.healthBar.setPosition(pos);//-350 200

	player.setManaBarTexture(resource.texture_Player_Mana_Bar);
	player.manaBar.setBorderTexture(resource.texture_Circle_Bar_Border);
	player.manaBar.setEffectTexture(resource.texture_Circle_Bar_Effect);
	player.manaBar.setFont(resource.font);
	pos = { abs(pos.x + player.manaBar.collisionCircle.getRadius() * 2), pos.y };
	player.manaBar.setPosition(pos);//250 200
	window.setView(view);

	player.setEmptyTexture(resource.texture_Empty);

	player.setWalking_Sound(resource.sound_walking);
	player.setRunning_Sound(resource.sound_running);
	player.setSwing_Sound(resource.sound_swing);

	//Inventory
	inventory.setTexture(resource.texture_Inventory);

	//Chat
	window.setView(view2);
	messageList.setFont(resource.font);
	pos = { view2.getSize().x * 0.005f - view2.getSize().x * 0.5f, -messageList.rc.getGlobalBounds().height / 2 + 40 };
	messageList.setPosition(pos.x, pos.y);
	messageBox.setFont(resource.font);
	pos = { pos.x, pos.y + abs(messageList.rc.getGlobalBounds().height + 3) };
	messageBox.setPosition(pos.x, pos.y);

	//FPS counter
	fpsCounter.setFont(resource.font);
	pos = { view2.getSize().x / 2 - view2.getSize().x * 0.015f - 16, -view2.getSize().y / 2};
	fpsCounter.setPosition(pos);
	window.setView(view);

	dieMessage.setFont(resource.font);
	dieMessage.setPos(0, 0);
	dieMessage.setSize(100, 50);
	dieMessage.setText("You died :(");
	dieMessage.setTextPos(2, 2);
	respawn_Button.setFont(resource.font);
	respawn_Button.setPos(0, 0);
	respawn_Button.setSize(78, 26);
	respawn_Button.setText("Respawn");
}