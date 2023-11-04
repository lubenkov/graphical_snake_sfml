#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "ColorDesign.h"
#include <sstream>
#include <fstream>
#include <string>
using namespace sf;

enum Stage { Playing, Menu , Settings};
Stage stage = Menu;

enum direction { STOP, UP, DOWN, LEFT, RIGHT };
direction dir;

direction prevDir;

int score = 0;
int it = 0;

int st = 0;

int CheckMaxScore()
{
	std::ifstream in("Score.txt");
	int CurrMaxScore;
	in >> CurrMaxScore;
	in.close();
	if (CurrMaxScore < score) {
		std::ofstream out("Score.txt");
		out << score;
		out.close();
		return 1;
	}
	return 0;
}

class SnakeHead 
{
	public:

		CircleShape rect;
		float x, y;
	SnakeHead(int X, int Y, Color color, int size)
	{
		dir = STOP;
		x = X;
		y = Y;
		rect.setFillColor(Color(color));
		rect.setPosition(x, y);
		rect.setRadius(size);
	}

	void control(Event& event, float &x, float &y, float time)
	{


		if (Event::KeyPressed and event.key.code == Keyboard::W)
		{
			dir = UP;
		}
		if (Event::KeyPressed and event.key.code == Keyboard::S)
		{
			dir = DOWN;
		}
		if (Event::KeyPressed and event.key.code == Keyboard::A)
		{
			dir = LEFT;
		}
		if (Event::KeyPressed and event.key.code == Keyboard::D)
		{
			dir = RIGHT;
		}
		
	}

	void move(float time)
	{
		if (dir == UP) {
			y -= 0.2 * time;  
			rect.setPosition(x, y);
		}
		if (dir == DOWN) {
			y += 0.2 * time;
			rect.setPosition(x, y);
		}
		if (dir == LEFT) {
			x -= 0.2 * time;
			rect.setPosition(x, y);
		}
		if (dir == RIGHT) {
			x += 0.2 * time;
			rect.setPosition(x, y);
		}

	}
	
};

class Map
{
public:
	RectangleShape m[100];
	const static int width = 1000;
	const static int height = 1000;

	int beginX = 600;
	int beginY = 120;

	int wallThickness = 40;

	
	String tileMap[height / 40 + 1] = {
		"wwwwwwwwwwwwwwwwwwwwwwwww",
		"w                       w",
		"w                       w",
		"w                       w",
		"w                       w",
		"w                       w",
		"w                       w",
		"w                       w",
		"w                       w",
		"w                       w",
		"w                       w",
		"w                       w",
		"w                       w",
		"w                       w",
		"w                       w",
		"w                       w",
		"w                       w",
		"w                       w",
		"w                       w",
		"w                       w",
		"w                       w",
		"w                       w",
		"w                       w",
		"w                       w",
		"w                       w",
		"wwwwwwwwwwwwwwwwwwwwwwwww"
	
	};

	int num = 0;
	Map()
	{
		for (int i = 0; i < height / 40 + 1; i++)
			for (int j = 0; j < width / 40 + 1; j++)
			{
				if (tileMap[i][j] == 'w')
				{
					m[num].setFillColor(Color3[st]);
					m[num].setSize(Vector2f(40, 40));
					m[num].setPosition(beginX + j * 40, beginY + i * 40);
				    num++;
				}
			}
	}



	void TouchTheWall(SnakeHead& head)
	{
		if (head.x < beginX + 40) head.x = beginX + width - 55;
		else if (head.x > beginX + width - 55) head.x = beginX + 40;
		else if (head.y < beginY + 40) head.y = beginY + height - 20;
		else if (head.y > beginY + height - 10) head.y = beginY + 40;
	}

	
	
};

int AppleX = 1100, AppleY = 600;


class Apple 
{
public:
	
	CircleShape apple;

	void GenerateApple(int x, int y)
	{
		srand(time(0));
		apple.setFillColor(Color5[st]);
		apple.setRadius(10);
		apple.setOutlineThickness(2);
		apple.setOutlineColor(Color::Black);
		srand(time(0));
		if (x + 10 > AppleX and y + 10 > AppleY and x + 10 < AppleX + 20 and y + 10 < AppleY + 20) {
			AppleX = ((rand() % (920) + 640)/20)*20;
			AppleY = ((rand() % (960) + 160)/20)*20;
			score++;
			
		}
		apple.setPosition(AppleX, AppleY);
	}
};


class Tail : Map
{
public: 
	
	
	CircleShape tail[1500];
	
	void UpdateTail(float x, float y, int& it)
	{
		if (it > score * 10 ) it = 0;
		
		if (it <= score * 10) 
		{
			
			tail[it].setPosition(x, y);
			tail[it].setFillColor(Color1[st]);
			tail[it].setRadius(10);

			//tail[it].setOutlineColor(Color::Black);
			//tail[it].setOutlineThickness(1);

			it++;
		}
		
	}


