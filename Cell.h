#ifndef CELL_H
#define CELL_H


class Cell {
public:
    Cell();

    bool has_mine;
    bool is_revealed;
    bool is_flagged;
    int adjacent_mines; 

    void reset();
    char get_display_char() const;
};

#endif 
