/**
 * @author: Huxley
 **/

#include "ai_mobility.h"
#include "human.h"
#include "othello_action.h"
#include "othello_game.h"

/**
  * OthelloGame class constructor.
  **/
OthelloGame::OthelloGame()
{
    layout_ = new BoardLayout(this);
    black_ = new Human(true, this);
    white_ = new AIMobility(false, this);
    board_ = new OthelloBoard();
}

/**
  * Initiate the game.
  * \param first Set to true if initialization must allocate memory.
  **/
void OthelloGame::initiate(bool first) {
    board_->initiate();
    layout_->initiate(first);
    layout_->updateLCD();
}

/**
  * Get the layout.
  **/
QLayout * OthelloGame::getLayout() {
    return layout_;
}

/**
  * Get possible moves in the current state of the game.
  * \return A list of pointers of the possible OthelloAction.
  **/
std::list<OthelloAction *> * OthelloGame::getMoves() {
    return board_->getMoves();
}

/**
  * Set the cell to the type \code{code}. Change are made both in the board and the layout.
  * \param i Line position.
  * \param j Column position.
  * \param type The new type of the cell.
  **/
void OthelloGame::setCell(int i, int j, CellType type) {
    board_->setCell(i, j, type);
    layout_->changeCellType(i, j, type);
}

/**
  * Make the current player plays.
  **/
void OthelloGame::play() {
    board_->blackIsToPlay() ? black_->play(this) : white_->play(this);
}

/**
  * Start or restart the game, i.e initiate the board and make the first player begin.
  * \param first Set to true if this is the first game.
  **/
void OthelloGame::start(bool first) {
    initiate(first);
    play();
}

/**
  * Set the cells corresponding to the OthelloAction given in the list as clickable cells.
  * \param allowed List of pointers of OthelloAction.
  **/
void OthelloGame::setClickableMoves(std::list<OthelloAction *> * &allowed ) {
    using namespace std;

    for(list<OthelloAction*>::iterator it = allowed->begin(); it != allowed->end(); ++it) {
        layout_->setCellClickable((*it)->getX(), (*it)->getY());
    }
}

/**
  * Set the whole board unclickable.
  **/
void OthelloGame::setUnclickable() {
    layout_->setUnclickable();
}

/**
  * \return OthelloBoard to the board.
  **/
OthelloBoard * OthelloGame::getBoard() {
    return board_;
}

/**
  * Test whether the end is reached.
  * \return True if the end is reached, false otherwise.
  **/
bool OthelloGame::isThatTheEnd() {
    if(board_->pass()) {
        return true;
    } else {
        board_->pass(true);
        return false;
    }
}

/**
  * Count the number of cells of each color and make the layout announce the winner.
  **/
void OthelloGame::theEnd() {
    int black = board_->getCount(BLACK);
    int white = board_->getCount(WHITE);
    layout_->win(black - white);
}

/**
  * Change the player and make the new current player play.
  **/
void OthelloGame::nextTurn() {
    board_->changePlayer();
    play();
}

/**
  * Play the given action.
  * If x and y are equal to -1, this is a pass move.
  * \param x Line position of the disc to play.
  * \param y Column position of the disc to play.
  **/
void OthelloGame::playAction(int x,int y) {
    if(x == -1 && y == -1) {
        if(isThatTheEnd()) {
            theEnd();
        } else {
            nextTurn();
        }
    } else {
        OthelloAction action = OthelloAction(x,y);
        setUnclickable();
        action.apply(this);
        nextTurn();
    }
    layout_->updateLCD();
}