	void TouchTheTail(float x, float y)
	{
		for (int i = 0; i < score * 10; i++)
		{
			
			if (dir == LEFT) {
				if (x < tail[i].getPosition().x + 20 and x > tail[i].getPosition().x + 15 and y > tail[i].getPosition().y - 10 and y < tail[i].getPosition().y + 10)
				{
					for (int j = 0; j < score * 10; j++)
					{
						tail[j].setPosition(2000, 2000);
					}
					CheckMaxScore();
					score = 0;
					it = 0;
					

				}
			}
			else if (dir == RIGHT) {
				if (x > tail[i].getPosition().x - 20 and x < tail[i].getPosition().x - 15 and y > tail[i].getPosition().y - 10 and y < tail[i].getPosition().y + 10)
				{
					for (int j = 0; j < score * 10; j++)
					{
						tail[j].setPosition(2000, 2000);
					}
					CheckMaxScore();
					score = 0;
					it = 0;
				}
			}
			else if (dir == UP) {
				if (y < tail[i].getPosition().y + 20 and y > tail[i].getPosition().y + 15 and x > tail[i].getPosition().x - 10 and x < tail[i].getPosition().x + 10)
				{
					for (int j = 0; j < score * 10; j++)
					{
						tail[j].setPosition(2000, 2000);
					}
					CheckMaxScore();
					score = 0;
					it = 0;
				}
			}
			else if (dir == DOWN) {
				if (y > tail[i].getPosition().y - 20 and y < tail[i].getPosition().y - 15 and x > tail[i].getPosition().x - 10 and x < tail[i].getPosition().x + 10)
				{
					for (int j = 0; j < score * 10; j++)
					{
						tail[j].setPosition(2000, 2000);
					}
					CheckMaxScore();
					score = 0;
					it = 0;
				}
			}
		   
		}

	}

};


