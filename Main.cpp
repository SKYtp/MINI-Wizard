#include <iostream>
#include <sstream>
#include <math.h>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "Menu.h"
//#include <SFML/Network.hpp>
using namespace std;
int level = 0, ingame = 0, pressW = 0;
float limitH = 0;
int Gp1, c_power = 0;
int starC = 0;
int G_time = 0;
int Strack = 1;
int Twait, d_power = 0, player_d = 0;
int c_score;
int c_s = 0;
struct point
{
	int x, y;
};
point plat[3];
point star[6];

void plat_lv1();
void plat_lv2();
void star_lv1();
float enemy_s = 0.015;
int enemy_mode = 0;
int _highScore, _score;
int score_sw = 0;

int main()
{
	sf::Clock clock;
	sf::RenderWindow window(sf::VideoMode(1000, 570), "MINI Wizard", sf::Style::Titlebar | sf::Style::Close);

	Menu menu(window.getSize().x, window.getSize().y);
	
	//set sprite
	sf::Texture menutex;
	if (!menutex.loadFromFile("Texture/MenubackG.png"))
	{
		//handle error
	}
	sf::Sprite menuBG;
	menuBG.setTexture(menutex);

	sf::Texture backG_p, playertex, plat_t, portal_t, player_L, H_s_t;
	backG_p.loadFromFile("Texture/backG.png");
	playertex.loadFromFile("Texture/player.png");
	plat_t.loadFromFile("Texture/plat.png");
	portal_t.loadFromFile("Texture/portal.png");
	player_L.loadFromFile("Texture/player_L.png");
	H_s_t.loadFromFile("Texture/backG_S.png");
	sf::Sprite backG, player, Sportal, H_s;
	sf::Sprite splat1, splat2, splat3;
	H_s.setTexture(H_s_t);
	backG.setTexture(backG_p);
	player.setTexture(playertex);
	player.setScale(0.1025f, 0.1025f);
	splat1.setTexture(plat_t);
	splat1.setScale(0.75f, 0.75f);
	splat2.setTexture(plat_t);
	splat2.setScale(0.75f, 0.75f);
	splat3.setTexture(plat_t);
	splat3.setScale(0.75f, 0.75f);
	Sportal.setTexture(portal_t);
	Sportal.setScale(0.075f, 0.075f);
	sf::Texture power_t1, star_t;
	power_t1.loadFromFile("Texture/power1.png");
	star_t.loadFromFile("Texture/star.png");
	sf::Sprite power1,starS;
	power1.setTexture(power_t1);
	starS.setTexture(star_t);
	power1.setScale(0.075f, 0.075f);
	power1.setPosition(1000, 80);
	starS.setScale(0.075f, 0.075f);
	
	sf::Font font_T;
	font_T.loadFromFile("Font/mainfont.ttf");

	std::ostringstream S_time;
	S_time << "Time: " << G_time;
	
	sf::Text count_t;
	count_t.setCharacterSize(20);
	count_t.setPosition(10, 10);
	count_t.setFont(font_T);
	count_t.setString(S_time.str());

	sf::SoundBuffer sound_SL, sound_BL;
	sound_SL.loadFromFile("Sound/sound_star.wav");
	//sound_BL.loadFromFile("Sound/bird.wav");
	sf::Sound sound_S, sound_B;
	sound_S.setBuffer(sound_SL);
	//sound_B.setBuffer(sound_BL);
	sound_S.setVolume(45);
	sf::Music music, menu_M;
	music.openFromFile("Sound/music.wav");
	music.setVolume(50);
	menu_M.openFromFile("Sound/menu_song.wav");
	menu_M.setVolume(50);
	sf::Texture enemy_t;
	enemy_t.loadFromFile("Texture/enemy.png");
	sf::Sprite enemy;
	enemy.setTexture(enemy_t);
	enemy.setScale(0.065f, 0.065f);
	std::ifstream readFile;
	readFile.open("Resources/Highscore.txt");
	if (readFile.is_open())
	{
		while (!readFile.eof())
		{
			readFile >> _highScore;
		}
	}
	readFile.close();
	sf::Text H_score_t;
	std::ostringstream S_score;
	S_score << "Less time: " << _highScore;
	H_score_t.setCharacterSize(20);
	H_score_t.setPosition(400, 220);
	H_score_t.setFont(font_T);
	H_score_t.setString(S_score.str());
	



	// end set sprite
	menu_M.play();
	menu_M.setLoop(true);

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
							player.setPosition(10, 348);
							plat_lv1();
							star_lv1();
							clock.restart();
							menu_M.stop();
							music.play();
							music.setLoop(true);
							enemy.setPosition(800, 360);
							score_sw = 0;
							
							//sound_B.play();
							// go to state
							break;
						case 1:
							std::cout << "High score has been preesed" << std::endl;
							menu_M.stop();
							score_sw = 1;
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
			/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				player.move(0.f, -0.5f);
				pressW = 1;
			}*/
			


		}
		// player move
		if (ingame > 0) // after menu
		{
			if (player.getTexture() == &playertex && c_power == 0)
			{
				d_power = 0;
			}
			else if (player.getTexture() == &player_L && c_power == 0)
			{
				d_power = 1;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && c_power == 0) 
			{
				power1.setPosition(player.getPosition().x + 2,player.getPosition().y + 5);
				c_power = 1;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && limitH <= 200 && player.getPosition().y > 1)
			{
				player.move(0.f, -0.12f);
				pressW = 1;
				limitH = limitH + 0.15;
				//std::cout << starC << std::endl;
				/*std::cout << player.getPosition().x << std::endl;
				std::cout << player.getPosition().y << std::endl;*/
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player.getPosition().x < 930)
			{
				player.move(0.15f, 0.f);
				player.setTexture(playertex);
				if (c_power == 0)
				{
					d_power = 0;
				}
				player_d = 0;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player.getPosition().x > 1)
			{
				player.move(-0.15f, 0.f);
				player.setTexture(player_L);
				if (c_power == 0)
				{
					d_power = 1;
				}
				player_d = 1;
			}
			if (player.getPosition().x > splat1.getPosition().x - 50 && player.getPosition().x < splat1.getPosition().x + 150
				&& player.getPosition().y < splat1.getPosition().y - 72 && player.getPosition().y > splat1.getPosition().y - 74 && pressW == 0)
			{
				limitH = 0;
			}
			else if (player.getPosition().x > splat2.getPosition().x - 50 && player.getPosition().x < splat2.getPosition().x + 150
				&& player.getPosition().y < splat2.getPosition().y - 72 && player.getPosition().y > splat2.getPosition().y - 74 && pressW == 0)
			{
				limitH = 0;
			}
			else if (player.getPosition().x > splat3.getPosition().x - 50 && player.getPosition().x < splat3.getPosition().x + 150
				&& player.getPosition().y < splat3.getPosition().y - 72 && player.getPosition().y > splat3.getPosition().y - 74 && pressW == 0)
			{
				limitH = 0;
			}
			else if (player.getPosition().y < 350 && pressW == 0)
			{
				player.move(0.f, 0.15f);
			}
			// end player move
			
			// check player
			if (player.getPosition().y < 350 && player.getPosition().y > 349)
			{
				limitH = 0;
			}
			// end check player

			




			if (c_power == 1 && d_power == 0)
			{
				power1.move(0.15f, 0.f);
			}
			else if (c_power == 1 && d_power == 1)
			{
				power1.move(-0.15f, 0.f);
			}
			


		}
		if (player.getGlobalBounds().intersects(Sportal.getGlobalBounds()) && starC == 6)
		{
			player.setPosition(10, 348);
			if (level == 1)
			{
				level = level + 1;
				starC = 0;
				enemy_s = 0.04;
				Strack = 1;
				star_lv1();
			}
			else if (level == 2)
			{
				level = level + 1;
			}
		}
		if (power1.getPosition().x > 1005 && d_power == 0)
		{
			c_power = 0;
		}
		if (power1.getPosition().x < -50 && d_power == 1)
		{
			c_power = 0;
		}
		if (level > 0)
		{
			for (int i = 0; i < 6; i++)
			{
				if (player.getPosition().x - 25 < star[i].x && player.getPosition().x + 25 > star[i].x
					&& player.getPosition().y - 25 < star[i].y && player.getPosition().y + 25 > star[i].y)
				{
					star[i] = { 1000,200 };
					starC++;
					sound_S.play();
				}
			}
			int enemy_x = enemy.getPosition().x;
			int enemy_y = enemy.getPosition().y;
			int player_x = player.getPosition().x;
			int player_y = player.getPosition().y;
			float track_x = (player_x - enemy_x) / sqrt(((player_x - enemy_x) * (player_x - enemy_x)) + ((player_y - enemy_y) * (player_y - enemy_y)));
			float track_y = (player_y - enemy_y) / sqrt(((player_x - enemy_x) * (player_x - enemy_x)) + ((player_y - enemy_y) * (player_y - enemy_y)));
			if (Strack == 1)
			{
				enemy.move(enemy_s* track_x, enemy_s* track_y);
			}
			
			if (player.getPosition().x - 25 < enemy.getPosition().x && player.getPosition().x + 25 > enemy.getPosition().x
				&& player.getPosition().y - 25 < enemy.getPosition().y && player.getPosition().y + 25 > enemy.getPosition().y)
			{
				player.setPosition(10, 348);
				enemy.setPosition(800, 360);
			}
			if (power1.getPosition().x - 25 < enemy.getPosition().x && power1.getPosition().x + 25 > enemy.getPosition().x
				&& power1.getPosition().y - 25 < enemy.getPosition().y && power1.getPosition().y + 25 > enemy.getPosition().y)
			{
				Strack = 0;
				Twait = G_time;
				//enemy_mode = 1;
			}
			/*if (player.getPosition().x > enemy.getPosition().x - 50 && player.getPosition().x < enemy.getPosition().x + 150
				&& player.getPosition().y < enemy.getPosition().y - 72 && player.getPosition().y > enemy.getPosition().y - 74)
			{
				limitH = 0;
			}w*/
			if (G_time - Twait > 3)
			{
				Strack = 1;
				//enemy_mode = 0;
			}



		}
		sf::Time elapsed1 = clock.getElapsedTime();
		G_time = elapsed1.asSeconds();
		//std::cout << G_time << std::endl;
		S_time.str("");
		S_time << "Time: " << G_time;
		count_t.setString(S_time.str());


		if (level == 1)
		{
			splat1.setPosition(plat[0].x, plat[0].y);
			splat2.setPosition(plat[1].x, plat[1].y);
			splat3.setPosition(plat[2].x, plat[2].y);
			Sportal.setPosition(890, 340);
		}
		else if (level == 2)
		{
			plat_lv2();
			splat1.setPosition(plat[0].x, plat[0].y);
			splat2.setPosition(plat[1].x, plat[1].y);
			splat3.setPosition(plat[2].x, plat[2].y);
		}
		else if (level == 3)
		{
			while (c_s == 0)
			{
				_score = G_time;
				c_s++;
				std::cout << _score << std::endl;
			}
			std::ifstream readFile;
			readFile.open("Resources/Highscore.txt");
			if (readFile.is_open())
			{
				while (!readFile.eof())
				{
					readFile >> _highScore;
				}
			}
			readFile.close();
			std::ofstream writeFile("Resources/Highscore.txt");
			if (writeFile.is_open())
			{
				if (_score < _highScore)
				{
					_highScore = _score;
				}
				writeFile << _highScore;
			}
			writeFile.close();
			
		}
		
		


        window.clear();
		// draw all display
		if (score_sw == 1)
		{
			window.draw(H_s);
			window.draw(H_score_t);
		}
		if (level == 0 && score_sw != 1)
		{
			window.draw(menuBG);
			menu.draw(window);
		}
		if (level == 1)
		{
			window.draw(backG);
			window.draw(splat1);
			window.draw(splat2);
			window.draw(splat3);
			window.draw(Sportal);
			
		}
		else if (level == 2)
		{
			window.draw(backG);
			window.draw(splat1);
			window.draw(splat2);
			window.draw(splat3);
			window.draw(Sportal);
		}
		
		



		if (level > 0)
		{
			window.draw(player);
			window.draw(power1);
			for (int i = 0; i < 6; i++)
			{
				starS.setPosition(star[i].x, star[i].y);
				window.draw(starS);
			}
			window.draw(count_t);
			window.draw(enemy);
		}

        window.display();
		pressW = 0;
    }
    return 0;
}

void plat_lv1()
{
	plat[0] = { 250,300 };
	plat[1] = { 150,100 };
	plat[2] = { 600,300 };
}
void plat_lv2()
{
	plat[0] = { 650,250 };
	plat[1] = { 400,200 };
	plat[2] = { 600,300 };
}
void star_lv1()
{
	star[0] = { 250,340 };
	star[1] = { 300,330 };
	star[2] = { 550,250 };
	star[3] = { 600,320 };
	star[4] = { 100,330 };
	star[5] = { 520,330 };
}