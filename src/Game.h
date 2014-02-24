#ifndef GAME_HEADER
#define GAME_HEADER

#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Paddle.h"
#include "Map.h"

class Game 
{
public:
	Game(sf::RenderWindow& window);
	~Game();

	void processEvents();
	void update();
	void draw();
	void run();

private:
	void processKeyEvent(Paddle& paddle, sf::Event& event, bool isKeyPressed);
	void processMouseMoveEvent(Paddle& paddle, sf::Event& event);
	void testCollision(Brick& brick, Ball& ball);
	void testCollision(Paddle& paddle, Ball& ball);

private:
	sf::RenderWindow&	window;
	Ball				ball;
	Paddle::Keys		paddle1Keys;
	Paddle::Keys		paddle2Keys;
	Paddle				paddle1;
	Paddle				paddle2;
	ColorMap			colorMap;
	Map					map;
};

#endif