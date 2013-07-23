#ifndef OTHELLOBOARD_H_
#define OTHELLOBOARD_H_

#include <stdlib.h>
#include <stdio.h>
#include <list>
#include <iostream>
#include <QGridLayout>
#include "board_interface.h"
#include "defines.h"
#include "player.h"

class BoardLayout;
class OthelloAction;

/**
  * Intern representation of game board.
  **/
class OthelloBoard : public BoardInterface {
private:
    CellType * board_;
    bool blackIsToPlay_;
    bool pass_;
    char canStartMove(int i, int j, CellType player, CellType opponent);
    void getMovesInLine(int i, int j, CellType, std::list<OthelloAction *> * &moves, bool);
    void getMovesInCol(int i, int j, CellType, std::list<OthelloAction *> * &moves, bool);
    void getMovesInDiag(int i, int j, CellType, std::list<OthelloAction *> * &moves, bool, bool);
public:
	OthelloBoard();
    OthelloBoard(OthelloBoard &board);
	~OthelloBoard();
    std::list<OthelloAction *> * getMoves();
    int getCount(CellType type);
    void initiate();
    void changePlayer();
    OthelloBoard * getBoard() { return this; }
    void setCell(int i, int j, CellType type);
    bool blackIsToPlay() { return blackIsToPlay_; }
    CellType getBoard(int i, int j) { return board_[i * MAX_SIZE + j]; }
    void pass(bool b) { pass_ = b; }
    bool pass() {return pass_; }
};

#endif /* OTHELLOBOARD_H_ */
