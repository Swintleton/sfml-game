#pragma once
#include <algorithm>

void Move_Collison_Rects(void) {
	unsigned int stepper = 0;
	for (Wall &wall : walls) {
		//PUT THE COLLISION RECT UP OR DOWN
		if (player.collisionRect.getPosition().y < wall.collisionRect.getPosition().y + 30)	//the +30 only for change quicker
			wall.collisionRect.setPosition(playerBeforeWall[stepper]);
		if (player.collisionRect.getPosition().y > wall.collisionRect.getPosition().y - 30)
			wall.collisionRect.setPosition(playerBehindWall[stepper]);
		++stepper;
	}
}

void Drawing(sf::RenderWindow &window, Inventory &inventory, Menu &menu, sf::View &view, sf::View &view2) {
	//Draw Safezones
	for (Safezone &s : safezones)
		s.draw(window);

	//Draw Regenerators
	for (Regenerator &r : regenerators)
		r.draw(window);

	//Draw items on the ground
	for (Item &item : items) {
		if(item.visible && !item.inInventory && !item.grabbed && !item.equipped && item.owner == -1)
			item.draw(window);
	}

	//Store all Y positions and sprites
	//------------------------------------------------------------------------------------------
	std::vector<std::pair<float, sf::Sprite *>> DrawList;

	//Add Player
	DrawList.push_back(std::make_pair(player.collisionRect.getPosition().y, &player.sprite));

	//Add Walls
	DrawList.reserve(sizeof(Wall) * walls.size());
	for (Wall &wall : walls)
		DrawList.emplace_back(std::make_pair(wall.sprite.getPosition().y, &wall.sprite));

	//Add Online Players
	DrawList.reserve(sizeof(Online_Player) * OPlayers.size());
	for (Online_Player &op : OPlayers)
		DrawList.emplace_back(std::make_pair(op.collisionRect.getPosition().y, &op.sprite));

	//Add Daemons
	DrawList.reserve(sizeof(Daemon) * daemons.size());
	for (Daemon &d : daemons)
		DrawList.emplace_back(std::make_pair(d.collisionRect.getPosition().y, &d.sprite));
	//------------------------------------------------------------------------------------------

	//Sort them by Y coordinates
	std::sort(DrawList.begin(), DrawList.end());

	//Draw them
	for (std::pair<float, sf::Sprite *> a : DrawList)
		window.draw(*a.second);

	//Draw HealthBars
	for (Online_Player &op : OPlayers) {
		op.healthBar.draw(window);
		op.manaBar.draw(window);
	}
	for (Daemon &d : daemons) {
		d.healthBar.draw(window);
		d.manaBar.draw(window);
	}

	window.setView(view2);
	//Draw PlayerHealthBar
	player.healthBar.draw(window);

	//Draw PlayerManaBar
	player.manaBar.draw(window);

	//Draw ChatBox
	messageBox.draw(window);
	messageList.draw(window);

	//Draw FPS
	fpsCounter.draw(window);
	window.setView(view);

	//Draw Inventory
	if (inventory.visible) {
		inventory.draw(window);

		//Draw Items in inventory
		for (Item &item : items) {
			if (item.visible && !item.grabbed && item.inInventory && item.owner == player.id)
				item.draw(window);
		}
	}

	//Draw Grabbed items
	for (Item &item : items) {
		if (item.visible && item.grabbed)
			item.draw(window);
	}

	if (dieMessage.visible) {
		dieMessage.draw(window);
		respawn_Button.draw(window);
	}

	//Draw Menu
	if(menu.visible)
		menu.draw(window);
}