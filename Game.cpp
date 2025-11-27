#include "Game.h"

#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <limits>   


Game::Game(int rows, int cols, int num_mines) 
    : status_(GameStatus::PLAYING) 
{
    board_ptr_ = std::make_unique<MinesweeperBoard>(rows, cols, num_mines);
}

void Game::handle_reveal_action(int r, int c) {
   
    if (!board_ptr_->reveal_cell(r, c)) {
        status_ = GameStatus::LOST;
        return;
    }
    
   
    if (board_ptr_->check_win()) {
        status_ = GameStatus::WON;
    }
}

bool Game::parse_input(const std::string& input, int& r, int& c, char& action) {
    std::stringstream ss(input);
    std::string token;
    
    if (!(ss >> token)) {
        return false; 
    }

    
    if (token.length() == 1 && (to_lower(token[0]) == 'f')) {
        action = 'f';
      
        if (!(ss >> token)) {
            std::cout << "'f' måste följas av en koordinat (t.ex. 'f c5')." << std::endl;
            return false; 
        }
    } else {
        action = 'r'; 
    }
    
   
    if (token.empty()) {
        std::cout << " Koordinaten är tom. Ange t.ex. 'a1'." << std::endl;
        return false;
    }
    
    if (!is_alpha(token[0])) { 
        std::cout << " Koordinaten måste börja med en bokstav (rad) följt av ett nummer (kolumn). T.ex. 'a1'." << std::endl;
        return false; 
    }

    r = to_lower(token[0]) - 'a'; 
    
    std::string col_str = token.substr(1);
    
   
    if (col_str.empty()) {
        std::cout << " Koordinaten saknar kolumnnummer. T.ex. 'a1'." << std::endl;
        return false;
    }

    for (char ch : col_str) {
        if (!is_digit(ch)) { 
            std::cout << " Kolumnen måste vara ett nummer. T.ex. 'a1', inte 'aB' eller 'a1 2'." << std::endl;
            return false;
        }
    }
    
    std::stringstream col_ss(col_str);
    int col_num;

    if (!(col_ss >> col_num) || !col_ss.eof()) {
    
        std::cout << " Kunde inte tolka kolumnnummer korrekt. Försök med en siffra (1-" << board_ptr_->get_cols() << ")." << std::endl; 
        return false; 
    }
    
    c = col_num - 1;

    
    if (!board_ptr_->is_valid_coord(r, c)) {
        std::cout << " Koordinat '" << token << "' ligger utanför spelplanen." << std::endl;
        return false;
    }
    return true;
}

void Game::play_turn() {
    std::string input;
    int r, c;
    char action;
    
    while (status_ == GameStatus::PLAYING) {
        board_ptr_->print_board();
        std::cout << "\nAntal säkra rutor kvar att avslöja: " << board_ptr_->get_safe_cells_remaining() << std::endl; 
        std::cout << "Ange ruta (t.ex. 'b2') eller 'f' + ruta för att flagga (t.ex. 'f c5'), eller 'q' för att avsluta: ";
        
       
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::getline(std::cin, input);

        if (input.empty()) {
            continue; 
        }
        
        if (parse_input(input, r, c, action)) {
            if (action == 'r') {
                handle_reveal_action(r, c); 
            } else if (action == 'f') {
                board_ptr_->flag_cell(r, c);
            }
        } else {
            
        }
    }

   
    if (status_ == GameStatus::LOST) { 
        board_ptr_->print_board(); 
        std::cout << "PANG!! Game Over. Du träffade en mina! " << std::endl;

    } else if (status_ == GameStatus::WON) { 
        board_ptr_->print_board();
        std::cout << "GRATTIS! Du har vunnit Minröj-spelet! " << std::endl;

    } else if (status_ == GameStatus::QUITTED) {
        std::cout << "Spelet avbröts av spelaren. Välkommen åter! " << std::endl;
    }
    
}

void Game::start() {

    std::cout << "========================================" << std::endl;
    std::cout << "     Välkommen till Textbaserat Minröj!     " << std::endl;
    std::cout << "========================================" << std::endl;

    play_turn(); 
}