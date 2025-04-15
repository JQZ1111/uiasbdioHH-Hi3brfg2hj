#include "chessmodel.h"
#include <iostream>


/*
Chessmodel::Chessmodel(){

};
*/

namespace logic{
int Emplacement::convertHorizontalPos(){return int(horizontalPos) - int('a');};

Piece::Piece():emplacement_({'a', 9}), isBlack_(true){};

Piece::Piece(Emplacement emplacement, bool isBlack):emplacement_(emplacement), isBlack_(isBlack){};

Emplacement Piece::getEmplacement() const{return emplacement_;};

void Piece::setEmplacement(Emplacement emplacement){emplacement_ = emplacement;};

bool Piece::getIsBlack() const {return isBlack_;};

void Piece::setBlack(bool isBlack){isBlack_ = isBlack;}

Roi::Roi():Piece(), typeDePiece_("Roi"){nbrRois_+=1;};

Roi::Roi(Emplacement emplacement, bool isBlack):Piece(emplacement, isBlack), typeDePiece_("Roi"){nbrRois_ += 1;};

bool Roi::peutDeplacer(Emplacement emplacementFutur){
    if(abs(emplacement_.convertHorizontalPos() - emplacementFutur.convertHorizontalPos())<=1 && abs(emplacement_.verticalPos - emplacementFutur.verticalPos) <= 1)
        return true;
    else
        return false;
};

int Roi::nbrRois_ = 0;

Tour::Tour():Piece(), typeDePiece_("Tour"){};

Tour::Tour(Emplacement emplacement, bool isBlack):Piece(emplacement, isBlack), typeDePiece_("Tour"){};

bool Tour::peutDeplacer(Emplacement emplacementFutur){
    if(abs(emplacement_.convertHorizontalPos() - emplacementFutur.convertHorizontalPos()) == 0 || abs(emplacement_.verticalPos - emplacementFutur.verticalPos) == 0)
        return true;
    else
        return false;
};

Cavalier::Cavalier():Piece(), typeDePiece_("Cavalier"){};

Cavalier::Cavalier(Emplacement emplacement, bool isBlack):Piece(emplacement, isBlack), typeDePiece_("Cavalier"){};

bool Cavalier::peutDeplacer(Emplacement emplacementFutur){
    if(abs(emplacement_.convertHorizontalPos() - emplacementFutur.convertHorizontalPos()) == 3 || abs(emplacement_.verticalPos - emplacementFutur.verticalPos) == 2)
        return true;
    else if(abs(emplacement_.convertHorizontalPos() - emplacementFutur.convertHorizontalPos()) == 2 || abs(emplacement_.verticalPos - emplacementFutur.verticalPos) == 3)
        return true;
    else
        return false;
};

Echequier::Echequier(){};

bool Echequier::isTherePiece(Emplacement emplacement){
    for(auto&& element:pieces_){
        if(element->getEmplacement().convertHorizontalPos() == emplacement.convertHorizontalPos() && element->getEmplacement().verticalPos == emplacement.verticalPos)
            return true;
    }
    return false;
};

void Echequier::ajouterPiece(std::string pieceType, Emplacement emplacement, bool isBlack){
    // Need to change that, piece is an abstract class now
    pieces_.push_back(std::make_unique<Tour>());
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

bool Game::move(Emplacement positionInitialOuFinal){
    if (!veutBouger_){
        if(echequier_->isTherePiece(positionInitialOuFinal)){
            veutBouger_ = true;
            emplacementInteresser_ = positionInitialOuFinal;
            return true;
        }
        return true;
    }
    else{
        for(auto&& piece:echequier_->pieces_){
            if(piece->getEmplacement().convertHorizontalPos()==emplacementInteresser_.convertHorizontalPos()&&piece->getEmplacement().verticalPos==emplacementInteresser_.verticalPos){
                piece->setEmplacement(positionInitialOuFinal);
                veutBouger_ = false;
                prochainEmplacement_ = positionInitialOuFinal;
            }
        }
        return false;

    }
};
}

