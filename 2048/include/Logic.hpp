#pragma once
#include <vector>
#include <utility>
#include <string>

using MoveResult = std::pair<std::vector<std::vector<int>>, std::vector<std::pair<int, int>>>;



// movements
MoveResult add_z(const std::vector<std::vector<int>>& grid, char input);
MoveResult add_q(const std::vector<std::vector<int>>& grid, char input);
MoveResult add_s(const std::vector<std::vector<int>>& grid, char input);
MoveResult add_d(const std::vector<std::vector<int>>& grid, char input);

//other functions
std::string final_message(const std::vector<std::vector<int>>& grid);
std::vector<std::vector<int>> number_implementation(const std::vector<std::vector<int>>& grid);
std::vector<std::vector<int>> zero_tb(const std::vector<std::vector<int>>& grid, char input);

//research
bool dictionary_search(int elt, const std::vector<int>& lst, int a = 0, int b = -1);
bool dico_research_grid(int elt, const std::vector<std::vector<int>>& grid);