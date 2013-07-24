/**
 * @author: Huxley
 **/

#include "human.h"
#include "tools.hpp"
#include "othello_action.h"

/**
  * Human class constructor.
  * \param black True if player's color is black, false otherwise.
  * \param game A pointer to the game environment.
  **/
Human::Human(bool black, OthelloGame * game) : Player(black, game)
{
}

/**
  * Main player's function. Set all clickable moves. The selected action is then returned by cell signal if any.
  * Else the function emits a pass move.
  * \param game The game environment.
  **/
void Human::play(OthelloGame * game) {
    std::list<OthelloAction *> * allowed = game->getMoves();
    if(allowed->empty()) {
        delete allowed;
        emit pass(-1,-1);
    } else {
        game->setClickableMoves(allowed);
        Tools::deleteList(allowed);
        delete allowed;
    }
}
