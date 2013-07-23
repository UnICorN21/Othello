#include <QApplication>
#include <QLabel>
#include <QMainWindow>
#include "defines.h"
#include "othello_game.h"

int main(int argc, char *argv[]) {
    QApplication * app = new QApplication(argc, argv);
    QMainWindow * w = new QMainWindow();
    OthelloGame * game = new OthelloGame();
    QLabel * central = new QLabel();
    central->setMinimumSize(BOARD_SIZE * 50 + 150, BOARD_SIZE * 50);
    central->setMaximumSize(BOARD_SIZE * 50 + 150, BOARD_SIZE * 50);
    central->setLayout(game->getLayout());
    game->initiate(true);
    w->setCentralWidget(central);
    w->show();

    return app->exec();
}
