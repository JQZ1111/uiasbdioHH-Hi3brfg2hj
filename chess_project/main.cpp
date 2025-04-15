#include "mainwindow.h"
#include "chessmodel.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Echequier echequier;
    MainWindow w;
    echequier.ajouterPiece({'a', 4}, true);
    w.show();
    return a.exec();
}

