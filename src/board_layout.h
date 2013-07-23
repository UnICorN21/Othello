#ifndef BOARDLAYOUT_H
#define BOARDLAYOUT_H

#include <QGridLayout>
#include <QLCDNumber>
#include <QMainWindow>
#include <QPushButton>
#include "cell.h"
#include "defines.h"
#include "othello_action.h"
#include "othello_board.h"
#include "start_button.h"

#define WHITE_CELL "img/white.png"
#define BLACK_CELL "img/black.png"
#define EMPTY_CELL "img/empty.png"
#define ALLOWED_CELL "img/allowed.png"

class OthelloBoard;

/**
  * This class handles the graphical implementation of the game.
  **/
class BoardLayout : public QGridLayout
{
    Q_OBJECT
private:
    QPixmap black_;
    QPixmap white_;
    QPixmap empty_;
    QPixmap allowed_;
    OthelloGame *game_;
    QLCDNumber *blackCountLcd_;
    QLCDNumber *whiteCountLcd_;

public:
    explicit BoardLayout(OthelloGame * const &game, QWidget * = 0);
    void initiate(bool first);
    void playAction(int i, int j);
    void changeCellType(int i, int j, CellType type);
    void setCellClickable(int i, int j);
    void setUnclickable();
    void setAllowed();
    void start();
    OthelloGame * getGame() {return game_; }
    void win(int score);
};

#endif // BOARDLAYOUT_H
