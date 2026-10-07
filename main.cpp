#include <SFML/Graphics.hpp>

#include "ColorDesign.h"

#include <deque>
#include <fstream>
#include <iostream>
#include <random>
#include <string>

using namespace sf;

enum Stage { Playing, Menu, Settings };
Stage stage = Menu;

enum direction { STOP, UP, DOWN, LEFT, RIGHT };
direction dir;

int score = 0;
int st = 0;

bool CheckMaxScore()
{
	int currentMaxScore = 0;
	std::ifstream in("Score.txt");
	in >> currentMaxScore;

	if (score <= currentMaxScore)
		return false;

	std::ofstream out("Score.txt", std::ios::trunc);
	if (!out)
		return false;

	out << score;
	return static_cast<bool>(out);
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

	void control(Event& event, float& x, float& y, float time)
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

	void SetTheme(int theme)
	{
		for (int i = 0; i < num; ++i)
			m[i].setFillColor(Color3[theme]);
	}

	void TouchTheWall(SnakeHead& head)
	{
		if (head.x < beginX + 40) head.x = beginX + width - 55;
		else if (head.x > beginX + width - 55) head.x = beginX + 40;
		else if (head.y < beginY + 40) head.y = beginY + height - 20;
		else if (head.y > beginY + height - 10) head.y = beginY + 40;

		head.rect.setPosition(head.x, head.y);
	}



};

int AppleX = 1100, AppleY = 600;


class Apple
{
public:

	CircleShape apple;

	void GenerateApple(float x, float y)
	{
		apple.setFillColor(Color5[st]);
		apple.setRadius(10);
		apple.setOutlineThickness(2);
		apple.setOutlineColor(Color::Black);

		if (x + 10 > AppleX and y + 10 > AppleY &&
			x + 10 < AppleX + 20 && y + 10 < AppleY + 20)
		{
			static std::mt19937 randomEngine{ std::random_device{}() };
			static std::uniform_int_distribution<int> appleColumn(32, 77);
			static std::uniform_int_distribution<int> appleRow(8, 55);

			AppleX = appleColumn(randomEngine) * 20;
			AppleY = appleRow(randomEngine) * 20;
			++score;
		}

		apple.setPosition(static_cast<float>(AppleX), static_cast<float>(AppleY));
	}
};


class Tail
{
public:
	std::deque<CircleShape> segments;

	void UpdateTail(float x, float y)
	{
		if (score <= 0)
		{
			segments.clear();
			return;
		}

		CircleShape segment;
		segment.setPosition(x, y);
		segment.setFillColor(Color1[st]);
		segment.setRadius(10);
		segments.push_front(segment);

		const std::size_t targetLength = static_cast<std::size_t>(score) * 10U;
		if (segments.size() > targetLength)
			segments.pop_back();
	}

	void TouchTheTail(float x, float y)
	{
		for (const CircleShape& segment : segments)
		{
			const Vector2f segmentPosition = segment.getPosition();
			bool collision = false;

			if (dir == LEFT)
				collision = x < segmentPosition.x + 20 && x > segmentPosition.x + 15 &&
				y > segmentPosition.y - 10 && y < segmentPosition.y + 10;
			else if (dir == RIGHT)
				collision = x > segmentPosition.x - 20 && x < segmentPosition.x - 15 &&
				y > segmentPosition.y - 10 && y < segmentPosition.y + 10;
			else if (dir == UP)
				collision = y < segmentPosition.y + 20 && y > segmentPosition.y + 15 &&
				x > segmentPosition.x - 10 && x < segmentPosition.x + 10;
			else if (dir == DOWN)
				collision = y > segmentPosition.y - 20 && y < segmentPosition.y - 15 &&
				x > segmentPosition.x - 10 && x < segmentPosition.x + 10;

			if (collision)
			{
				CheckMaxScore();
				score = 0;
				segments.clear();
				return;
			}
		}
	}
};


