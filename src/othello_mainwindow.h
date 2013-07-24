/**
 * @author: Huxley
 **/

#ifndef OTHELLO_MAINWINDOW_H
#define OTHELLO_MAINWINDOW_H

#include <QAction>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include "board_layout.h"

class BoardLayout;

class OthelloMainWindow : public QMainWindow {
    Q_OBJECT
public:
    OthelloMainWindow(BoardLayout *layout, QWidget *parent = 0);
    ~OthelloMainWindow();

private:
    BoardLayout *layout_;
    QAction *gameRunAction_;
    QAction *exitGameAction_;
    QAction *aboutGameAction_;

private slots:
    void exit_game_slot();
    void about_game_slot();
};

#endif // OTHELLO_MAINWINDOW_H
