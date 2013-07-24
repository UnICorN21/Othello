/**
 * @author: Huxley
 **/

#include "ai_player.h"
#include "defines.h"
#include "othello_action.h"
#include "othello_search_node.h"

/**
  * AIPlayer class constructor.
  * \param black True if player's color is black, false otherwise.
  * \param game A pointer to the game environment.
  **/
AIPlayer::AIPlayer(bool black, OthelloGame *game) : Player(black, game)
{
}

/**
  * Main player's function. Relay the action to play by emitting a signal.
  * \param game The game environment.
  **/
void AIPlayer::play(OthelloGame * game) {
    OthelloSearchNode * head = new OthelloSearchNode(0, game->getBoard());
    int score = alphaBeta(head, -kInf, kInf, true);
    OthelloAction * bestAction = head->getActionFromUtility(score);
    if(bestAction == NULL) {
        delete head;
        emit pass(-1,-1);
    } else {
        int x = bestAction->getX();
        int y = bestAction->getY();
        delete head;
        emit pass(x, y);
    }
}

/**
  * Determine the weight of each action, in a depth of \code{DEPTH}, using the alphabeta algorithm.
  * \param node The node to evaluate.
  * \param alpha
  * \param beta
  * \param maximise True if node is maximizing node, false otherwise.
  **/
int AIPlayer::alphaBeta(OthelloSearchNode * &node, int alpha, int beta, bool maximize){
    if(node->getLevel() == kDepth){
        int utility = evaluate(node->getBoard());
        return utility;
    }
    int value;
    using namespace std;
    if(maximize){
        value = -kInf;
        if(!node->expandNode()) {
            int utility = evaluate(node->getBoard());
            node->setUtility(utility);
            return utility;
        }
        list<OthelloSearchNode*> * children= node->getChilds();
        for(list<OthelloSearchNode*>::iterator it = children->begin(); it != children->end(); ++it) {
            value = std::max(value, alphaBeta(*it, alpha, beta, !maximize));
            if(value >= beta){
                node->setUtility(value);
                return value;
            }
            alpha = max(alpha, value);
        }
    } else{
        value = kInf;
        if(!node->expandNode()) {
            int utility = evaluate(node->getBoard());
            node->setUtility(utility);
            return utility;
        }
        list<OthelloSearchNode*> * children = node->getChilds();
        for(list<OthelloSearchNode*>::iterator it = children->begin(); it != children->end(); ++it) {
            value = std::min(value, alphaBeta(*it, alpha, beta, !maximize));
            if(alpha >= value){
                node->setUtility(value);
                return value;
            }
            beta = min(beta, value);
        }
    }
    node->setUtility(value);
    return value;
}
