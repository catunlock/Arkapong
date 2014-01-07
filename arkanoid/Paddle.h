#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "constants.h"

struct Paddle
{
	struct Keys
	{
		sf::Keyboard::Key keyUp;
		sf::Keyboard::Key keyDown;

		Keys(sf::Keyboard::Key mKeyUp, sf::Keyboard::Key mKeyDown) :
			keyUp{ mKeyUp }, keyDown{ mKeyDown }
		{
#if _DEBUG
			std::cout << "Creating new set of Keys for a paddle..." << std::endl;
#endif
		}

		// TODO: Quiza cambiarlo por un move constructor seria mas adecuado.
		Keys(const Keys& other) :
			keyUp{ other.keyUp }, keyDown{ other.keyDown }
		{
#if _DEBUG
			std::cout << "Copying a new set of keys for a paddle..." << std::endl;
#endif
		}
	} keys;

	sf::RectangleShape shape;
	sf::Vector2f velocity{ 0.0f, 0.0f };
	bool moveUp{ false };
	bool moveDown{ false };

	Paddle(float mX, float mY, Paddle::Keys& paddleKeys) :
		shape{ sf::Vector2f{ paddleWidth, paddleHeight } },
		keys{ paddleKeys }
	{
		shape.setPosition(mX, mY);
		shape.setFillColor(sf::Color{ 100, 100, 100, 255 });
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
	float right()	{ return x() + paddleWidth / 2.0f; }
};