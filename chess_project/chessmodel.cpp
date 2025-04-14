#include "chessmodel.h"
#include <iostream>


/*
Chessmodel::Chessmodel(){

};
*/


int Emplacement::convertHorizontalPos(){return int(horizontalPos) - int('a');};

Piece::Piece():emplacement_({'a', 9}), isBlack_(true){};

Piece::Piece(Emplacement emplacement, bool isBlack):emplacement_(emplacement), isBlack_(isBlack){};

Emplacement Piece::getEmplacement() const{emplacement_;};

void Piece::setEmplacement(Emplacement emplacement){emplacement_ = emplacement;};

bool Piece::getIsBlack() const {return isBlack_;};

void Piece::setBlack(bool isBlack){isBlack_ = isBlack;}

Echequier::Echequier(){};

//bool Echequier::isTherePiece(Emplacement emplacement){};

void Echequier::ajouterPiece(Emplacement emplacement, bool isBlack){
    pieces_.push_back(std::make_unique<Piece>());
    if(pieces_.size() == 1){
        pieces_[0]->setEmplacement(emplacement);
        pieces_[0]->setBlack(isBlack);
    }
    else{
        pieces_[pieces_.size()-1]->setEmplacement(emplacement);
        pieces_[pieces_.size()-1]->setBlack(isBlack);
    }
    emit ajoutDUnePiece(emplacement, isBlack);
};

//Game::Game(){};

//void Game::setEmplacementInteresser(Emplacement emplacementInteresser){};

//void Game::setProchainEmplacement(Emplacement prochainEmplacement){};

//void Game::move(){};


