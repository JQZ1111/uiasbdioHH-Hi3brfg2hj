#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , echequierLogique_()
{
    ui->setupUi(this);
    makeCentralWidget();
    QObject::connect(echequierLogique_, SIGNAL(ajoutDUnePiece(Emplacement,bool)), this, SLOT(ajouterPiece(Emplacement,bool)));
    echequierLogique_->ajouterPiece({'a', 5}, true);
    // Cant center it tho
}

void MainWindow::makeCentralWidget(){
    layout_ = new QGridLayout();
    layout_->setSpacing(0);
    layout_->setContentsMargins(0, 0, 0, 0);
    echequierLogique_ = new Echequier;
    centralWidget_ = new QWidget();
    for(int i = 0; i < TAILLEECHEQUIER; i++){
        for(int j = 0; j<TAILLEECHEQUIER; j++){
            buttons_[(i*TAILLEECHEQUIER)+j] = new QPushButton();
            buttons_[(i*TAILLEECHEQUIER)+j]->setFixedHeight(40);
            buttons_[(i*TAILLEECHEQUIER)+j]->setFixedWidth(40);
            if ((i+j)%2 == 1){
                buttons_[(i*TAILLEECHEQUIER)+j]->setStyleSheet("background-color:yellow;");
            }
            else buttons_[(i*TAILLEECHEQUIER)+j]->setStyleSheet("background-color:brown;");
            layout_->addWidget(buttons_[(i*TAILLEECHEQUIER)+j], i, j);
        }
    }
    centralWidget_->setLayout(layout_);
    centralWidget_->setMaximumHeight(40*TAILLEECHEQUIER);
    centralWidget_->setMaximumWidth(40*TAILLEECHEQUIER);
    setCentralWidget(centralWidget_);
}

Emplacement MainWindow::findPositionButton(QPushButton* buttonToFind){
    for(unsigned long long i = 0; i<TAILLEECHEQUIER*TAILLEECHEQUIER; i++){
        if(buttons_[i] == buttonToFind){
            char horizontalPos = char(i%TAILLEECHEQUIER + int('a'));
            int verticalPos = i/TAILLEECHEQUIER;
            return {horizontalPos, verticalPos};
        }
    }
    return {'a', 0};
}

void MainWindow::ajouterPiece(Emplacement emplacement, bool isBlack){
    if(!isBlack){
        QPalette palette = buttons_[TAILLEECHEQUIER*emplacement.convertHorizontalPos() + emplacement.verticalPos]->palette();
        QColor color = QColorDialog::getColor(Qt::white, this);
        palette.setColor(QPalette::WindowText, color);
        buttons_[TAILLEECHEQUIER*emplacement.convertHorizontalPos() + emplacement.verticalPos]->setPalette(palette);
    }
    int a = TAILLEECHEQUIER*emplacement.verticalPos + emplacement.convertHorizontalPos();
    buttons_[TAILLEECHEQUIER*emplacement.verticalPos + emplacement.convertHorizontalPos()]->setText("P");
}
/*
void MainWindow::deplacePiece(){
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    Emplacement position = findPositionButton(button);
    echequierLogique_->move(position);
    if(!echequierLogique_->getPreparerBougerOuNon()){
        emplacementPrecedent_ = position;
    }
    else{
        buttons_[TAILLEECHEQUIER*emplacementPrecedent_.convertCharToInt() + emplacementPrecedent_.verticalPos_]->setText("");
        buttons_[TAILLEECHEQUIER*position.convertCharToInt() + position.verticalPos_]->setText(typeid(*(echequierLogique_->getPieceADeplacer())).name());
    }

}
*/
MainWindow::~MainWindow()
{
    delete ui;
    delete centralWidget_;
    delete layout_;
    delete echequierLogique_;
    for(int i = 0; i<TAILLEECHEQUIER*TAILLEECHEQUIER; i++){
        delete buttons_[i];
    }
}

