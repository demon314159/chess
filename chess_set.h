//
// chess_set.h
//
#if !defined(CHESS_SET_H_)
#define CHESS_SET_H_

#include "piece.h"

class ChessSet
{
public:
    ChessSet();
    ~ChessSet();
    void clear_highlights();
    void clear_position();
    void home_position();
    Piece *get_highlighted_piece();
    Piece *get_piece_in_play(int col, int row);
    Piece *get_piece_in_light_tray(int row);
    Piece *get_piece_in_dark_tray(int row);
    Piece *get_piece(int ix);
    int analyze();
private:
    Piece *pieces_[32];
    Piece *map_[8][8];

    void clear_map();
    void build_map();
};

#endif // CHESS_SET_H_
