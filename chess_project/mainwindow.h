#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QWidget>

/*
 * Module pour la Vue et le Controlleur du modèle d'interface graphique
**/

int const TAILLEECHEQUIER = 8;

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
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGridLayout* layout_;
    QWidget* echequier_;
    QPushButton* buttons_[TAILLEECHEQUIER*TAILLEECHEQUIER];
};
#endif // MAINWINDOW_H

