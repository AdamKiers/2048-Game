
#include "Grid.hpp"
#include <cstdlib>

//init
std::vector<std::vector<int>> init_grid(int size) {
    return std::vector<std::vector<int>>(size, std::vector<int>(size, 0));
}

std::pair<int, int> recup_ind(int index, int size) {
    return { index / size, index % size };
}

std::vector<std::vector<int>> filling(const std::vector<std::vector<int>>& grid, int i, int j) {
    std::vector<std::vector<int>> new_grid = grid;
    new_grid[i][j] = (rand() % 2 == 0) ? 2 : 4;
    return new_grid;
}

bool is_full(const std::vector<std::vector<int>>& grid) {
    for (auto& row : grid)
        for (int v : row)
            if (v == 0) return false;
    return true;
}
