#ifndef OTHELLOGAME_H
#define OTHELLOGAME_H

#include <QObject>
#include "board_layout.h"
#include "board_interface.h"
#include "defines.h"
#include "player.h"
#include "othello_board.h"

/**
  * Game master class.
  **/
class OthelloGame : public QObject, public BoardInterface
{
    Q_OBJECT
private:
    BoardLayout * layout_;
    OthelloBoard * board_;
    Player * white_;
    Player * black_;
    bool isThatTheEnd();
    void theEnd();
    void nextTurn();
    void play();
public:
    OthelloGame();
    QLayout * getLayout();
    void setCell(int i, int j, CellType type);
    CellType getBoard(int i, int j);
    OthelloBoard * getBoard();
    void setClickableMoves(std::list<OthelloAction*> *&allowed);
    void setUnclickable();
    void initiate(bool first);
    void changePlayer();
    std::list<OthelloAction *> * getMoves();

public slots :
    void playAction(int x, int y);
    void start(bool = false);
};

#endif // OTHELLOGAME_H
