/**
 * @author: Huxley
 **/

#include "start_button.h"

/**
  * Create a "start" button which starts or restarts the game when clicked.
  **/
StartButton::StartButton(BoardLayout *layout) : QPushButton("start"), layout_(layout)
{
    setObjectName("startButton");
        setStyleSheet(
                    "QPushButton#startButton{background-color:rgb(238, 238, 238); color:black; border-radius:10px; border: 2px groove gray; border-style:outset}"
                    "QPushButton:hover#startButton{background-color:white; color:black;}"
                    "QPushButton:pressed#startButton{background-color:rgb(85, 170, 255); border-style:inset}"
                    );
    setFixedSize(100, 50);
    QObject::connect(this, SIGNAL(clicked()), layout_->getGame(), SLOT(start()));
}
