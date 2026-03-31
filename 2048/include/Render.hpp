#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "TileAnim.hpp"

sf::Color tileColor(int val);

void draw_grid(sf::RenderWindow& window,
    const std::vector<std::vector<int>>& grid,
    const sf::Font& font,
    const std::vector<std::vector<TileAnim>>& anims);