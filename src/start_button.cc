#include "start_button.h"

/**
  * Create a "start" button which starts or restarts the game when clicked.
  **/
StartButton::StartButton(BoardLayout *layout) : QPushButton("start"), layout_(layout)
{
    QObject::connect(this, SIGNAL(clicked()), layout_->getGame(), SLOT(start()));
}
