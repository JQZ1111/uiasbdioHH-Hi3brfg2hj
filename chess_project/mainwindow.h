#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QWidget>
#include "chessmodel.h"


/*
 * Module pour la Vue et le Controlleur du modèle d'interface graphique
**/


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    Emplacement findPositionButton(QPushButton* buttonToFind);
    ~MainWindow();
public slots:
    //void deplacerPiece();
    void ajouterPiece(Emplacement emplacement, bool isBlack);
private:
    Ui::MainWindow *ui;
    QGridLayout* layout_;
    QWidget* centralWidget_;
    Echequier* echequierLogique_;
    QPushButton* buttons_[TAILLEECHEQUIER*TAILLEECHEQUIER];
    Emplacement emplacementPrecedent_;
    void makeCentralWidget();
};
#endif // MAINWINDOW_H

