#include "config.h" 		// The cmake configuration file

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Game.h"
#include "constants.h"

using namespace std;

int main()
{
	cout << "Version " << Arkapong_VERSION_MAJOR << "." << Arkapong_VERSION_MINOR << endl;
  
	sf::RenderWindow window{ sf::VideoMode{ windowWidth, windowHeight }, "Balls" };
	//window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	Game game(window);
	game.run();


	return 0; 
}
