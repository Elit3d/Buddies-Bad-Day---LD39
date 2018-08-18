#include "game.h"

int main()
{
	Game game;
	sf::RenderWindow window(sf::VideoMode(800, 640), "Buddies Bad Day - LD39 - Running out of Power");
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false); // need this for looping animations with keypress

	game.Setup();
	game.Update(window);

	return 0;
}