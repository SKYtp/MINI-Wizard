#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "Menu.h"
//#include <SFML/Network.hpp>
using namespace std;
int level = 0, ingame = 0;
int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 570), "MINI Wizard", sf::Style::Titlebar | sf::Style::Close);

	Menu menu(window.getSize().x, window.getSize().y);
	sf::Texture menutex;
	if (!menutex.loadFromFile("Texture/MenubackG.png"))
	{
		//handle error
	}
	sf::Sprite menuBG;
	menuBG.setTexture(menutex);

	sf::Texture backG_p, player;
	backG_p.loadFromFile("Texture/backG.png");
	sf::Sprite backG;
	backG.setTexture(backG_p);


    while (window.isOpen())
    {
        sf::Event ev;
		while (window.pollEvent(ev))
		{
			switch (ev.type)
			{
			case sf::Event::KeyReleased:
				switch (ev.key.code)
				{
				case sf::Keyboard::Up:
					menu.MoveUp();
					break;
				case sf::Keyboard::Down:
					menu.MoveDown();
					break;
				case sf::Keyboard::Return:
					if(ingame == 0)
					{
						switch (menu.GetPressedItem())
						{
						case 0:
							std::cout << "Play has been preesed" << std::endl;
							ingame = 1;
							level = 1;
							// go to state
							break;
						case 1:
							std::cout << "Leaderboard has been preesed" << std::endl;
							// go to state
							break;
						case 2:
							window.close();
							break;

						}
						break;
					}
				}

				break;

			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
					window.close();
				break;

			case sf::Event::TextEntered:
				cout << char(ev.text.unicode) << endl;
				break;
				default:
				break;
			}



		}

        window.clear();
		// draw all display
		if (level == 0)
		{
			window.draw(menuBG);
			menu.draw(window);
		}
		if (level == 1)
		{
			window.draw(backG);
		}
		





        window.display();
    }
    return 0;
}
