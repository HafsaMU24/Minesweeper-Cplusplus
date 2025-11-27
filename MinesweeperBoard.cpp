#include "MinesweeperBoard.h"
#include "Game.h" 

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <fstream>
#include <limits>


MinesweeperBoard::MinesweeperBoard(int rows, int cols, int num_mines) 
    : rows_(rows), cols_(cols), num_mines_(num_mines) 
{
    board_.resize(rows, std::vector<Cell>(cols));

    safe_cells_to_reveal_ = (rows * cols) - num_mines; 
    
    place_mines();
    calculate_adjacent_mines();
}


void MinesweeperBoard::place_mines() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> row_dist(0, rows_ - 1);
    std::uniform_int_distribution<> col_dist(0, cols_ - 1);

    int mines_placed = 0;
    while (mines_placed < num_mines_) {
        int r = row_dist(gen);
        int c = col_dist(gen);
        if (!board_[r][c].has_mine) {
            board_[r][c].has_mine = true;
            mines_placed++;
        }
    }
}


void MinesweeperBoard::calculate_adjacent_mines() {
    for (int r = 0; r < rows_; ++r) {
        for (int c = 0; c < cols_; ++c) {
            if (!board_[r][c].has_mine) {
                board_[r][c].adjacent_mines = count_adjacent_mines(r, c);
            }
        }
    }
}


int MinesweeperBoard::count_adjacent_mines(int r, int c) const {
    int count = 0;
    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            if (dr == 0 && dc == 0) continue; 
            int nr = r + dr;
            int nc = c + dc;
            if (is_valid_coord(nr, nc) && board_[nr][nc].has_mine) {
                count++;
            }
        }
    }
    return count;
}


bool MinesweeperBoard::is_valid_coord(int r, int c) const {
    return r >= 0 && r < rows_ && c >= 0 && c < cols_;
}


bool MinesweeperBoard::reveal_cell(int r, int c) {
    if (!is_valid_coord(r, c) || board_[r][c].is_revealed || board_[r][c].is_flagged) {
        return true; 
    }

    board_[r][c].is_revealed = true;

    if (board_[r][c].has_mine) {
        return false; 
    }
    
    safe_cells_to_reveal_--;
   /*

    if (board_[r][c].adjacent_mines == 0) {
        auto_reveal_adjacent(r, c);
    }

    */
    return true;
}

/*

void MinesweeperBoard::auto_reveal_adjacent(int r, int c) {
    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            if (dr == 0 && dc == 0) continue; 
            int nr = r + dr;
            int nc = c + dc;

            if (is_valid_coord(nr, nc) && !board_[nr][nc].is_revealed && !board_[nr][nc].is_flagged) {
                board_[nr][nc].is_revealed = true;
                safe_cells_to_reveal_--;

                if (board_[nr][nc].adjacent_mines == 0) {
                    auto_reveal_adjacent(nr, nc);
                }
            }
        }
    }
}

*/

void MinesweeperBoard::flag_cell(int r, int c) {
    if (is_valid_coord(r, c) && !board_[r][c].is_revealed) {
        board_[r][c].is_flagged = !board_[r][c].is_flagged; 
        std::cout << "Ruta " << (char)('a' + r) << (c + 1) 
                  << (board_[r][c].is_flagged ? " flaggad." : " avflaggad.") << std::endl;
    } else {
        std::cout << " Ogiltig koordinat eller rutan är redan avtäckt." << std::endl;

    }
}

bool MinesweeperBoard::check_win() const {
    return safe_cells_to_reveal_ == 0;
}

void MinesweeperBoard::print_board() const {

    auto draw_horizontal_line = [this]() {
       
        std::cout << "     +";
        for (int c = 0; c < cols_; ++c) {
            
            std::cout << "---+"; 
        }
        std::cout << "\n";
    };

 
    std::cout << "\n        ";
    for (int c = 0; c < cols_; ++c) {
        std::cout << " " << c + 1 << " "; 
    }
    std::cout << "\n";
    
    draw_horizontal_line(); 

  
    for (int r = 0; r < rows_; ++r) {
        std::cout << "   " << (char)('a' + r) << " |"; 
        
        for (int c = 0; c < cols_; ++c) {

            std::cout << ' ' << board_[r][c].get_display_char() << ' ';
            std::cout << '|';
        }
        std::cout << "\n"; 

      
        draw_horizontal_line();
    }
}