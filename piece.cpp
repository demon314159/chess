//
// piece.cpp
//
#include "piece.h"

Piece::Piece(int kind, bool dark, int home_col, int home_row)
    : in_play_(true)
    , kind_(kind)
    , dark_(dark)
    , highlight_(false)
    , home_col_(home_col)
    , home_row_(home_row)
    , col_(home_col)
    , row_(home_row)
{
}

bool Piece::get_in_play()
{
    return in_play_;
}

int Piece::get_kind()
{
    return kind_;
}

bool Piece::get_dark()
{
    return dark_;
}

bool Piece::get_highlight()
{
    return highlight_;
}

int Piece::get_col()
{
    return col_;
}

int Piece::get_row()
{
    return row_;
}

void Piece::set_in_play(bool v)
{
    in_play_ = v;
}

void Piece::set_highlight(bool v)
{
    highlight_ = v;
}

void Piece::move_to_home()
{
    col_ = home_col_;
    row_ = home_row_;
}

void Piece::move_to(int col, int row)
{
    col_ = col;
    row_ = row;
}

void Piece::promote_to(int kind)
{
    kind_ = kind;
}

