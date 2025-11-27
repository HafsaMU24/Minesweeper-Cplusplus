#ifndef GAME_H
#define GAME_H

#include "MinesweeperBoard.h"

#include <iostream>
#include <string>
#include <memory> 


enum class GameStatus {
    PLAYING,      
    WON,          
    LOST,
    QUITTED        
};

class Game {
public:
    
    Game(int rows, int cols, int num_mines);
    
    void start();

private:
    GameStatus status_;
    
    std::unique_ptr<MinesweeperBoard> board_ptr_; 

    void play_turn(); 
    void handle_reveal_action(int r, int c);
    
    bool parse_input(const std::string& input, int& r, int& c, char& action);
    
    char to_lower(char c) const {
        if (c >= 'A' && c <= 'Z') {
            return c + ('a' - 'A');
        }
        return c;
    }
    
    bool is_alpha(char c) const {
        char lc = to_lower(c);
        return lc >= 'a' && lc <= 'z';
    }
    
    bool is_digit(char c) const {
        return c >= '0' && c <= '9';
    }
};

#endif