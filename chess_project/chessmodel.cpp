#include "chessmodel.h"
#include <iostream>


/*
Chessmodel::Chessmodel(){

};
*/


int Emplacement::convertHorizontalPos(){return int(horizontalPos) - int('a');};

Piece::Piece():emplacement_({'a', 9}), isBlack_(true){};

Piece::Piece(Emplacement emplacement, bool isBlack):emplacement_(emplacement), isBlack_(isBlack){};

Emplacement Piece::getEmplacement() const{return emplacement_;};

void Piece::setEmplacement(Emplacement emplacement){emplacement_ = emplacement;};

bool Piece::getIsBlack() const {return isBlack_;};

void Piece::setBlack(bool isBlack){isBlack_ = isBlack;}

Echequier::Echequier(){};

bool Echequier::isTherePiece(Emplacement emplacement){
    for(auto&& element:pieces_){
        if(element->getEmplacement().convertHorizontalPos() == emplacement.convertHorizontalPos() && element->getEmplacement().verticalPos == emplacement.verticalPos)
            return true;
    }
    return false;
};

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

Game::Game():veutBouger_(false){echequier_ = std::make_shared<Echequier>();};

void Game::setEmplacementInteresser(Emplacement emplacementInteresser){
    emplacementInteresser_ = emplacementInteresser;
};

void Game::setProchainEmplacement(Emplacement prochainEmplacement){
    prochainEmplacement_ = prochainEmplacement;
};

std::shared_ptr<Echequier> Game::getEchequier() const {
    return echequier_;
}

bool Game::getVeutBouger() const {
    return veutBouger_;
}

void Game::move(Emplacement positionInitialOuFinal){
    if (!veutBouger_){
        if(echequier_->isTherePiece(positionInitialOuFinal)){
            veutBouger_ = true;
            emplacementInteresser_ = positionInitialOuFinal;
        }
    }
    else{
        for(auto&& piece:echequier_->pieces_){
            if(piece->getEmplacement().convertHorizontalPos()==emplacementInteresser_.convertHorizontalPos()&&piece->getEmplacement().verticalPos==emplacementInteresser_.verticalPos){
                piece->setEmplacement(positionInitialOuFinal);
                veutBouger_ = false;
                prochainEmplacement_ = positionInitialOuFinal;
                emit pieceMoved(emplacementInteresser_, prochainEmplacement_);
            }
        }

    }
};


