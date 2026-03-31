#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "TileAnim.hpp"

class Game {
public:
	Game();
	void run();
private:
	void processEvents();
	void update(float dt);
	void render();

	void handleMove(char move);

private:
    sf::RenderWindow window;
    sf::Font font;

    int n;
    std::vector<std::vector<int>> grid;
    std::vector<std::vector<TileAnim>> anims;

    std::string state;
    sf::Clock clock;
};