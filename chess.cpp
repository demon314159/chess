#include "chess.h"
#include "board.h"

#include <QtWidgets>

Chess::Chess()
    : board_(0)
    , light_tray_(0)
    , dark_tray_(0)
    , chess_set_(0)
{
    chess_set_ = new ChessSet();
    board_ = new Board(chess_set_, false, false, 8, 8, 80, this);
    light_tray_ = new Board(chess_set_, true, false, 1, 16, 40, this);
    dark_tray_ = new Board(chess_set_, true, true, 1, 16, 40, this);

    clear_button_ = new QPushButton("Clear");
    home_button_ = new QPushButton("Home");
    analyze_button_ = new QPushButton("Analyze");
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(light_tray_, 0, 0, 1, 1);
    mainLayout->addWidget(board_, 0, 1, 1, 8);
    mainLayout->addWidget(dark_tray_, 0, 9, 1, 1);
    mainLayout->addWidget(home_button_, 1, 0, 1, 2);
    mainLayout->addWidget(clear_button_, 1, 2, 1, 2);
    mainLayout->addWidget(analyze_button_, 1, 4, 1, 2);
    setLayout(mainLayout);
    setWindowTitle(tr("chess thing"));
    connect(clear_button_, SIGNAL(released()), this, SLOT (handle_clear_button()));
    connect(home_button_, SIGNAL(released()), this, SLOT (handle_home_button()));
    connect(analyze_button_, SIGNAL(released()), this, SLOT (handle_analyze_button()));
}

void Chess::update_all()
{
    board_->update();
    light_tray_->update();
    dark_tray_->update();
}

void Chess::handle_clear_button()
{
    if (chess_set_) {
        chess_set_->clear_position();
        update_all();
    }
}

void Chess::handle_home_button()
{
    if (chess_set_) {
        chess_set_->home_position();
        update_all();
    }
}

void Chess::handle_analyze_button()
{
    if (chess_set_) {
        int result = chess_set_->analyze();
        setWindowTitle(tr("Analyze result = %1").arg(result));
        update_all();
    }
}

