/**
 * @author: Huxley
 **/

#include <QList>
#include <QMessageBox>
#include "othello_mainwindow.h"

/**
 * OthelloMainWindow class constructor.
 * \param layout: A pointer to the current game layout.
 * \param parent
 */
OthelloMainWindow::OthelloMainWindow(BoardLayout *layout, QWidget *parent) : QMainWindow(parent), layout_(layout) {
    setObjectName("OthelloMain");
    setStyleSheet("QMainWindow#OthelloMain{border-image:url(./img/background.jpg)}");

    gameRunAction_ = new QAction(tr("New Game"), this);
    exitGameAction_ = new QAction(tr("Exit"), this);
    aboutGameAction_ = new QAction(tr("About"), this);

    connect(gameRunAction_, SIGNAL(triggered()), layout_->getGame(), SLOT(start()));
    connect(exitGameAction_, SIGNAL(triggered()), this, SLOT(exit_game_slot()));
    connect(aboutGameAction_, SIGNAL(triggered()), this, SLOT(about_game_slot()));

    QList<QAction*> _actionList;
    _actionList.push_back(gameRunAction_);
    _actionList.push_back(exitGameAction_);
    menuBar()->addMenu(tr("Game"))->addActions(_actionList);
    menuBar()->addMenu(tr("Help"))->addAction(aboutGameAction_);
}
/**
 * OthelloMainWindow class destructor.
 */
OthelloMainWindow::~OthelloMainWindow(){
    delete layout_;
    delete gameRunAction_;
    delete exitGameAction_;
    delete aboutGameAction_;
}

/**
 * This function defines what the program will do if the client click exit menu.
 */
void OthelloMainWindow::exit_game_slot(){
    exit(0);
}

/**
 * This function defines what the program will do if the client click about menu.
 */
void OthelloMainWindow::about_game_slot(){
    QMessageBox::about(0, tr("About"), tr("\tWritten by Huxley\nAI implement with alpha-beta algorithm."));
}
