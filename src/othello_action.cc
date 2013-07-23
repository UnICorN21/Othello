#include "othello_action.h"
#include "tools.hpp"

/**
  * OthelloAction class constructor. Actions are represented by the position of the new disc.
  * \param i Line position.
  * \param j Column position.
  **/
OthelloAction::OthelloAction(int i, int j) : x_(i), y_(j) {
}

OthelloAction::~OthelloAction() {}

/**
  * Get line position.
  **/
int OthelloAction::getX() {
    return x_;
}

/**
  * Get column position.
  **/
int OthelloAction::getY() {
    return y_;
}

void OthelloAction::getChangesInLine(OthelloBoard * board, CellType opponent, std::list<OthelloAction *> * &actions) {
    getChangesInLineAux(board, opponent, actions, -1, 1);
    getChangesInLineAux(board, opponent, actions, 1, BOARD_SIZE);

}

/**
  * Get the changes in a line. The parameter k gives the direction.
  **/
void OthelloAction::getChangesInLineAux(OthelloBoard * board, CellType opponent, std::list<OthelloAction *> * &actions,
                                        int k, int ilimit) {
    using namespace std;
    int i = y_ + k;
    list<OthelloAction *> tmp = list<OthelloAction *>();
    while(abs(i - ilimit) > 0 && board->getBoard(x_,i) == opponent){
        tmp.push_front(new OthelloAction(x_, i));
        i += k;
    }
    // If the last cell is an opponent cell, actions in the list are to be applied.
    if (board->getBoard(x_, i) == (WHITE == opponent) ? BLACK : WHITE) {
        list<OthelloAction *>::iterator it = actions->begin();
        actions->splice(it, tmp);
    } else {
        Tools::deleteList(&tmp);
    }
}

void OthelloAction::getChangesInCol(OthelloBoard * board, CellType opponent, std::list<OthelloAction *> * &actions) {
    getChangesInColAux(board, opponent, actions, 1, BOARD_SIZE);
    getChangesInColAux(board, opponent, actions, -1, 1);
}

/**
  * Get the changes in a column. The parameter k gives the direction.
  **/
void OthelloAction::getChangesInColAux(OthelloBoard * board, CellType opponent, std::list<OthelloAction *> * &actions,
                                       int k, int ilimit) {
    int i = x_ + k;
    using namespace std;
    list<OthelloAction *>  tmp = list<OthelloAction *>();

    while(abs(i - ilimit) > 0 && board->getBoard(i,y_) == opponent){
        tmp.push_front(new OthelloAction(i, y_));
        i += k;
    }

    // If the last cell is an opponent cell, actions in the list are to be applied.
    if (board->getBoard(i, y_) == (WHITE == opponent) ? BLACK : WHITE) {
        list<OthelloAction *>::iterator it = actions->begin();
        actions->splice(it, tmp);
    } else {
        Tools::deleteList(&tmp);
    }
}

void OthelloAction::getChangesInDiag(OthelloBoard * board, CellType opponent, std::list<OthelloAction *> * &actions) {
    getChangesInDiagAux(board, opponent, actions, -1, -1, 1, 1);
    getChangesInDiagAux(board, opponent, actions, -1,  1, 1, BOARD_SIZE);
    getChangesInDiagAux(board, opponent, actions,  1, -1, BOARD_SIZE, 1);
    getChangesInDiagAux(board, opponent, actions, 1, 1, BOARD_SIZE, BOARD_SIZE);
}

/**
  * Get the changes in a diagonal. The parameters k and l give the direction of the diagonal.
  * ilimit and jlimit are to set the limits.
  **/
void OthelloAction::getChangesInDiagAux(OthelloBoard * board, CellType opponent, std::list<OthelloAction *> * &actions,
                                        int k, int l, int ilimit, int jlimit) {
    using namespace std;
    int i = x_ + k;
    int j = y_ + l;
    list<OthelloAction *> tmp = list<OthelloAction *>();
    while(abs(j - jlimit) > 0 && abs(i - ilimit) > 0 && board->getBoard(i, j) == opponent){
        tmp.push_front(new OthelloAction(i, j));
        i += k;
        j += l;
    }

    // If the last cell is an opponent cell, actions in the list are to be applied.
    if (board->getBoard(i, j) == (WHITE == opponent) ? BLACK : WHITE) {
        list<OthelloAction *>::iterator it = actions->begin();
        actions->splice(it, tmp);
    } else {
        Tools::deleteList(&tmp);
    }
}
/**
  * Apply an action on either the whole game, or only a given board.
  * \param game The object on which apply the action.
  **/
void OthelloAction::apply(BoardInterface * const & game) {
    using namespace std;
    OthelloGame * test = dynamic_cast<OthelloGame *>(game);
    OthelloBoard * board = (NULL == test) ? (OthelloBoard*) game : ((OthelloGame *)game)->getBoard();

    board->pass(false);
    CellType type = board->blackIsToPlay() ? BLACK : WHITE;
    CellType optype = board->blackIsToPlay() ? WHITE : BLACK;
    list<OthelloAction *> * actions = new list<OthelloAction *>();

    game->setCell(x_, y_, type);
    getChangesInLine(board, optype, actions);
    getChangesInCol(board, optype, actions);
    getChangesInDiag(board, optype, actions);
    while(!actions->empty()) {
        OthelloAction *action = actions->front();
        game->setCell(action->getX(), action->getY(), type);
        delete action;
        actions->pop_front();
    }
    delete actions;
}
