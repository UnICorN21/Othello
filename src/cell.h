#ifndef CELL_H
#define CELL_H

#include <QLabel>
#include <QMouseEvent>
#include "board_layout.h"

class BoardLayout;

/**
  * This class represents all single cell of the graphic board.
  **/
class Cell : public QLabel
{
    Q_OBJECT
private :
    int x_;
    int y_;
    bool clickable_;
    BoardLayout * layout_;
    void mousePressEvent(QMouseEvent *event);
public:
    Cell(int i, int j, BoardLayout * layout);
    bool isClickable() { return clickable_;}
    void setClickable(bool clickable) { clickable_ = clickable;}

signals:
    void clicked(int,int);
};

#endif // CELL_H
