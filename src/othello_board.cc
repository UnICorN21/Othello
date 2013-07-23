#include "ai_mobility.h"
#include "board_layout.h"
#include "human.h"
#include "othello_action.h"
#include "board_layout.h"

#define DIAG1 0x80
#define DIAG2 0x20
#define DIAG3 0x8
#define DIAG4 0x2
#define LINE1 0x40
#define LINE2 0x10
#define LINE3 0x4
#define LINE4 0x1

/**
  * OthelloBoard class constructor.
  **/
OthelloBoard::OthelloBoard() {
    board_ = new CellType[MAX_SIZE * MAX_SIZE];
}

/**
  * OthelloBoard class copy constructor.
  * \param board Reference to the board to copy.
  **/
OthelloBoard::OthelloBoard(OthelloBoard & board) {
    blackIsToPlay_ = board.blackIsToPlay_;
    pass_ = board.pass_;
    board_ = new CellType[MAX_SIZE * MAX_SIZE];
    memcpy(board_, board.board_, MAX_SIZE * MAX_SIZE * sizeof(CellType));
}

OthelloBoard::~OthelloBoard() {
    delete[] board_;
}

/**
  * Initiate the board. Memory must be already allocated.
  **/
void OthelloBoard::initiate() {
    blackIsToPlay_ = true;
    pass_ = false;
    for(int i = 0; i < MAX_SIZE; i++) {
        for(int j = 0; j < MAX_SIZE; j++) {
            board_[(i * MAX_SIZE) + j] = EMPTY;
        }
    }
    int midlow = (BOARD_SIZE / 2);
    int midhigh = (BOARD_SIZE / 2) + 1;
    board_[midhigh * MAX_SIZE + midhigh] = board_[midlow * MAX_SIZE + midlow] = BLACK;
    board_[midhigh * MAX_SIZE + midlow] = board_[midlow * MAX_SIZE + midhigh] = WHITE;
}

/**
  * Get the possible moves in the current configuration of the board.
  * \return A list of OthelloAction pointers representing the legal moves.
  **/
std::list<OthelloAction *> * OthelloBoard::getMoves() {
    using namespace std;
    list<OthelloAction *> * actions = new list<OthelloAction *>();
    CellType playerColor = (blackIsToPlay_) ? BLACK : WHITE;
    CellType opponentColor = (blackIsToPlay_) ? WHITE : BLACK;
    char directions;
    for(int i = 1; i <= BOARD_SIZE; i++) {
        for(int j = 1; j <= BOARD_SIZE; j++) {
            directions = canStartMove(i, j, playerColor, opponentColor);

            if(directions & DIAG1)
                getMovesInDiag(i, j, opponentColor, actions, true, true);
            if(directions & DIAG2)
                getMovesInDiag(i, j, opponentColor, actions, true, false);
            if(directions & DIAG3)
                getMovesInDiag(i, j, opponentColor, actions, false, false);
            if(directions & DIAG4)
                getMovesInDiag(i, j, opponentColor, actions, false, true);

            if(directions & LINE1)
                getMovesInCol(i, j, opponentColor, actions, true);
            if(directions & LINE2)
                getMovesInLine(i, j, opponentColor, actions, false);
            if(directions & LINE3)
                getMovesInCol(i, j, opponentColor, actions, false);
            if(directions & LINE4)
                getMovesInLine(i, j, opponentColor, actions, true);
        }
    }
    return actions;
}

/**
  * Return a mask of 8 bytes. Each bit is set to one if and only if the player can start a move in this position.
  * The first bit corresponds to the top left diagonal, and so on in clockwise.
  **/
