#include "chess.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Chess chess;
    chess.show();
    return app.exec();
}
