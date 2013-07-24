/**
 * @author: Huxley
 **/

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <QObject>
#include "defines.h"

class OthelloGame;
class OthelloAction;

/**
  * Basic player class. Each player must implement the \code{play} function, which describe actions played at each turn.
  **/
class Player : public QObject
{
    Q_OBJECT
protected:
    bool isBlack_;
    OthelloGame *game_;
public:
    Player(bool black, OthelloGame *game) : isBlack_(black), game_(game) {
        QObject::connect(this, SIGNAL(pass(int,int)), (QObject *) game_, SLOT(playAction(int,int)));
    }
    virtual void play(OthelloGame*) = 0;
signals:
    void pass(int,int);
};

#endif // PLAYER_H
