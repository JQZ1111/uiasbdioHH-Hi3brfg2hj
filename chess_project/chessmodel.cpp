#include "chessmodel.h"


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

std::string Piece::getTypeDePiece() const {return typeDePiece_;}

void Piece::setTypeDePiece(std::string typeDePiece){typeDePiece_ = typeDePiece;}

Roi::Roi():Piece(){
    nbrRois_+=1;
    typeDePiece_ = "Roi";
};

Roi::Roi(Emplacement emplacement, bool isBlack):Piece(emplacement, isBlack){
    nbrRois_ += 1;
    typeDePiece_ = "Roi";
};

bool Roi::peutDeplacer(Emplacement emplacementFutur){
    if(abs(emplacement_.convertHorizontalPos() - emplacementFutur.convertHorizontalPos())<=1 && abs(emplacement_.verticalPos - emplacementFutur.verticalPos) <= 1)
        return true;
    else
        return false;
};

int Roi::nbrRois_ = 0;

Tour::Tour():Piece(){typeDePiece_ = "Tour";};

Tour::Tour(Emplacement emplacement, bool isBlack):Piece(emplacement, isBlack){typeDePiece_ = "Tour";};

bool Tour::peutDeplacer(Emplacement emplacementFutur){
    if(abs(emplacement_.convertHorizontalPos() - emplacementFutur.convertHorizontalPos()) == 0 || abs(emplacement_.verticalPos - emplacementFutur.verticalPos) == 0)
        return true;
    else
        return false;
};

Cavalier::Cavalier():Piece(){typeDePiece_ = "Cavalier";};

Cavalier::Cavalier(Emplacement emplacement, bool isBlack):Piece(emplacement, isBlack){typeDePiece_ = "Cavalier";};

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
    if(pieceType == "Roi")
        pieces_.push_back(std::make_unique<Roi>());
    if(pieceType == "Tour")
        pieces_.push_back(std::make_unique<Tour>());
    if(pieceType == "Cavalier")
        pieces_.push_back(std::make_unique<Cavalier>());
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

int Echequier::trouverPiece(Emplacement emplacement){
    for(unsigned long long i = 0; i<pieces_.size(); i++){
        if(pieces_[i]->getEmplacement().convertHorizontalPos() == emplacement.convertHorizontalPos() && pieces_[i]->getEmplacement().verticalPos == emplacement.verticalPos)
            return i;
    }
    return 0;
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

MoveTemporaire::MoveTemporaire(Emplacement positionInitiale, Emplacement positionFinale, Game* game):positionInitiale_(positionInitiale), positionFinale_(positionFinale), game_(game){};

bool MoveTemporaire::enEchec(){
    Emplacement emplacementRoi;
    int indexPiece = game_->getEchequier()->trouverPiece(positionInitiale_);
    game_->move(positionInitiale_);
    game_->move(positionFinale_);
    for(auto&& piece:game_->getEchequier()->pieces_){
        if(piece->getTypeDePiece() == "Roi" && piece->getIsBlack() == game_->getEchequier()->pieces_[indexPiece]->getIsBlack()){
            emplacementRoi = piece->getEmplacement();
        }
        if(piece->getIsBlack() != game_->getEchequier()->pieces_[indexPiece]->getIsBlack()){
            if(piece->getTypeDePiece() == "Tour"){
                if(dynamic_cast<Tour*>(&(*(piece)))->peutDeplacer(emplacementRoi))
                            return true;
            }
            else if(piece->getTypeDePiece() == "Cavalier"){
                if(dynamic_cast<Cavalier*>(&(*(piece)))->peutDeplacer(emplacementRoi))
                    return true;
            }
            else
                return false;
        }
    }
    return false;
};

MoveTemporaire::~MoveTemporaire(){
    game_->move(positionFinale_);
    game_->move(positionInitiale_);
};

}

