#ifndef OTHELLOACTION_H
#define OTHELLOACTION_H

#include "board_interface.h"
#include "defines.h"
#include "othello_game.h"

class OthelloBoard;

/**
  * OthelloAction are represented by their coordinates.
  * (-1, -1) is a pass move.
  **/
class OthelloAction {
private :
    int x_;
    int y_;

public:
	OthelloAction(int i, int j);
	~OthelloAction();
	int getX();
    int getY();
    void apply(BoardInterface * const &);
private:
    void getChangesInLine(OthelloBoard * board, CellType opponent, std::list<OthelloAction *> * &actions);
    void getChangesInCol(OthelloBoard * board, CellType opponent, std::list<OthelloAction *> * &actions);
    void getChangesInDiag(OthelloBoard * board, CellType opponent, std::list<OthelloAction *> * &actions);
    void getChangesInDiagAux(OthelloBoard *, CellType, std::list<OthelloAction *> * &, int, int, int, int);
    void getChangesInLineAux(OthelloBoard *, CellType, std::list<OthelloAction *> * &, int , int);
    void getChangesInColAux(OthelloBoard *, CellType, std::list<OthelloAction *> * &, int , int);
};

#endif /* OTHELLOACTION_H_ */
