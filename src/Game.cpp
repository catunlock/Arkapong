#include "Game.h"

Game::Game(sf::RenderWindow& window) :
	window{window},
	ball{ windowWidth / 2, windowHeight / 2 },
	paddle1Keys{ sf::Keyboard::W, sf::Keyboard::S },
	paddle2Keys{ sf::Keyboard::Up, sf::Keyboard::Down },
	paddle1{ paddleWindowMargin + 10, windowHeight / 2, paddle1Keys },
	paddle2{ windowWidth - paddleWindowMargin - 10, windowHeight / 2, paddle2Keys },
	map{ "resources/level1.txt", colorMap }

{
	colorMap['R'] = sf::Color::Red;
	colorMap['B'] = sf::Color::Cyan;
}

Game::~Game()
{

}

template<class T1, class T2> bool isIntersecting(T1& mA, T2& mB)
{
	return mA.right() >= mB.left() && mA.left() <= mB.right()
		&& mA.bottom() >= mB.top() && mA.top() <= mB.bottom();
}

void Game::testCollision(Brick& brick, Ball& ball)
{
	if (!isIntersecting(brick, ball)) return;

	brick.destroyed = true;

	// Calculate how much the ball intersects the brick. 
	// The order of the subs are important to maintain positive the overlap X and Y.
	float overlapLeft{ ball.right() - brick.left() };
	float overlapRight{ brick.right() - ball.left() };
	float overlapTop{ ball.bottom() - brick.top() };
	float overlapBottom{ brick.bottom() - ball.top() };

	bool fromLeft{ abs(overlapLeft) < abs(overlapRight) };
	bool fromTop{ abs(overlapTop) < abs(overlapBottom) };

	float minOverlapX{ fromLeft ? overlapLeft : overlapRight };
	float minOverlapY{ fromTop ? overlapTop : overlapBottom };

	if (abs(minOverlapX) < abs(minOverlapY))
		ball.velocity.x = fromLeft ? -ballVelocity : ballVelocity;
	else
		ball.velocity.y = fromTop ? -ballVelocity : ballVelocity;
}

void Game::testCollision(Paddle& paddle, Ball& ball)
{
	if (!isIntersecting(paddle, ball)) return;

	// Calculate the Y where collide the ball in the paddle.
	float tocado{ ball.y() - paddle.top() };
	// Calcula el nuevo angulo de la bola teniendo en cuenta, que al restar la 
	// posicion donde a tocado, a la mitad de la altura de la paleta, si el numero 
	// es positivo la pelota sale
	// hacia arriba, si es negativo hacia abajo
	float newAngle = ((paddleHeight / 2.0f) - tocado) * paddleToRadians;

	// negamos el sinus porque en sfml la cordneada 0,0 es arriba a la izquierda.
	float cosinus = cos(newAngle), sinus = -sin(newAngle);

	// if the ball has a positive velocity in the x-axis means the ball collide to the right paddle.
	ball.velocity.x = (ball.velocity.x > 0) ? -(cosinus*ballVelocity) : cosinus*ballVelocity;
	ball.velocity.y = sinus * ballVelocity;
}

void Game::processKeyEvent(Paddle& paddle, sf::Event& event, bool isKeyPressed)
{
	if (event.key.code == paddle.keys.keyUp)
		paddle.moveUp = isKeyPressed;
	else if (event.key.code == paddle.keys.keyDown)
		paddle.moveDown = isKeyPressed;
}

void Game::processMouseMoveEvent(Paddle& paddle, sf::Event& event)
{
	paddle.shape.setPosition(paddle.x(), event.mouseMove.y);
}

void Game::processEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			processKeyEvent(paddle1, event, true);
			processKeyEvent(paddle2, event, true);
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			processKeyEvent(paddle1, event, false);
			processKeyEvent(paddle2, event, false);
		}
		else if (event.type == sf::Event::MouseMoved)
		{
			processMouseMoveEvent(paddle1, event);
		}
	}
}

void Game::update()
{
	ball.update();
	paddle1.update();
	paddle2.update();

	testCollision(paddle1, ball);
	testCollision(paddle2, ball);
	for (auto& brick : map.bricks) testCollision(brick, ball);

	map.bricks.erase(remove_if(begin(map.bricks), end(map.bricks),
		[](const Brick& mBrick){ return mBrick.destroyed; }), end(map.bricks));
}

void Game::draw()
{
	window.clear();
	for (auto& brick : map.bricks) window.draw(brick.shape);
	window.draw(ball.shape);
	window.draw(paddle1.shape);
	window.draw(paddle2.shape);
	window.display();
}

void Game::run()
{
	while (window.isOpen())
	{
		processEvents();
		update();
		draw();
	}
}