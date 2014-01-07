#define _USE_MATH_DEFINES // for C++
#include <cmath>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include "angles.h"

using namespace std;
using namespace sf;

// Window fix size.
const unsigned int windowWidth{ 800 }, windowHeight{ 600 };
// Ball constants
const float ballRadius{ 6.0f }, ballVelocity{ 4.0f };
// Paddle constants
const float paddleHeight{ 80.0f }, paddleWidth{ 20.0f }, paddleVelocity{ 14.0f };
const double paddleToRadians{ M_PI / paddleHeight };
const float paddleWindowMargin{ 10.0f };
// Bricks constants
const float blockWidth{ 80.0f }, blockHeight{ 25.0f }, blockSpace{ 3 };
const int countBlocksX{ 7 }, countBlocksY{ 20 };
const float blockXMargin{ windowWidth / 2 - ((blockWidth + blockSpace) / 1.5f * countBlocksX) };
// Degree constants
const double maxRadian{ M_PI * 2 };

typedef std::unordered_map<char, sf::Color> ColorMap;

// Objects
struct Brick
{
	RectangleShape shape;

	bool destroyed{ false };

	Brick(float mX, float mY, Color mColor)
		: shape(Vector2f{ blockWidth, blockHeight })
	{
		shape.setPosition(mX, mY);
		shape.setFillColor(mColor);
		shape.setOrigin(blockWidth / 2.0f, blockHeight / 2.0f);
	}

	float x()		{ return shape.getPosition().x; }
	float y()		{ return shape.getPosition().y; }
	float top()		{ return y() - blockHeight / 2.0f; }
	float bottom()	{ return y() + blockHeight / 2.0f; }
	float left()	{ return x() - blockWidth / 2.0f; }
	float right()	{ return x() + blockWidth / 2.0f; }
};

struct Map
{
	vector<Brick> bricks;

	Map(string filePath, ColorMap& colorMap)
	{
		ifstream file{ filePath };
		char brickType{ '.' };
		
		for (int iY{ 0 }; iY < countBlocksY; iY++) {
			for (int iX{ 0 }; iX < countBlocksX; iX++) {	
				file >> brickType;
				cout << brickType;

				if (brickType != '.') {
					bricks.emplace_back((iX + 1) * (blockWidth + blockSpace) + blockXMargin,
						(iY + 1) * (blockHeight + blockSpace), colorMap[brickType]);
				}
				
			}
			cout << endl;
		}
	}

};

struct Paddle
{
	struct Keys
	{
		Keyboard::Key keyUp;
		Keyboard::Key keyDown;

		Keys(Keyboard::Key mKeyUp, Keyboard::Key mKeyDown) : 
			keyUp{ mKeyUp }, keyDown{ mKeyDown }
		{
			cout << "Creating new set of Keys for a paddle..." << endl;
		}

		// TODO: Quiza cambiarlo por un move constructor seria mas adecuado.
		Keys(const Keys& other) :
			keyUp{ other.keyUp }, keyDown{ other.keyDown }
		{
			cout << "Copying a new set of keys for a paddle..." << endl;
		}
	} keys;

	RectangleShape shape;
	Vector2f velocity{ 0.0f, 0.0f };
	bool moveUp{ false };
	bool moveDown{ false };

	Paddle(float mX, float mY, Paddle::Keys& paddleKeys) : 
		shape{ Vector2f{ paddleWidth, paddleHeight } },
		keys{ paddleKeys }
	{
		shape.setPosition(mX, mY);
		shape.setFillColor(sf::Color{ 100, 100, 100, 255 });
		//shape.setOutlineColor(Color::Black);
		//shape.setOutlineThickness(3.0f);
		shape.setOrigin(paddleWidth / 2, paddleHeight / 2);
	}

	void update()
	{
		if (moveUp && top() > 0)
			velocity.y = -paddleVelocity;
		else if (moveDown && bottom() < windowHeight)
			velocity.y = paddleVelocity;
		else
			velocity.y = 0;

		shape.move(velocity);
	}

	float x()		{ return shape.getPosition().x; }
	float y()		{ return shape.getPosition().y; }
	float top()		{ return y() - paddleHeight / 2.0f; }
	float bottom()	{ return y() + paddleHeight / 2.0f; }
	float left()	{ return x() - paddleWidth / 2.0f; }
	float right()	{ return x() + paddleWidth/ 2.0f; }
};

struct Ball
{
	CircleShape shape;
	Vector2f velocity{ -ballVelocity, -ballVelocity };
	float angle;

	Ball(float mX, float mY) 
	{
		angle = 0;
		shape.setPosition(mX, mY);
		shape.setRadius(ballRadius);
		shape.setFillColor(Color::White);
		//shape.setOutlineColor(Color::Black);
		//shape.setOutlineThickness(3.1415f);
		shape.setOrigin(ballRadius, ballRadius);
	};

