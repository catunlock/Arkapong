#pragma once

#include <SFML/Graphics.hpp>
#include "constants.h"

struct Ball
{
	sf::CircleShape shape;
	sf::Vector2f velocity{ -ballVelocity, -ballVelocity };

	Ball(float mX, float mY)
	{
		shape.setPosition(mX, mY);
		shape.setRadius(ballRadius);
		shape.setFillColor(sf::Color::White);
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