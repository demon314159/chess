//
// chess_set.cpp
//
#include "chess_set.h"

ChessSet::ChessSet()
{
    int ix = 0;
    pieces_[ix++] = new Piece(KING, false, 4, 0);
    pieces_[ix++] = new Piece(QUEEN, false, 3, 0);
    pieces_[ix++] = new Piece(ROOK, false, 0, 0);
    pieces_[ix++] = new Piece(ROOK, false, 7, 0);
    pieces_[ix++] = new Piece(BISHOP, false, 2, 0);
    pieces_[ix++] = new Piece(BISHOP, false, 5, 0);
    pieces_[ix++] = new Piece(KNIGHT, false, 1, 0);
    pieces_[ix++] = new Piece(KNIGHT, false, 6, 0);
    for (int i = 0; i < 8; i++) {
        pieces_[ix++] = new Piece(PAWN, false, i, 1);
    }
    pieces_[ix++] = new Piece(KING, true, 4, 7);
    pieces_[ix++] = new Piece(QUEEN, true, 3, 7);
    pieces_[ix++] = new Piece(ROOK, true, 0, 7);
    pieces_[ix++] = new Piece(ROOK, true, 7, 7);
    pieces_[ix++] = new Piece(BISHOP, true, 2, 7);
    pieces_[ix++] = new Piece(BISHOP, true, 5, 7);
    pieces_[ix++] = new Piece(KNIGHT, true, 1, 7);
    pieces_[ix++] = new Piece(KNIGHT, true, 6, 7);
    for (int i = 0; i < 8; i++) {
        pieces_[ix++] = new Piece(PAWN, true, i, 6);
    }
    clear_map();
}

ChessSet::~ChessSet()
{
    for (int ix = 0; ix < 32; ix++) {
        delete pieces_[ix];
        pieces_[ix] = 0;
    }
}

void ChessSet::clear_highlights()
{
    for (int ix = 0; ix < 32; ix++) {
        pieces_[ix]->set_highlight(false);
    }
}

void ChessSet::clear_position()
{
    for (int ix = 0; ix < 32; ix++) {
        pieces_[ix]->move_to(0, 0);
        pieces_[ix]->set_in_play(false);
        pieces_[ix]->set_highlight(false);
    }
}

void ChessSet::home_position()
{
    for (int ix = 0; ix < 32; ix++) {
        pieces_[ix]->move_to_home();
        pieces_[ix]->set_in_play(true);
        pieces_[ix]->set_highlight(false);
    }
}

Piece *ChessSet::get_highlighted_piece()
{
    for (int ix = 0; ix < 32; ix++) {
        if (pieces_[ix]->get_highlight()) {
            return pieces_[ix];
        }
    }
    return 0;
}

Piece *ChessSet::get_piece_in_play(int col, int row)
{
    Piece *piece;
    for (int ix = 0; ix < 32; ix++) {
        piece = pieces_[ix];
        if (piece->get_in_play()) {
            if (piece->get_col() == col && piece->get_row() == row) {
                return piece;
            }
        }
    }
    return 0;
}

Piece *ChessSet::get_piece_in_light_tray(int row)
{
    Piece *piece;
    for (int ix = 0; ix < 32; ix++) {
        piece = pieces_[ix];
        if (!piece->get_in_play() && !piece->get_dark()) {
            if (piece->get_row() == row) {
                return piece;
            }
        }
    }
    return 0;
}

Piece *ChessSet::get_piece_in_dark_tray(int row)
{
    Piece *piece;
    for (int ix = 0; ix < 32; ix++) {
        piece = pieces_[ix];
        if (!piece->get_in_play() && piece->get_dark()) {
            if (piece->get_row() == row) {
                return piece;
            }
        }
    }
    return 0;
}

Piece *ChessSet::get_piece(int ix)
{
    return pieces_[ix];
}

void ChessSet::clear_map()
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            map_[i][j] = 0;
        }
    }
}

void ChessSet::build_map()
{
    clear_map();
    for (int ix = 0; ix < 32; ix++) {
        Piece *piece = pieces_[ix];
        if (piece->get_in_play()) {
            map_[piece->get_col()][piece->get_row()] = piece;
        }
    }
}

int ChessSet::analyze()
{
    build_map();
    return 3;
}
