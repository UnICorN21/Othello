#include "othello_action.h"
#include "othello_search_node.h"
#include "tools.hpp"

/**
  * OthelloSearchNode class constructor.
  * \param level Depth of the new node. Root level is 0.
  * \param board State of the board for this node.
  **/
OthelloSearchNode::OthelloSearchNode(int level, OthelloBoard * board) :
    level_(level), utility_(0), action_(NULL), children_(NULL)
{
    board_ = new OthelloBoard(*board);
}

/**
  * OthelloSearchNode class constructor.
  * \param level Depth of the new node. Root level is 0.
  * \param board State of the board for this node.
  * \param action Action made to reach this state for the parent.
  **/
OthelloSearchNode::OthelloSearchNode(int level, OthelloBoard * board, OthelloAction * action) :
    level_(level), utility_(0), board_(board), action_(action), children_(NULL)
{
}

/**
  * OthelloSearchNode destructor.
  * Recursively delete the children of the node.
  **/
OthelloSearchNode::~OthelloSearchNode() {
    if(action_ != NULL) {
        delete action_;
    }
    delete board_;
    if(children_ != NULL) {
        Tools::deleteList(children_);
        delete children_;
    }
}

/**
  * Create the children of the node, corresponding to all possible moves from node board.
  * \return True if the node has been expand, false if no move was possible.
  **/
bool OthelloSearchNode::expandNode() {
    using namespace std;
    list<OthelloAction*> * moves = board_->getMoves();
    if(moves == NULL)
        return false;

    children_ = new list<OthelloSearchNode*>();
    for(list<OthelloAction*>::iterator it = moves->begin(); it != moves->end(); ++it) {
        OthelloBoard * p = new OthelloBoard(*board_);
        (*it)->apply(p);
        p->changePlayer();
        children_->push_front(new OthelloSearchNode(level_ + 1, p, *it));
    }
    delete moves;
    return true;
}

/**
  * Search in the children the one which has an utility equal to \code{utility}.
  * \return The corresponding node, or NULL if none.
  **/
OthelloAction * OthelloSearchNode::getActionFromUtility(int utility){
    using namespace std;
    OthelloAction * action = NULL;
    if(children_ != NULL) {
        for(list<OthelloSearchNode*>::iterator it = children_->begin(); it != children_->end(); ++it) {
            if((*it)->utility_ == utility){
                action = (*it)->action_;
            }
        }
    }
    return action;
}

void OthelloSearchNode::setUtility(int utility) {
    utility_ = utility;
}

std::list<OthelloSearchNode*> * OthelloSearchNode::getChilds() {
    return children_;
}
