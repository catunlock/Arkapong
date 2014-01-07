#pragma once

#include <SFML/Graphics.hpp>
#include "constants.h"

struct Brick
{
	sf::RectangleShape shape;

	bool destroyed{ false };

	Brick(float mX, float mY, sf::Color mColor)
		: shape(sf::Vector2f{ blockWidth, blockHeight })
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