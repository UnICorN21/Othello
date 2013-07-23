#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "othello_board.h"
#include "othello_search_node.h"
#include "player.h"

/**
  * Basic class of artificial intelligent player.
  * Action are chosen with alpha-beta algorithm, and players must implement \code{evaluate} to weight possible actions.
  **/
class AIPlayer : public Player
{
    Q_OBJECT
public:
    AIPlayer(bool black, OthelloGame * game);
    void play(OthelloGame *);
    virtual int evaluate(OthelloBoard * board) = 0;
    int alphaBeta(OthelloSearchNode * &node, int alpha, int beta, bool maximize);
};

#endif // AIPLAYER_H
