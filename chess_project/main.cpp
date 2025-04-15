#include "mainwindow.h"
#include "chessmodel.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Echequier echequier;
    MainWindow w;
    w.show();
    return a.exec();
}

