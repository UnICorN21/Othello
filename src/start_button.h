#ifndef STARTBUTTON_H
#define STARTBUTTON_H

#include "board_layout.h"

/**
  * Button used to start or restart the game.
  **/
class StartButton : public QPushButton
{
    Q_OBJECT
private:
    BoardLayout * layout_;
public:
    StartButton(BoardLayout * layout);
};

#endif // STARTBUTTON_H
