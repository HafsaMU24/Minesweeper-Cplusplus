#ifndef MINESWEEPERBOARD_H
#define MINESWEEPERBOARD_H

#include "Cell.h"

#include <vector>
#include <string>
#include <random>
#include <fstream>


class MinesweeperBoard {
public:
    MinesweeperBoard(int rows, int cols, int num_mines);
    ~MinesweeperBoard() = default;

    void print_board() const;
    
    bool reveal_cell(int r, int c); 
    void flag_cell(int r, int c);
    bool check_win() const;
    bool is_valid_coord(int r, int c) const;
    
    int get_safe_cells_remaining() const { return safe_cells_to_reveal_; }
    int get_cols() const { return cols_; } 


private:
    int rows_;
    int cols_;
    int num_mines_;
    int safe_cells_to_reveal_;

    std::vector<std::vector<Cell>> board_; 

    void place_mines();
    void calculate_adjacent_mines();
    int count_adjacent_mines(int r, int c) const;
   // void auto_reveal_adjacent(int r, int c); 
};

#endif
 