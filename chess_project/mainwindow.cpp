#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    layout_ = new QGridLayout();
    layout_->setSpacing(0);
    layout_->setContentsMargins(0, 0, 0, 0);

    echequier_ = new QWidget();
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
    echequier_->setLayout(layout_);
    echequier_->setMaximumHeight(40*TAILLEECHEQUIER);
    echequier_->setMaximumWidth(40*TAILLEECHEQUIER);
    setCentralWidget(echequier_);
    // Cant center it tho
}


MainWindow::~MainWindow()
{
    delete ui;
    delete echequier_;
    delete layout_;
    for(int i = 0; i<TAILLEECHEQUIER*TAILLEECHEQUIER; i++){
        delete buttons_[i];
    }
}

