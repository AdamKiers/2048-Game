#pragma once
#include <vector>
#include <utility>

//init
std::vector<std::vector<int>> init_grid(int size);
std::pair<int, int> recup_ind(int index, int size);
std::vector<std::vector<int>> filling(const std::vector<std::vector<int>>& grid, int i, int j);
bool is_full(const std::vector<std::vector<int>>& grid);