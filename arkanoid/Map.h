#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

#include "constants.h"
#include "Brick.h"

struct Map
{
	std::vector<Brick> bricks;

	Map(std::string filePath, ColorMap& colorMap)
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

};