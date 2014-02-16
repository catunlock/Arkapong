#include "config.h" 		// The cmake configuration file
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

int main(int argc, char* argv[]) {

	/* Code adapted from the SFML 2 "Window" example */

	cout << "Version " << Arkapong_VERSION_MAJOR << "." << Arkapong_VERSION_MINOR << endl;

	sf::Window App(sf::VideoMode(800, 600), "myproject");

	while (App.isOpen()) {
		sf::Event Event;
		while (App.pollEvent(Event)) {
			if (Event.type == sf::Event::Closed)
				App.close();
		}
		App.display();
	}
}