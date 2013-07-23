#include "cell.h"

/**
  * Cell constructor. Connect clicked signal with \code{OthelloGame::playAction(int, int)}.
  * The cell is unclickable by default.
  * \param i Line position.
  * \param j Column position.
  * \param layout The layout to which the cell belongs.
  **/
Cell::Cell(int i, int j, BoardLayout * layout) : QLabel(), x_(i), y_(j), layout_(layout)
{
    installEventFilter(this);
    QObject::connect(this, SIGNAL(clicked(int,int)), (QObject*) layout_->getGame(), SLOT(playAction(int,int)));
    clickable_ = false;
}

/**
  * Describe the cell behaviour on click.
  **/
void Cell::mousePressEvent(QMouseEvent *event)
{
    // If left button is clicked.
    if (event->button() == Qt::LeftButton)
    {
        if(clickable_) {
            emit clicked(x_,y_);
        } else {
            layout_->setAllowed();
        }
    }
}
