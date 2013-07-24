/**
 * @author: Huxley
 **/

#include <QApplication>
#include <QLabel>
#include "othello_mainwindow.h"
#include "defines.h"
#include "othello_game.h"

int main(int argc, char *argv[]) {
    QApplication *app = new QApplication(argc, argv);
    OthelloGame *game = new OthelloGame();
    OthelloMainWindow *w = new OthelloMainWindow((BoardLayout*)game->getLayout());
    QLabel *central = new QLabel();
    central->setMinimumSize(kBoardSize * 50 + 150, kBoardSize * 50);
    central->setMaximumSize(kBoardSize * 50 + 150, kBoardSize * 50);
    central->setLayout(game->getLayout());
    game->initiate(true);
    w->setCentralWidget(central);
    w->show();

    return app->exec();
}