int main()
{
	
	std::ifstream in1("Score.txt");
	std::string PlScore;
	in1 >> PlScore;
	in1.close();
	
	
	ColorDesign colorDesign;

	Font font;
	font.loadFromFile("resources/font1.ttf");

	Text play("PLAY", font, 400);
	play.setStyle(Text::Bold);
	play.setFillColor(Color3[st]);
	play.setPosition(550, 300);

	Text settings("SETTINGS", font, 150);
	settings.setStyle(Text::Bold);
	settings.setFillColor(Color3[st]);
	settings.setPosition(700, 800);

	Text pScore("Score: ", font, 50);
	pScore.setStyle(Text::Bold);
	pScore.setFillColor(Color4[st]);
	pScore.setPosition(1000, 1200);
	
	Text death("DEATH ", font, 100);
	death.setFillColor(Color3[st]);
	death.setPosition(875, 500);
	
	RectangleShape deathShape;
	CircleShape deathFlag;
	deathShape.setFillColor(Color::White);
	deathShape.setOutlineColor(Color::Black);
	deathShape.setOutlineThickness(3);
	deathShape.setPosition(1000, 700);
	deathShape.setSize(Vector2f(100, 100));
	deathFlag.setFillColor(Color::Red);
	deathFlag.setOutlineColor(Color::Black);
	deathFlag.setOutlineThickness(3);
	deathFlag.setPosition(1020, 720);
	deathFlag.setRadius(30);
	bool chanceToDie = false;
	
	
	ContextSettings sett;
	sett.antialiasingLevel = 16;
	

	RenderWindow window(sf::VideoMode(2240, 1400), "snake", Style::Default, sett);

	SnakeHead head(1000, 500, Color1[st], 9);

	Tail tail;
	
	Clock clock;
	
	Text color("COLOR ", font, 100);
	color.setPosition(875, 50);
	color.setFillColor(Color3[st]);

	CircleShape triangle(40, 3);
	triangle.setPosition(50, 100);
	triangle.setFillColor(Color4[st]);
	triangle.setOutlineThickness(3);
	triangle.setOutlineColor(Color::Black);
	triangle.setRotation(270);
	
	RectangleShape colorShape[5];

	
	Text MaxScore("MAX SCORE\n", font, 50);
	Text ScoreValue(PlScore, font, 70);
	MaxScore.setFillColor(Color3[st]);
	ScoreValue.setFillColor(Color1[st]);
	MaxScore.setPosition(Vector2f(1800, 100));
	ScoreValue.setPosition(Vector2f(1900, 160));


	while (window.isOpen())
	{
		Vector2i pixelPos = Mouse::getPosition(window);
		Vector2f pos = window.mapPixelToCoords(pixelPos);

		
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 1000;
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed or (Event::KeyPressed and event.key.code == Keyboard::Escape))
			{
				window.close();
			}
			head.control(event, head.x, head.y, time);
		}

		if (stage == Playing) {
			
			
			head.rect.setFillColor(Color1[st]);


			tail.UpdateTail(head.x, head.y, it);

			
			head.move(time);

			Apple Apple;
			Apple.GenerateApple(head.x, head.y);

			Map map;

			map.TouchTheWall(head);
			window.draw(head.rect);

			window.draw(Apple.apple);

			
			for (int i = 1; i < score * 10; i++)
				window.draw(tail.tail[i]);


			for (int i = 0; i < 100; i++)
				window.draw(map.m[i]);

			std::stringstream buf;
			std::string plScore;
			buf << score;
			buf >> plScore;
			pScore.setString("Score: " + plScore);
			window.draw(pScore);

			if (pos.x > 50 and pos.y > 30 and pos.x < 110 and pos.y < 100)
			{
				triangle.setOutlineThickness(10);
				if (Event::KeyPressed and event.key.code == Mouse::Left) stage = Menu;

			}
			else triangle.setOutlineThickness(3);
			window.draw(triangle);

			if (chanceToDie) tail.TouchTheTail(head.x, head.y);
			
		}

		if (stage == Menu)
		{
			if (pos.x > 550 and pos.y > 415 and pos.x < 1600 and pos.y < 700)
			{
				play.setFillColor(Color1[st]);
				if (Event::KeyPressed and event.key.code == Mouse::Left) stage = Playing;

			}
			else play.setFillColor(Color4[st]);

			if (pos.x > 700 and pos.y > 850 and pos.x < 1450 and pos.y < 970)
			{
				settings.setFillColor(Color1[st]);
				if (Event::KeyPressed and event.key.code == Mouse::Left) stage = Settings;

			}
			else settings.setFillColor(Color4[st]);

			
			window.draw(play);
			window.draw(settings);


			if ((Event::KeyPressed and event.key.code == Keyboard::Space)) stage = Playing;

		}

		if (stage == Settings)
		{
			if (CheckMaxScore()) {
				std::ifstream in("Score.txt");
				in >> PlScore;
				in.close();
				ScoreValue.setString(PlScore);
			}
			
			
			window.draw(color);

			colorShape[0].setPosition(800, 200);
			colorShape[0].setFillColor(Color2[0]);
			colorShape[0].setSize(Vector2f(50, 50));
			colorShape[0].setOutlineThickness(3);
			colorShape[0].setOutlineColor(Color::Black);
			colorShape[1].setPosition(900, 200);
			colorShape[1].setFillColor(Color2[1]);
			colorShape[1].setSize(Vector2f(50, 50));
			colorShape[1].setOutlineThickness(3);
			colorShape[1].setOutlineColor(Color::Black);
		    colorShape[2].setPosition(1000, 200);
			colorShape[2].setFillColor(Color2[2]);
			colorShape[2].setSize(Vector2f(50, 50));
			colorShape[2].setOutlineThickness(3);
			colorShape[2].setOutlineColor(Color::Black);
			colorShape[3].setPosition(1100, 200);
			colorShape[3].setFillColor(Color2[3]);
			colorShape[3].setSize(Vector2f(50, 50));
			colorShape[3].setOutlineThickness(3);
			colorShape[3].setOutlineColor(Color::Black);
			colorShape[4].setPosition(1200, 200);
			colorShape[4].setFillColor(Color2[4]);
			colorShape[4].setSize(Vector2f(50, 50));
			colorShape[4].setOutlineThickness(3);
			colorShape[4].setOutlineColor(Color::Black);

			

			window.draw(death);
			window.draw(deathShape);


			if (pos.x > 1000 and pos.y > 700 and pos.x < 1100 and pos.y < 800)
			{
				deathShape.setOutlineThickness(10);
				if (Event::KeyPressed and event.key.code == Mouse::Left) {
					if (chanceToDie == false) chanceToDie = true;
					else chanceToDie = false;
					stage = Menu;
				}

			}
			else deathShape.setOutlineThickness(3);
			if(chanceToDie == true) window.draw(deathFlag);
			

			for (int i = 0; i < 5; i++)
			{
				if (pos.x > 800 + 100 * i and pos.y > 200 and pos.x < 850 + 100 * i and pos.y < 250)
				{
					colorShape[i].setOutlineThickness(10);
					if (Event::KeyPressed and event.key.code == Mouse::Left)
					{
						st = i;
						stage = Menu;
					}

				}
				else colorShape[i].setOutlineThickness(3);
			}
			
			for (int i = 0; i < 5; i++)
				window.draw(colorShape[i]);

			if (pos.x > 50 and pos.y > 30 and pos.x < 110 and pos.y < 100)
			{
				triangle.setOutlineThickness(10);
				if (Event::KeyPressed and event.key.code == Mouse::Left) stage = Menu;

			}
			else triangle.setOutlineThickness(3);
			window.draw(triangle);


			window.draw(MaxScore);
			window.draw(ScoreValue);
		}

		
		window.display();
		window.clear(Color2[st]);
	}
}

