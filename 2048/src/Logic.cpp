#include "Logic.hpp"
#include <cstdlib>
#include <algorithm>
#include "Grid.hpp"



std::vector<std::vector<int>> number_implementation(const std::vector<std::vector<int>>& grid) {
    if (is_full(grid)) return grid;
    int n = grid.size();
    auto ind = recup_ind(rand() % (n * n), n);
    if (grid[ind.first][ind.second] == 0)
        return filling(grid, ind.first, ind.second);
    return number_implementation(grid);
}

// movements
std::vector<int> zero_rl(const std::vector<int>& lst, char input) {
    int n = lst.size();
    std::vector<int> res(n, 0);
    int pos;
    if (input == 'd') {
        pos = n - 1;
        for (int i = n - 1; i >= 0; i--) if (lst[i] != 0) res[pos--] = lst[i];
    }
    else if (input == 'q') {
        pos = 0;
        for (int i = 0; i < n; i++) if (lst[i] != 0) res[pos++] = lst[i];
    }
    return res;
}

std::vector<std::vector<int>> zero_tb(const std::vector<std::vector<int>>& grid, char input) {
    std::vector<std::vector<int>> new_grid = grid;
    if (input == 's') input = 'd';
    if (input == 'z') input = 'q';
    int n = new_grid.size();
    for (int i = 0; i < n; i++) {
        std::vector<int> col;
        for (int j = 0; j < n; j++) col.push_back(new_grid[j][i]);
        col = zero_rl(col, input);
        for (int j = 0; j < n; j++) new_grid[j][i] = col[j];
    }
    return new_grid;
}



MoveResult add_q(const std::vector<std::vector<int>>& grid, char input) {
    std::vector<std::vector<int>> new_grid = grid;
    std::vector<std::pair<int, int>> merged;
    int n = new_grid.size();
    for (int i = 0; i < n; i++) {
        new_grid[i] = zero_rl(new_grid[i], input);
        for (int j = 0; j < n - 1; j++)
            if (new_grid[i][j] == new_grid[i][j + 1] && new_grid[i][j] != 0) {
                new_grid[i][j] *= 2; new_grid[i][j + 1] = 0; merged.push_back({ i, j });
            }
        new_grid[i] = zero_rl(new_grid[i], input);
    }
    return { new_grid, merged };
}

MoveResult add_d(const std::vector<std::vector<int>>& grid, char input) {
    std::vector<std::vector<int>> new_grid = grid;
    std::vector<std::pair<int, int>> merged;
    int n = new_grid.size();
    for (int i = 0; i < n; i++) {
        new_grid[i] = zero_rl(new_grid[i], input);
        int j = n - 1;
        while (j > 0) {
            if (new_grid[i][j] == new_grid[i][j - 1] && new_grid[i][j] != 0) {
                new_grid[i][j] *= 2; new_grid[i][j - 1] = 0; merged.push_back({ i, j });
            }
            j--;
        }
        new_grid[i] = zero_rl(new_grid[i], input);
    }
    return { new_grid, merged };
}

MoveResult add_z(const std::vector<std::vector<int>>& grid, char input) {
    std::vector<std::vector<int>> new_grid = zero_tb(grid, input);
    std::vector<std::pair<int, int>> merged;
    int n = new_grid.size();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n - 1; j++)
            if (new_grid[j][i] == new_grid[j + 1][i] && new_grid[j][i] != 0) {
                new_grid[j][i] *= 2; new_grid[j + 1][i] = 0; merged.push_back({ j, i });
            }
    return { zero_tb(new_grid, input), merged };
}

MoveResult add_s(const std::vector<std::vector<int>>& grid, char input) {
    std::vector<std::vector<int>> new_grid = zero_tb(grid, input);
    std::vector<std::pair<int, int>> merged;
    int n = new_grid.size();
    for (int i = 0; i < n; i++) {
        int j = n - 1;
        while (j > 0) {
            if (new_grid[j][i] == new_grid[j - 1][i] && new_grid[j][i] != 0) {
                new_grid[j][i] *= 2; new_grid[j - 1][i] = 0; merged.push_back({ j, i });
            }
            j--;
        }
    }
    return { zero_tb(new_grid, input), merged };
}
//research
bool dictionary_search(int elt, const std::vector<int>& lst, int a, int b) {
    if (b == -1) b = lst.size() - 1;
    int start = a, end = b - 1;
    if (start < end) {
        int middle = (start + end) / 2;
        if (elt > lst[middle]) return dictionary_search(elt, lst, middle + 1, b);
        else return dictionary_search(elt, lst, start, middle + 1);
    }
    return a < b && elt == lst[start];
}

bool dico_research_grid(int elt, const std::vector<std::vector<int>>& grid) {
    for (auto& row : grid) {
        std::vector<int> sorted_row = row;
        std::sort(sorted_row.begin(), sorted_row.end());
        if (dictionary_search(elt, sorted_row)) return true;
    }
    return false;
}

//final message
std::string final_message(const std::vector<std::vector<int>>& grid) {
    if (dico_research_grid(2048, grid)) return "You Won !";
    if (grid == add_z(grid, 'z').first && grid == add_q(grid, 'q').first &&
        grid == add_s(grid, 's').first && grid == add_d(grid, 'd').first) return "You Lose !";
    return "not finish";
}