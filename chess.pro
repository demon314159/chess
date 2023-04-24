
TEMPLATE = app
TARGET = chess

QT += widgets
QT += svg

HEADERS += \
    chess.h \
    board.h \
    piece.h \
    chess_set.h

SOURCES += \
    main.cpp \
    chess.cpp \
    board.cpp \
    piece.cpp \
    chess_set.cpp

RESOURCES += \
    chess.qrc

