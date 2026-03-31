#include "Game.hpp"
#include "Grid.hpp"
#include "Logic.hpp"
#include "Render.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include "TileAnim.hpp"
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <algorithm>
#include <windows.h>

int WIN_SIZE = 875;

Game::Game()
    : window(sf::VideoMode({ (unsigned int)WIN_SIZE, (unsigned int)WIN_SIZE }), "2048"),
    n(4), state("not finish")
{
    window.setFramerateLimit(60);

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    window.setPosition(sf::Vector2i(
        (int)(desktop.size.x - WIN_SIZE) / 2,
        (int)(desktop.size.y - WIN_SIZE) / 2
    ));

    if (!font.openFromFile("assets/arial.ttf")) {}

    grid = init_grid(n);
    grid = number_implementation(grid);
    grid = number_implementation(grid);

    anims = std::vector<std::vector<TileAnim>>(n, std::vector<TileAnim>(n));
}

void Game::run() {
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        processEvents();
        update(dt);
        render();
    }
}

void Game::processEvents() {
    while (auto event = window.pollEvent()) {

        if (event->is<sf::Event::Closed>()) {
            window.close();
        }

        if (auto* kp = event->getIf<sf::Event::KeyPressed>()) {
            if (state != "not finish") return;
            char move = 0;
            if (kp->code == sf::Keyboard::Key::Z) move = 'z';
            if (kp->code == sf::Keyboard::Key::Q) move = 'q';
            if (kp->code == sf::Keyboard::Key::S) move = 's';
            if (kp->code == sf::Keyboard::Key::D) move = 'd';
            if (move) handleMove(move);
        }
    }
}

void Game::handleMove(char move) {
    std::vector<std::vector<int>> old_grid = grid;
    MoveResult result;

    if (move == 'z') result = add_z(old_grid, move);
    if (move == 'q') result = add_q(old_grid, move);
    if (move == 's') result = add_s(old_grid, move);
    if (move == 'd') result = add_d(old_grid, move);

    auto after_move = result.first;
    auto merged = result.second;

    grid = number_implementation(after_move);
    state = final_message(grid);

    for (auto& p : merged)
        anims[p.first][p.second] = { 1.3f, 0.15f, true };

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (after_move[i][j] == 0 && grid[i][j] != 0)
                anims[i][j] = { 1.3f, 0.15f, true };
}

void Game::update(float dt) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (anims[i][j].active) {
                anims[i][j].timer -= dt;
                if (anims[i][j].timer <= 0.f) {
                    anims[i][j].scale = 1.f;
                    anims[i][j].active = false;
                }
                else {
                    anims[i][j].scale = 1.f + 0.3f * (anims[i][j].timer / 0.15f);
                }
            }
        }
    }
}

void Game::render() {
    draw_grid(window, grid, font, anims);

    if (state != "not finish") {
        sf::RectangleShape overlay(sf::Vector2f(
            static_cast<float>(WIN_SIZE),
            static_cast<float>(WIN_SIZE)
        ));
        overlay.setFillColor(sf::Color(255, 255, 255, 150));
        window.draw(overlay);

        sf::Text msg(font, state, 40u);
        msg.setFillColor(sf::Color(119, 110, 101));

        sf::FloatRect b = msg.getLocalBounds();
        msg.setOrigin(sf::Vector2f(
            b.position.x + b.size.x / 2.f,
            b.position.y + b.size.y / 2.f
        ));
        msg.setPosition(sf::Vector2f(
            static_cast<float>(WIN_SIZE) / 2.f,
            static_cast<float>(WIN_SIZE) / 2.f
        ));
        window.draw(msg);
    }

    window.display();
}