char OthelloBoard::canStartMove(int i, int j, CellType player, CellType opponent) {
    char mask = 0x0;
    if(board_[i * MAX_SIZE + j] == player) {
        mask = (board_[(i-1) * MAX_SIZE + (j-1)] == opponent) ? (mask | 1) << 1 : mask << 1; // DIAG1
        mask = (board_[(i-1) * MAX_SIZE + j]   == opponent) ? (mask | 1) << 1 : mask << 1; // LINE1
        mask = (board_[(i-1) * MAX_SIZE + (j+1)] == opponent) ? (mask | 1) << 1 : mask << 1; // DIAG2
        mask = (board_[i * MAX_SIZE + (j+1)]   == opponent) ? (mask | 1) << 1 : mask << 1; // LINE2
        mask = (board_[(i+1) * MAX_SIZE + (j+1)] == opponent) ? (mask | 1) << 1 : mask << 1; // DIAG3
        mask = (board_[(i+1) * MAX_SIZE + j]   == opponent) ? (mask | 1) << 1 : mask << 1; // LINE3
        mask = (board_[(i+1) * MAX_SIZE + (j-1)] == opponent) ? (mask | 1) << 1 : mask << 1; // DIAG4
        if(board_[i * MAX_SIZE + (j-1)]   == opponent) mask = (mask | 1); // LINE4
    }
    return mask;
}

/**
  * Get possible move in line from a given position (X,Y). The direction is given by the left parameter.
  **/
void OthelloBoard::getMovesInLine(int X, int Y, CellType opponent, std::list<OthelloAction *> * &moves, bool left) {
    using namespace std;
    int k = left ? -1 : 1;
    int i = Y + k;
    int ilimit = left ? 1 : BOARD_SIZE;
    while(abs(i - ilimit) > 0 && board_[X * MAX_SIZE + i] == opponent){
        i += k;
    }
    if(abs(i - ilimit) >= 0 && abs(i - (Y + k)) > 0 && EMPTY == board_[X * MAX_SIZE + i]){
        moves->push_back(new OthelloAction(X, i));
    }
}

/**
  * Get possible move in column from a given position (X,Y). The direction is given by the top parameter.
  **/
void OthelloBoard::getMovesInCol(int X, int Y, CellType opponent, std::list<OthelloAction *> * &moves, bool top) {
    using namespace std;
    int k = top ? -1 : 1;
    int i = X + k;
    int ilimit = top ? 1 : BOARD_SIZE;
    while(abs(i - ilimit) > 0 && board_[i * MAX_SIZE + Y] == opponent){
        i += k;
    }
    if(abs(i - ilimit) >= 0 && abs(i - (X + k)) > 0 && EMPTY == board_[i * MAX_SIZE + Y]){
        moves->push_back(new OthelloAction(i, Y));
    }
}

/**
  * Get possible move in diagonal from a given position (X,Y). The direction is given by the left and top parameters.
  **/
void OthelloBoard::getMovesInDiag(int X, int Y, CellType opponent, std::list<OthelloAction *> * &moves, bool top, bool left) {
    using namespace std;
    int k, l;
    int ilimit, jlimit;
    k = top ? -1 : 1;
    ilimit = (top) ? 1 : BOARD_SIZE;
    l = left ? -1 : 1;
    jlimit = (left) ? 1 : BOARD_SIZE;

    bool done = false;
    int i = X + k;
    int j = Y + l;
    while(abs(j - jlimit) > 0 && abs(i - ilimit) > 0 && board_[i * MAX_SIZE + j] == opponent){
        i += k;
        j += l;
        done = true;
    }
    if(abs(j - jlimit) >= 0 && abs(i - ilimit) >= 0 && done && board_[i * MAX_SIZE + j] == EMPTY){
        moves->push_back(new OthelloAction(i, j));
    }
}

/**
  * Set the type of the cell at position (i,j) to \code{type}.
  * \param i Line position.
  * \param j Column position.
  * \param type New type of the cell.
  **/
void OthelloBoard::setCell(int i, int j, CellType type) {
    board_[i * MAX_SIZE + j] = type;
}

/**
  * Get the number of the cells of the type \code{type}.
  * \param type Type to count.
  **/
int OthelloBoard::getCount(CellType type) {
    int count = 0;
    for(int i = 1; i < BOARD_SIZE; i++) {
        for(int j = 1; j < BOARD_SIZE; j++) {
            if(board_[i * MAX_SIZE + j] == type)
                count++;
        }
    }
    return count;
}

/**
  * Change player.
  **/
void OthelloBoard::changePlayer() {
    blackIsToPlay_ = !blackIsToPlay_;
}
