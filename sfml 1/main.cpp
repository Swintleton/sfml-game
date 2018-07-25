#include "stdafx.h"
#include "Login.h"
#include "Game.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(static_cast<unsigned short>(VIEW_WIDTH), static_cast<unsigned short>(VIEW_HEIGHT)), "SFML 1", sf::Style::Default);
	window.setFramerateLimit(60);

	sf::Thread* thread_Receive = new sf::Thread(&Receive_Packets);

	login:
	if (Run_Login(window, thread_Receive))
		if (Run_Game(window, thread_Receive))
			goto login;
}
