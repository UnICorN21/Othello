#ifndef HUMAN_H
#define HUMAN_H

#include <stdio.h>
#include "player.h"
class OthelloGame;

/**
  * Human player, only set clickable cell and emit a signal when a click is detected.
  **/
class Human : public Player
{
    Q_OBJECT
public:
    Human(bool black, OthelloGame * game);
    void play(OthelloGame * board);
};

#endif // HUMAN_H
