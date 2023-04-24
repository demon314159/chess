#include <QPainter>
#include "board.h"
#include "chess.h"

Board::Board(ChessSet *chess_set, bool tray, bool dark, int cols, int rows, int spacing, QWidget *parent)
    : parent_(parent)
    , chess_set_(chess_set)
    , tray_(tray)
    , dark_(dark)
    , cols_(cols)
    , rows_(rows)
    , spacing_(spacing)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    light_images_[PAWN].load(":/images/Chess_plt80.svg");
    light_images_[KNIGHT].load(":/images/Chess_nlt80.svg");
    light_images_[BISHOP].load(":/images/Chess_blt80.svg");
    light_images_[ROOK].load(":/images/Chess_rlt80.svg");
    light_images_[QUEEN].load(":/images/Chess_qlt80.svg");
    light_images_[KING].load(":/images/Chess_klt80.svg");
    dark_images_[PAWN].load(":/images/Chess_pdt80.svg");
    dark_images_[KNIGHT].load(":/images/Chess_ndt80.svg");
    dark_images_[BISHOP].load(":/images/Chess_bdt80.svg");
    dark_images_[ROOK].load(":/images/Chess_rdt80.svg");
    dark_images_[QUEEN].load(":/images/Chess_qdt80.svg");
    dark_images_[KING].load(":/images/Chess_kdt80.svg");
    for (int i = 0; i < 6; i++) {
        light_images_[i] = light_images_[i].scaled(spacing_, spacing_);
        dark_images_[i] = dark_images_[i].scaled(spacing_, spacing_);
    }
}

void Board::paintEvent(QPaintEvent *)
{
    QPainter qp(this);
    qp.save();
    draw_image(qp);
    qp.restore();
 }

void Board::draw_image(QPainter &qp)
{
    QColor light(240, 240, 220);
    QColor dark(210, 105, 30);
    QColor tray(192, 192, 192);
    QColor highlight(128, 128, 255);

    for (int i = 0; i < cols_; i++) {
        for (int j = 0; j < rows_; j++) {
            if (tray_) {
                qp.fillRect(i * spacing_, j * spacing_, spacing_, spacing_, tray);
            } else {
                if (((i ^ j) & 1) == 1) {
                    qp.fillRect(i * spacing_, j * spacing_, spacing_, spacing_, dark);
                } else {
                    qp.fillRect(i * spacing_, j * spacing_, spacing_, spacing_, light);
                }
            }
        }
    }
    Piece *np;
    int next_row = 0;
    for (int ix = 31; ix >= 0; ix--) {
        np = chess_set_->get_piece(ix);
        if (!np->get_dark()) {
            if (tray_) {
                if (!dark_ && !np->get_in_play()) {
                    np->move_to(0, next_row);
                    if (np->get_highlight()) {
                        qp.fillRect(np->get_col() * spacing_, (rows_ - 1 - np->get_row()) * spacing_, spacing_, spacing_, highlight);
                    }
                    qp.drawImage(0, spacing_ * (rows_ - 1 - next_row++), light_images_[np->get_kind()]);
                }
            } else {
                if (np->get_in_play()) {
                    if (np->get_highlight()) {
                        qp.fillRect(np->get_col() * spacing_, (rows_ - 1 - np->get_row()) * spacing_, spacing_, spacing_, highlight);
                    }
                    qp.drawImage(spacing_ * np->get_col(), spacing_ * (rows_ - 1 - np->get_row()), light_images_[np->get_kind()]);
                }
            }
        } else {
            if (tray_) {
                if (dark_ && !np->get_in_play()) {
                    np->move_to(0, next_row);
                    if (np->get_highlight()) {
                        qp.fillRect(np->get_col() * spacing_, (rows_ - 1 - np->get_row()) * spacing_, spacing_, spacing_, highlight);
                    }
                    qp.drawImage(0, spacing_ * (rows_ - 1 - next_row++), dark_images_[np->get_kind()]);
                }
            } else {
                if (np->get_in_play()) {
                    if (np->get_highlight()) {
                        qp.fillRect(np->get_col() * spacing_, (rows_ - 1 - np->get_row()) * spacing_, spacing_, spacing_, highlight);
                    }
                    qp.drawImage(spacing_ * np->get_col(), spacing_ * (rows_ - 1 - np->get_row()), dark_images_[np->get_kind()]);
                }
            }
        }
    }
}

QSize Board::minimumSizeHint() const
{
    return QSize(spacing_ * cols_, spacing_ * rows_);
}

QSize Board::sizeHint() const
{
    return QSize(spacing_ * cols_, spacing_ * rows_);
}

void Board::mousePressEvent(QMouseEvent *event)
{
    QString s;
    int hi_x = event->position().x() / spacing_;
    int hi_y = rows_ - 1 - (event->position().y() / spacing_);
    Piece *sel_piece;
    if (tray_) {
        if (dark_) {
            sel_piece = chess_set_->get_piece_in_dark_tray(hi_y);
        }
        else {
            sel_piece = chess_set_->get_piece_in_light_tray(hi_y);
        }
    }
    else {
        sel_piece = chess_set_->get_piece_in_play(hi_x, hi_y);
    }
    Piece *highlighted_piece = chess_set_->get_highlighted_piece();
    chess_set_->clear_highlights();

    if (highlighted_piece) {
        if (sel_piece) {
            if (tray_) {
                highlighted_piece->set_in_play(false);
                highlighted_piece->move_to(0, 0);
            }
        }
        else {
            if (tray_) {
                highlighted_piece->set_in_play(false);
                highlighted_piece->move_to(0, 0);
            }
            else {
                highlighted_piece->set_in_play(true);
                highlighted_piece->move_to(hi_x, hi_y);
            }
        }
    }
    else {
        if (sel_piece != 0) {
            sel_piece->set_highlight(true);
        }
    }
    if (parent_) {
        ((Chess*) parent_)->update_all();
    }
}
