#ifndef OTHELLOSEARCHNODE_H
#define OTHELLOSEARCHNODE_H

#include "othello_board.h"

class OthelloAction;

/**
  * Piece of the search tree used for forecasting and action selection.
  **/
class OthelloSearchNode
{
private:
    int level_;
    int utility_;
    OthelloBoard * board_;
    OthelloAction * action_;
    std::list<OthelloSearchNode*> * children_;
public:
    OthelloSearchNode(int level, OthelloBoard *board);
    OthelloSearchNode(int level, OthelloBoard *board, OthelloAction *action);
    ~OthelloSearchNode();
    bool expandNode();
    void setUtility(int utility);
    std::list<OthelloSearchNode*> * getChilds();
    OthelloAction * getActionFromUtility(int utility);
    int getLevel() { return level_; }
    int getUtility() { return utility_; }
    OthelloBoard * getBoard() { return board_;}
};

#endif // OTHELLOSEARCHNODE_H