	void update()
	{
		shape.move(velocity);

		if (top() < 0 || bottom() > windowHeight) { velocity.y *= -1; }
		if (left() < 0 || right() > windowWidth) { velocity.x *= -1; }
		
		/*		//Manual control.
		if (sf::Keyboard::isKeyPressed(Keyboard::U)) { shape.move(0, -1); }
		if (sf::Keyboard::isKeyPressed(Keyboard::J)) { shape.move(0, 1); }
		if (sf::Keyboard::isKeyPressed(Keyboard::H)) { shape.move(-1, 0); }
		if (sf::Keyboard::isKeyPressed(Keyboard::K)) { shape.move(1, 0); }
		*/
	}

	float x()		{ return shape.getPosition().x; }
	float y()		{ return shape.getPosition().y; }
	float top()		{ return y() - ballRadius; }
	float bottom()	{ return y() + ballRadius; }
	float left()	{ return x() - ballRadius; }
	float right()	{ return x() + ballRadius; }
};

template<class T1> bool isIntersecting(T1& mA, Ball& mBall)
{
	bool aRight_GE_bLeft = mA.right() >= mBall.left();
	bool aLeft_LE_bRight = mA.left() <= mBall.right();
	bool aBottom_GE_bTop = mA.bottom() >= mBall.top();
	bool aTop_LE_bBottom = mA.top() <= mBall.bottom();

	bool intersecting = aRight_GE_bLeft &&  aLeft_LE_bRight 
		&& aBottom_GE_bTop  && aTop_LE_bBottom;

//	if (intersecting) 

	return intersecting;
}

/*
template<class T1, class T2> bool isIntersecting(T1& mA, T2& mB)
{
	return mA.right() >= mB.left() && mA.left() <= mB.right()
		&& mA.bottom() >= mB.top() && mA.top() <= mB.bottom();
}
*/

void testCollision(Paddle& paddle, Ball& ball)
{
	if (!isIntersecting(paddle, ball)) return;

	// Calculate the Y where collide the ball in the paddle.
	float tocado{ ball.y() - paddle.top() };
	// Calcula el nuevo angulo de la bola teniendo en cuenta, que al restar la 
	// posicion donde a tocado, a la mitad de la altura de la paleta, si el numero 
	// es positivo la pelota sale
	// hacia arriba, si es negativo hacia abajo
	float newAngle = ((paddleHeight / 2) - tocado) * paddleToRadians;

	// negamos el sinus porque en sfml la cordneada 0,0 es arriba a la izquierda.
	float cosinus = cos(newAngle), sinus = -sin(newAngle);

#if _DEBUG
	cout << "New angle: " << newAngle << " cos: " << cosinus << " sin: " << sinus << endl;
#endif

	// if the ball has a positive velocity in the x-axis means the ball collide to the right paddle.
	ball.velocity.x = (ball.velocity.x > 0) ? -(cosinus*ballVelocity) : cosinus*ballVelocity;
	ball.velocity.y = sinus * ballVelocity;
}

void testCollision(Brick& brick, Ball& ball)
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

void processKeyEvent(Paddle& paddle, Event& event, bool isKeyPressed)
{
	if (event.key.code == paddle.keys.keyUp)
		paddle.moveUp = isKeyPressed;
	else if (event.key.code == paddle.keys.keyDown)
		paddle.moveDown = isKeyPressed;
}

void processMouseMoveEvent(Paddle& paddle, Event& event)
{
	paddle.shape.setPosition(paddle.x(), event.mouseMove.y);
}

int main()
{
	testRadians();

	RenderWindow window{ VideoMode{ windowWidth, windowHeight }, "Balls" };
	//window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	Ball ball{ windowWidth / 2, windowHeight / 2 };

	Paddle::Keys paddle1Keys{ Keyboard::W, Keyboard::S };
	Paddle::Keys paddle2Keys{ Keyboard::Up, Keyboard::Down };

	Paddle paddle1{ paddleWindowMargin + 10, windowHeight / 2, paddle1Keys };
	Paddle paddle2{ windowWidth - paddleWindowMargin - 10 , windowHeight / 2, paddle2Keys };

	ColorMap colorMap;
	colorMap['R'] = sf::Color::Red;
	colorMap['B'] = sf::Color::Cyan;

	Map map("level0.txt", colorMap);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			else if (event.type == Event::KeyPressed)
			{
				processKeyEvent(paddle1, event, true);
				processKeyEvent(paddle2, event, true);
			}
			else if (event.type == Event::KeyReleased)
			{
				processKeyEvent(paddle1, event, false);
				processKeyEvent(paddle2, event, false);
			}
			else if (event.type == Event::MouseMoved) {
				processMouseMoveEvent(paddle1, event);
			}
		}

		ball.update();
		paddle1.update();
		paddle2.update();

		testCollision(paddle1, ball);
		testCollision(paddle2, ball);
		for (auto& brick : map.bricks) testCollision(brick, ball);

		map.bricks.erase(remove_if(begin(map.bricks), end(map.bricks),
			[](const Brick& mBrick){ return mBrick.destroyed; }), end(map.bricks));
		
		// Drawing
		window.clear();
		for (auto& brick : map.bricks) window.draw(brick.shape);
		window.draw(ball.shape);
		window.draw(paddle1.shape);
		window.draw(paddle2.shape);
		window.display();
	}

	return 0; 
}
