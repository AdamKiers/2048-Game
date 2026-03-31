#include "Render.hpp"
#include <SFML/Graphics.hpp>
#include "TileAnim.hpp"  
#include <vector>

sf::Color tileColor(int val) {
    switch (val) {
    case 0: return sf::Color(205, 193, 180);
    case 2: return sf::Color(238, 228, 218);
    case 4: return sf::Color(237, 224, 200);
    case 8: return sf::Color(242, 177, 121);
    case 16: return sf::Color(245, 149, 99);
    case 32: return sf::Color(246, 124, 95);
    case 64: return sf::Color(246, 94, 59);
    case 128: return sf::Color(237, 207, 114);
    case 256: return sf::Color(237, 204, 97);
    case 512: return sf::Color(237, 200, 80);
    case 1024: return sf::Color(237, 197, 63);
    case 2048: return sf::Color(237, 194, 46);
    default: return sf::Color(60, 58, 50);
    }
}

void draw_grid(sf::RenderWindow& window,
    const std::vector<std::vector<int>>& grid,
    const sf::Font& font,
    const std::vector<std::vector<TileAnim>>& anims)
{
    const float TILE = 200;
    const float GAP = 15;
    const float OFFSET = 15;
    int n = grid.size();

    window.clear(sf::Color(187, 173, 160));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int val = grid[i][j];
            float x = OFFSET + j * (TILE + GAP);
            float y = OFFSET + i * (TILE + GAP);
            float scale = anims[i][j].scale;

            // square
            float size = TILE * scale;
            sf::RectangleShape rect(sf::Vector2f(size, size));
            rect.setOrigin(sf::Vector2f(size / 2.f, size / 2.f));
            rect.setPosition(sf::Vector2f(x + TILE / 2.f, y + TILE / 2.f));
            rect.setFillColor(tileColor(val));
            window.draw(rect);

            // text
            if (val != 0) {
                sf::Text text(font, std::to_string(val), val < 100 ? 70u : val < 1000 ? 55u : 40u);
                text.setFillColor(val <= 4 ? sf::Color(119, 110, 101) : sf::Color::White);
                sf::FloatRect b = text.getLocalBounds();
                text.setOrigin(sf::Vector2f(b.position.x + b.size.x / 2.f, b.position.y + b.size.y / 2.f));
                text.setPosition(sf::Vector2f(x + TILE / 2.f, y + TILE / 2.f));
                text.setScale(sf::Vector2f(scale, scale));
                window.draw(text);
            }
        }
    }
}