#pragma once
#include "Network.h"
#include "TextBox.h"
#include "Button_K.h"
#include <regex>

static unsigned short VIEW_WIDTH = 800;
static unsigned short VIEW_HEIGHT = 600;

bool Run_Login(sf::RenderWindow &window, sf::Thread *thread_Receive)
{
	sf::View view(sf::Vector2f(player.sprite.getPosition().x, player.sprite.getPosition().y), sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT));
	view.setCenter(window.getSize().x / 2, window.getSize().y / 2);
	window.setView(view);

	socket.disconnect();
	sf::Font font;
	if (!font.loadFromFile("Fonts/arial.ttf")) {
		std::cout << "Can not load Fonts/arial.ttf" << std::endl;
	}
	std::vector<bool *> tabControl;
	sf::Uint8 index = 0;
	TextBox username(font, window.getSize().x / 2.f - 92, window.getSize().y / 5.f);
	TextBox password(font, window.getSize().x / 2.f - 92, window.getSize().y / 4.f);
	Button_K submit (font, window.getSize().x / 2.f - 92, window.getSize().y / 3.f, "Login");
	tabControl.reserve(3);
	tabControl.emplace_back(&username.selected);
	tabControl.emplace_back(&password.selected);
	tabControl.emplace_back(&submit.selected);
	username.selected = true;

	globalMutex.lock();
	quit = false;
	login = false;
	ready = false;
	globalMutex.unlock();

	while (window.isOpen() && !login)
	{
		sf::Event event;

		window.clear(sf::Color(150, 150, 150));

		while (window.pollEvent(event)) {
			if (username.update(window, event))
				index = 0;
			if (password.update(window, event))
				index = 1;
			if (submit.update(window))
				index = 2;

			if (submit.isPressed(window, event)) {
				if (username.getText().empty()) {
					std::cout << "Username can not be empty!" << std::endl;
				}
				else if (password.getText().empty()) {
					std::cout << "Password can not be empty!" << std::endl;
				}
				else if (!regex_match(username.getText(), std::regex("\\w+"))){
					std::cout << "Username contains not allowed characters!" << std::endl;
				}
				else if (!regex_match(password.getText(), std::regex("\\w+"))) {
					std::cout << "Password contains not allowed characters!" << std::endl;
				}
				else if (Connect()) {
					thread_Receive->launch();
					Send_Login_Request(username.getText(), password.getText());
					username.setText("");
					password.setText("");
				}
			}

			switch (event.type) {
				case sf::Event::Closed:
					window.close();
					return false;
					break;
				case sf::Event::Resized:
					break;
				case sf::Event::KeyPressed:
					switch (event.key.code) {
					case sf::Keyboard::Escape:
						window.close();
						return false;
						break;
					case sf::Keyboard::Tab:
						*tabControl[index] = false;
						if (++index >= tabControl.size())
							index = 0;
						*tabControl[index] = true;
						break;
					}
					break;
			}
		}
		username.draw(window);
		password.draw(window);
		submit.draw(window);
		window.display();
		if (login)
			return 1;
	}
	Delete(thread_Receive);
	for (sf::Uint8 i = 0; i < tabControl.size(); ++i)
		delete tabControl[i];
	return 0;
}