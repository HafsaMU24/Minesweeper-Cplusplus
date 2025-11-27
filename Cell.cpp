#include "Cell.h"
#include <iostream>

Cell::Cell() : 
    has_mine(false), 
    is_revealed(false), 
    is_flagged(false), 
    adjacent_mines(0) {
}

void Cell::reset() {
    has_mine = false;
    is_revealed = false;
    is_flagged = false;
    adjacent_mines = 0;
}

char Cell::get_display_char() const {
    if (!is_revealed) {
        if (is_flagged) {
            return 'F'; 
        } else {
            return ' '; 
        }
    } else {
        if (has_mine) {
            return 'X'; 
        } else if (adjacent_mines > 0) {
            return static_cast<char>('0' + adjacent_mines); 
        } else {
            return 'O'; 
        }
    }
}