int main()
{

	int highScore = 0;
	{
		std::ifstream scoreFile("Score.txt");
		scoreFile >> highScore;
	}
	const std::string PlScore = std::to_string(highScore);


	ColorDesign colorDesign;

	Font font;
	if (!font.loadFromFile("resources/font1.ttf"))
	{
		std::cerr << "Failed to load font: resources/font1.ttf\n";
		return 1;
	}

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
	Apple apple;
	Map map;

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
			if (event.type == Event::Closed)
			{
				window.close();
			}
			else if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Escape)
					window.close();
				else if (stage == Menu && event.key.code == Keyboard::Space)
					stage = Playing;
				else if (stage == Playing)
					head.control(event, head.x, head.y, time);
			}
			else if (event.type == Event::MouseButtonPressed &&
				event.mouseButton.button == Mouse::Left)
			{
				const Vector2f clickPosition = window.mapPixelToCoords(
					Vector2i(event.mouseButton.x, event.mouseButton.y));

				if (stage == Playing && clickPosition.x > 50 && clickPosition.y > 30 &&
					clickPosition.x < 110 && clickPosition.y < 100)
				{
					stage = Menu;
				}
				else if (stage == Menu)
				{
					if (clickPosition.x > 550 && clickPosition.y > 415 &&
						clickPosition.x < 1600 && clickPosition.y < 700)
						stage = Playing;
					else if (clickPosition.x > 700 && clickPosition.y > 850 &&
						clickPosition.x < 1450 && clickPosition.y < 970)
						stage = Settings;
				}
				else if (stage == Settings)
				{
					if (clickPosition.x > 50 && clickPosition.y > 30 &&
						clickPosition.x < 110 && clickPosition.y < 100)
					{
						stage = Menu;
					}
					else if (clickPosition.x > 1000 && clickPosition.y > 700 &&
						clickPosition.x < 1100 && clickPosition.y < 800)
					{
						chanceToDie = !chanceToDie;
						stage = Menu;
					}
					else
					{
						for (int i = 0; i < 5; ++i)
						{
							if (clickPosition.x > 800 + 100 * i &&
								clickPosition.y > 200 &&
								clickPosition.x < 850 + 100 * i &&
								clickPosition.y < 250)
							{
								st = i;
								map.SetTheme(st);
								stage = Menu;
								break;
							}
						}
					}
				}
			}
		}

		if (!window.isOpen())
			break;

		if (stage == Playing) {


			head.rect.setFillColor(Color1[st]);


			tail.UpdateTail(head.x, head.y);


			head.move(time);

			apple.GenerateApple(head.x, head.y);
			map.TouchTheWall(head);
			window.draw(head.rect);

			window.draw(apple.apple);


			for (const CircleShape& segment : tail.segments)
				window.draw(segment);


			for (int i = 0; i < 100; i++)
				window.draw(map.m[i]);

			pScore.setString("Score: " + std::to_string(score));
			window.draw(pScore);

			if (pos.x > 50 and pos.y > 30 and pos.x < 110 and pos.y < 100)
			{
				triangle.setOutlineThickness(10);

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

			}
			else play.setFillColor(Color4[st]);

			if (pos.x > 700 and pos.y > 850 and pos.x < 1450 and pos.y < 970)
			{
				settings.setFillColor(Color1[st]);

			}
			else settings.setFillColor(Color4[st]);


			window.draw(play);
			window.draw(settings);



		}

		if (stage == Settings)
		{
			if (CheckMaxScore())
				ScoreValue.setString(std::to_string(score));


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

			}
			else deathShape.setOutlineThickness(3);
			if (chanceToDie == true) window.draw(deathFlag);


			for (int i = 0; i < 5; i++)
			{
				if (pos.x > 800 + 100 * i and pos.y > 200 and pos.x < 850 + 100 * i and pos.y < 250)
				{
					colorShape[i].setOutlineThickness(10);

				}
				else colorShape[i].setOutlineThickness(3);
			}

			for (int i = 0; i < 5; i++)
				window.draw(colorShape[i]);

			if (pos.x > 50 and pos.y > 30 and pos.x < 110 and pos.y < 100)
			{
				triangle.setOutlineThickness(10);

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

