#ifndef _BOARD_H_
#define _BOARD_H_

#include <QWidget>
#include <QMouseEvent>
#include "chess_set.h"

class Board: public QWidget
{
    Q_OBJECT

public:
    Board(ChessSet* chess_set, bool tray, bool dark, int cols, int rows, int spacing, QWidget *parent = 0);
    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;
private slots:
    void mousePressEvent(QMouseEvent *event);

protected:
    QWidget *parent_;
    ChessSet *chess_set_;
    bool tray_;
    bool dark_;
    int cols_;
    int rows_;
    int spacing_;
    QImage light_images_[6];
    QImage dark_images_[6];
    void paintEvent(QPaintEvent *event) override;
    void draw_image(QPainter &qp);
};
#endif
