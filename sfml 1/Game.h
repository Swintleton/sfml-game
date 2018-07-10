#pragma once
#include "stdafx.h"
#include "Menu.h"
#include "Graphics.h"
#include "FpsCounter.h"

#define VIEW_WIDTH 	800.f
#define VIEW_HEIGHT	600.f

#include "Initialization.h"

bool Run_Game(sf::RenderWindow &window, sf::Thread *thread_Receive){
	sf::View view(sf::Vector2f(player.sprite.getPosition().x, player.sprite.getPosition().y), sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT));
	sf::View view2(sf::Vector2f(player.sprite.getPosition().x, player.sprite.getPosition().y), sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT));
	window.setView(view);

	Load_Graphics_Elements(resource);

	Menu menu(VIEW_WIDTH, VIEW_HEIGHT, resource.font);

	init(window, view, view2);
	//------------------------------DECLARATIONS-----------------------------------------------------------------
	float deltaTime = 0.f;

	sf::Clock clock;
	sf::Event event;

	bool updateHapped = false;

	sf::Vector2f pos;
	//-----------------------------------------------------------------------------------------------------------

	while (window.isOpen())
	{
		if (quit && !login) {
			Clear_Game();
			return true;
		}

		window.clear(sf::Color(150, 150, 150));

		deltaTime = clock.restart().asSeconds();

		if (!player.dead) {
			//player moved?
			if (window.hasFocus() && !messageBox.selected && player.move(deltaTime, walls)) {
				//Player moved
				Send_Move_Request();

				view.setCenter(player.collisionRect.getPosition());
				window.setView(view);

				//Set "fixed" positions
				if (menu.visible)
					menu.updatePos(player.getSprite().getPosition(), view.getSize().y);
				if (inventory.visible)
					inventory.setPosition(player.getSprite().getPosition().x + 80, player.getSprite().getPosition().y);
			}
			//Update player
			player.attack(deltaTime);
			player.beenHit(deltaTime);
			player.doMove = false;
		}
		else {
			player.die(deltaTime);
			respawn_Button.update(window);
			dieMessage.setPos(player.getSprite().getPosition().x - dieMessage.rc.getSize().x / 2, player.getSprite().getPosition().y - dieMessage.rc.getSize().y / 2);
			respawn_Button.setPos(player.getSprite().getPosition().x - respawn_Button.rc.getSize().x / 2, player.getSprite().getPosition().y - respawn_Button.rc.getSize().y / 2);
			if (respawn_Button.isPressed(window, event))
				Send_Respawn_Request();
		}

		//update online players
		for (Online_Player *op : OPlayers) {
			if (!op->dead) {
				op->move(deltaTime);
				op->attack(deltaTime);
				op->beenHit(deltaTime);
			}
			else {
				op->die(deltaTime);
			}
		}

		//update daemons
		for (Daemon *d : daemons) {
			if (!d->dead) {
				if (!d->doMove)
					d->notMovedTime += deltaTime;
				d->move(deltaTime);
				d->attack(deltaTime);
				d->beenHit(deltaTime);
			}
			else {
				d->die(deltaTime);
			}
		}

		view.setCenter(player.collisionRect.getPosition());
		window.setView(view);

		fpsCounter.update(deltaTime);

		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				globalMutex.lock();
				quit = true;
				globalMutex.unlock();
				window.close();
				break;
			case sf::Event::Resized:
				view.setSize(VIEW_HEIGHT * static_cast<float>(window.getSize().x) / static_cast<float>(window.getSize().y), VIEW_HEIGHT);
				view2.setSize(VIEW_HEIGHT * static_cast<float>(window.getSize().x) / static_cast<float>(window.getSize().y), VIEW_HEIGHT);

				pos = { view2.getSize().x * 0.06f - view2.getSize().x * 0.5f,  abs(player.healthBar.collisionCircle.getRadius() * 2 - view2.getSize().y / 2) };
				player.healthBar.setPosition(pos);
				pos = { abs(pos.x + player.manaBar.collisionCircle.getRadius() * 2), pos.y };
				player.manaBar.setPosition(pos);

				pos = { view2.getSize().x * 0.005f - view2.getSize().x * 0.5f, -messageList.rc.getGlobalBounds().height / 2 + 40 };
				messageList.setPosition(pos.x, pos.y);
				pos = { pos.x, pos.y + abs(messageList.rc.getGlobalBounds().height + 3) };
				messageBox.setPosition(pos.x, pos.y);

				pos = { view2.getSize().x / 2 - view2.getSize().x * 0.015f - 16, -view2.getSize().y / 2 };
				fpsCounter.setPosition(pos);
				break;
			case sf::Event::KeyPressed:
				if (!window.hasFocus())
					break;

				switch (event.key.code) {
				case sf::Keyboard::Escape:
					menu.visible = !menu.visible;
					if (menu.visible)
						menu.updatePos(player.getSprite().getPosition(), view.getSize().y);
					break;
				case sf::Keyboard::I:
					if (messageBox.selected)
						break;
					inventory.setVisible(!inventory.visible);
					if (inventory.visible)
						inventory.setPosition(player.getSprite().getPosition().x + 80, player.getSprite().getPosition().y);
					break;
				case sf::Keyboard::LShift:
					player.setRunning(!player.getRunning());
					if (player.getRunning())
						Send_Running();
					else
						Send_Walking();
					break;
				case sf::Keyboard::Up:
					menu.moveUp();
					break;
				case sf::Keyboard::Down:
					menu.moveDown();
					break;
				}
				break;
			case::sf::Event::MouseButtonPressed:
				if (!window.hasFocus())
					break;
				if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
					break;

				updateHapped = false;
				if (inventory.visible) {
					unsigned char inventory_update = inventory.update(window, player.collisionRect.getPosition());
					if (inventory_update == 0) {
						//Nothing happened in the inventory
						for (Item *item : items) {
							if (item->update(window, 1, player.collisionRect.getPosition()) == 1) {
								//Grab item
								inventory.OneItemisGrabbed = true;
								inventory.grabbedItem = item;
								Send_Grab_Request(item);
								inventory.grabbedItem->setNonGroundPosition();
								updateHapped = true;
								break;
							}
						}
					}
					else if (inventory_update == 1) {
						//item taked out
						inventory.grabbedItem->owner = -1;
						Send_Take_Out_Request(inventory.grabbedItem);
						updateHapped = true;
						break;
					}
					else if (inventory_update == 2) {
						//item released
						inventory.grabbedItem->owner = -1;
						Send_Release_Request(inventory.grabbedItem);
						updateHapped = true;
						break;
					}
					else if (inventory_update == 3) {
						//item inserted
						inventory.grabbedItem->owner = player.id;
						Send_Insert_Request(inventory.grabbedItem);
						inventory.grabbedItem->setNonGroundPosition();
						updateHapped = true;
						break;
					}
					else if (inventory_update == 4) {
						//item repositioned
						Send_Repositioning_Request(inventory.grabbedItem);
						inventory.grabbedItem->setNonGroundPosition();
						updateHapped = true;
						break;
					}
				}
				else if (!inventory.OneItemisGrabbed) {
					for (Item *item : items)
						if (item->update(window, 0, player.collisionRect.getPosition()) == 2)
							//Auto insert item
							if (inventory.insert(item)) {
								item->visible = false;
								item->owner = player.id;
								updateHapped = true;
								Send_Auto_Inserting_Request(item);
								item->setNonGroundPosition();
								break;
							}
				}
				break;
			}

			if (window.hasFocus()) {
				//Update menu
				if (menu.visible)
					if(menu.update(window))
						updateHapped = true;

				//Update chat
				if (messageBox.update(window, event) && !Command(messageBox.sendMsg)) {
					char fullMsg[277];
					strncpy_s(fullMsg, player.name, 20);
					strcat_s(fullMsg, ": ");
					strcat_s(fullMsg, messageBox.sendMsg);

					messageList.addMessage(fullMsg);
					Send_Message(messageBox.sendMsg);
					updateHapped = true;
				}
				messageList.update(window, event.text.unicode);
			
				//User actions
				if (!updateHapped && !messageBox.selected && !messageList.selected) {
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
						player.doAttack = true;
						Send_Attack_Request();
					}
				}
			}
		}
		//Grabbed item set to mouse position
		if (inventory.OneItemisGrabbed && inventory.grabbedItem->grabbed)
			inventory.grabbedItem->sprite.setPosition(static_cast<sf::Vector2f>((window.mapPixelToCoords(sf::Mouse::getPosition(window)))));

		//Mouse hovered bars
		if (player.healthBar.hovered(window)) {
			player.healthBar.setText(player.getHealth());
			player.manaBar.setText("");
		}
		else if (player.manaBar.hovered(window)) {
			player.manaBar.setText(player.getMana());
			player.healthBar.setText("");
		}
		else {
			player.healthBar.setText("");
			player.manaBar.setText("");
		}

		Move_Collison_Rects();
		Drawing(window, inventory, menu, view, view2);

		window.display();
	}
	Delete(thread_Receive);
	return false;
}