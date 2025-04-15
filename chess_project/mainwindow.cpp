#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
#include <QComboBox>
#include <qcombobox.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , game_()
    , pieceHorizontalPos_('a')
    , pieceVerticalPos_(0)
    , noirOuPas_(true)
{
    ui->setupUi(this);
    makeComboBox();
    QObject::connect(comboBoxHorizontal_, SIGNAL(currentIndexChanged(int)), this, SLOT(setHorizontalPosition(int)));
    QObject::connect(comboBoxVertical_, SIGNAL(currentIndexChanged(int)), this, SLOT(setVerticalPosition(int)));
    QObject::connect(comboBoxNoirOuBlanc_, SIGNAL(currentIndexChanged(int)), this, SLOT(setNoirOuBlanc(int)));
    makeCentralWidget();
    QObject::connect(this, SIGNAL(pieceAjouter(Emplacement,bool)), game_->getEchequier().get(), SLOT(ajouterPiece(Emplacement,bool)));
    QObject::connect(addPieceButton_, SIGNAL(clicked()), this, SLOT(ajouterPiece()));
    game_->getEchequier()->ajouterPiece({'a', 5}, false);// Sill does not work well for white piece
    // Cant center it tho
    for(int i = 0; i < TAILLEECHEQUIER; i++){
        for(int j = 0; j < TAILLEECHEQUIER; j ++){
            QObject::connect(buttons_[TAILLEECHEQUIER*j + i], SIGNAL(clicked()), this, SLOT(deplacerPiece()));// aaand it crashed
        }
    }
}

void MainWindow::makeComboBox(){
    comboBoxVertical_ = new QComboBox();
    comboBoxHorizontal_ = new QComboBox();
    for(int i = 0; i < TAILLEECHEQUIER; i++){
        comboBoxHorizontal_->addItem(QString::number(i));
        comboBoxVertical_->addItem(QString(QChar::fromLatin1(char(i + int('a')))));
    }
    comboBoxNoirOuBlanc_ = new QComboBox();
    comboBoxNoirOuBlanc_->addItem("noir");
    comboBoxNoirOuBlanc_->addItem("blanc");
}

void MainWindow::makeCentralWidget(){
    layout_ = new QGridLayout();
    layout_->setSpacing(0);
    layout_->setContentsMargins(0, 0, 0, 0);
    game_ = new Game();
    centralWidget_ = new QWidget();
    addPieceButton_ = new QPushButton();
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
    addPieceButton_->setText("ajouter");
    addPieceButton_->setFixedHeight(20);
    addPieceButton_->setFixedWidth(40);
    layout_->addWidget(comboBoxVertical_);
    layout_->addWidget(comboBoxHorizontal_);
    layout_->addWidget(comboBoxNoirOuBlanc_);
    layout_->addWidget(addPieceButton_);
    centralWidget_->setLayout(layout_);
    centralWidget_->setMaximumHeight(40*TAILLEECHEQUIER);
    centralWidget_->setMaximumWidth(40*TAILLEECHEQUIER);
    setCentralWidget(centralWidget_);
}

void MainWindow::setHorizontalPosition(int horizontalPos){
    pieceHorizontalPos_ = char(horizontalPos + int('a'));
}

void MainWindow::setVerticalPosition(int verticalPos){pieceVerticalPos_ = verticalPos;}

void MainWindow::setNoirOuBlanc(int noirOuBlanc){
    if(noirOuBlanc == 0)
        noirOuPas_ = true;
    else
        noirOuPas_ = false;
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

void MainWindow::ajouterPiece(){
    Emplacement emplacement = {pieceHorizontalPos_, pieceVerticalPos_};
    bool isBlack = noirOuPas_;
    if(!isBlack){
        if((emplacement.verticalPos + emplacement.convertHorizontalPos())%2 == 1)
            buttons_[TAILLEECHEQUIER*emplacement.verticalPos + emplacement.convertHorizontalPos()]->setStyleSheet("background-color:yellow;color:white");
        else
            buttons_[TAILLEECHEQUIER*emplacement.verticalPos + emplacement.convertHorizontalPos()]->setStyleSheet("background-color:brown;color:white");
        /*
        QPalette palette = buttons_[TAILLEECHEQUIER*emplacement.convertHorizontalPos() + emplacement.verticalPos]->palette();
        QColor color = QColorDialog::getColor(Qt::white, this);
        palette.setColor(QPalette::WindowText, color);
        buttons_[TAILLEECHEQUIER*emplacement.convertHorizontalPos() + emplacement.verticalPos]->setPalette(palette);
*/
    }
    buttons_[TAILLEECHEQUIER*emplacement.verticalPos + emplacement.convertHorizontalPos()]->setText("P");
    emit pieceAjouter(emplacement, isBlack);
}

void MainWindow::deplacerPiece(){
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    Emplacement position = findPositionButton(button);
    bool nePasDeplacer = game_->move(position);
    // If the text at the position of button is blank, dont do anything
    if(game_->getVeutBouger() && button->text() != ""){
        emplacementPrecedent_ = position;
    }
    else if (!nePasDeplacer && button->text() == ""){
        buttons_[TAILLEECHEQUIER*emplacementPrecedent_.verticalPos + emplacementPrecedent_.convertHorizontalPos()]->setText("");
        buttons_[TAILLEECHEQUIER*position.verticalPos + position.convertHorizontalPos()]->setText("P"); // changer ca quand on aura plus qu'une type de piece
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

