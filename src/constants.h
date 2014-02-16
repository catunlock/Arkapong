#pragma once

#define _USE_MATH_DEFINES // for C++
#include <cmath>

// Window fix size.
const unsigned int windowWidth{ 800 }, windowHeight{ 600 };

// Ball constants
const float ballRadius{ 6.0f }, ballVelocity{ 6.0f };

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

// Typedef
typedef std::unordered_map<char, sf::Color> ColorMap;