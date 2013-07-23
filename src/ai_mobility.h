#ifndef AIMOBILITY_H
#define AIMOBILITY_H

#include "ai_player.h"

/**
  * Artificial intelligent player based on mobility (possible moves),
  * stability (number of dics which can't be retaken) and number of dics of each color.
  **/
class AIMobility : public AIPlayer
{
public:
    AIMobility(bool black, OthelloGame *game);
    int evaluate(OthelloBoard * board);
private:
    int getNumberOfStableDisc(OthelloBoard * board, CellType player);
    int getStableFromEdge(OthelloBoard * board, CellType player, int border, bool isHorizontal);
    bool isBorderFull(OthelloBoard * board, int border,	bool isHorizontal);
    int getStableFromCorner(OthelloBoard * board, CellType player,	int cRowIndex, int cColumnIndex);
};

#endif // AIMOBILITY_H

