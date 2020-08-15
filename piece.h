//
// piece.h
//
#if !defined(_PIECE_H_)
#define _PIECE_H_
//
// Choices for KIND parameter
//
#define KING 5
#define QUEEN 4
#define ROOK 3
#define BISHOP 2
#define KNIGHT 1
#define PAWN 0
//
// RANK and FILE are 0 .. 7
//
class Piece
{
public:
    Piece(int kind, bool dark, int home_col, int home_row);
    bool get_in_play();
    int get_kind();
    bool get_dark();
    bool get_highlight();
    int get_col();
    int get_row();
    void set_in_play(bool v);
    void set_highlight(bool v);
    void move_to_home();
    void move_to(int col, int row);
    void promote_to(int kind);
private:
    bool in_play_;
    int kind_;
    bool dark_;
    bool highlight_;
    int home_col_;
    int home_row_;
    int col_;
    int row_;
};

#endif // _PIECE_H_
