#include "Game.h"
#include <iostream>
#include <memory> 
#include <limits>

int main() {
    
    const int ROWS = 6;
    const int COLS = 6;
    const int MINES = 6;
    
    std::cout << "Startar Minröj: " << std::endl;

    std::unique_ptr<Game> game_ptr = std::make_unique<Game>(ROWS, COLS, MINES);

    game_ptr->start();
    
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "\nSpelet avslutat. " << std::endl;

    return 0;
}

