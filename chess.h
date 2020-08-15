#ifndef CHESS_H
#define CHESS_H

#include <QtWidgets>
#include "chess_set.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Chess; }
QT_END_NAMESPACE
class Board;

class Chess : public QWidget
{
    Q_OBJECT

public:
    Chess();
    void update_all();

private slots:
    void handle_clear_button();
    void handle_home_button();
    void handle_analyze_button();

private:
    Board *board_;
    Board *light_tray_;
    Board *dark_tray_;
    ChessSet *chess_set_;
    QPushButton *clear_button_;
    QPushButton *home_button_;
    QPushButton *analyze_button_;
};
#endif // CHESS_H
