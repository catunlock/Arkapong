#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <SFML/Graphics.hpp>

#include "constants.h"
#include "Brick.h"

// Typedef
typedef std::unordered_map<char, sf::Color> ColorMap;

class Map
{
public:
	// TODO: Check for the level file exists.
	Map(std::string filePath, ColorMap& colorMap) :
		filePath(filePath),
		colorMap(colorMap)
	{
		
	}

	void loadMap()
	{
		std::ifstream file{ filePath };
		char brickType{ '.' };

		for (int iY{ 0 }; iY < countBlocksY; iY++) {
			for (int iX{ 0 }; iX < countBlocksX; iX++) {
				file >> brickType;
#if _DEBUG
				std::cout << brickType;
#endif
				if (brickType != '.') {
					bricks.emplace_back((iX + 1) * (blockWidth + blockSpace) + blockXMargin,
						(iY + 1) * (blockHeight + blockSpace), colorMap[brickType]);
				}

			}
#if _DEBUG
			std::cout << std::endl;
#endif
		}
	}

public:
	std::vector<Brick> bricks;

private:
	std::string filePath;
	ColorMap& colorMap;

	

};