#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , game_()
{
    ui->setupUi(this);
    makeCentralWidget();
    QObject::connect((game_->getEchequier()).get(), SIGNAL(ajoutDUnePiece(Emplacement,bool)), this, SLOT(ajouterPiece(Emplacement,bool)));
    game_->getEchequier()->ajouterPiece({'a', 5}, false);// Sill does not work well for white piece
    // Cant center it tho
    for(int i = 0; i < TAILLEECHEQUIER; i++){
        for(int j = 0; j < TAILLEECHEQUIER; j ++){
            QObject::connect(buttons_[TAILLEECHEQUIER*j + i], SIGNAL(clicked()), this, SLOT(deplacerPiece()));// aaand it crashed
        }
    }
}

void MainWindow::makeCentralWidget(){
    layout_ = new QGridLayout();
    layout_->setSpacing(0);
    layout_->setContentsMargins(0, 0, 0, 0);
    game_ = new Game();
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
    buttons_[TAILLEECHEQUIER*emplacement.verticalPos + emplacement.convertHorizontalPos()]->setText("P");
}

void MainWindow::deplacerPiece(){
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    Emplacement position = findPositionButton(button);
    game_->move(position);
    if(!game_->getVeutBouger()){
        emplacementPrecedent_ = position;
    }
    else{
        buttons_[TAILLEECHEQUIER*emplacementPrecedent_.convertHorizontalPos() + emplacementPrecedent_.verticalPos]->setText("");
        buttons_[TAILLEECHEQUIER*position.convertHorizontalPos() + position.verticalPos]->setText("P"); // changer ca quand on aura plus qu'une type de piece
    }

}

MainWindow::~MainWindow()
{
    delete ui;
    delete centralWidget_;
    delete layout_;
    delete game_;
    for(int i = 0; i<TAILLEECHEQUIER*TAILLEECHEQUIER; i++){
        delete buttons_[i];
    }
}

