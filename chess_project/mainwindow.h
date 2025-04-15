#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QWidget>
#include <QComboBox>
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
    void deplacerPiece();
    void ajouterPiece();
    void setHorizontalPosition(int horizontalPos);
    void setVerticalPosition(int verticalPos);
    void setNoirOuBlanc(int noirOuBlanc);
    void setTypePieceAjouter(int pieceTypeIndex);
private:
    Ui::MainWindow *ui;
    QGridLayout* layout_;
    QWidget* centralWidget_;
    Game* game_;
    QPushButton* buttons_[TAILLEECHEQUIER*TAILLEECHEQUIER];
    QPushButton* addPieceButton_;
    QComboBox* comboBoxVertical_;
    QComboBox* comboBoxHorizontal_;
    QComboBox* comboBoxNoirOuBlanc_;
    QComboBox* comboBoxPiecesSelection_;
    Emplacement emplacementPrecedent_;
    char pieceHorizontalPos_;
    int pieceVerticalPos_;
    bool noirOuPas_;
    std::string typePieceAjouter_;
    void makeCentralWidget();
    void makeComboBox();
signals:
    void pieceAjouter(std::string pieceType, Emplacement emplacement, bool isBlack);
};
#endif // MAINWINDOW_H

