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
    if(abs(emplacement_.convertHorizontalPos() - emplacementFutur.convertHorizontalPos()) == 2 && abs(emplacement_.verticalPos - emplacementFutur.verticalPos) == 1)
        return true;
    else if(abs(emplacement_.convertHorizontalPos() - emplacementFutur.convertHorizontalPos()) == 1 && abs(emplacement_.verticalPos - emplacementFutur.verticalPos) == 2)
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
    if(!isTherePiece(emplacement)){
        if(pieceType == "Roi"){
            try{
                pieces_.push_back(std::make_unique<Roi>());
                if(dynamic_cast<Roi*>(&(*(pieces_[pieces_.size() - 1])))->nbrRois_ >= 3){
                    pieces_.pop_back();
                    throw std::logic_error("Trop de rois");
                }
            }
            catch(std::logic_error& e){
                emit erreurAjout();
                return ;
            }
            // verifier cmb de rois il y a
            }
        else if(pieceType == "Tour")
            pieces_.push_back(std::make_unique<Tour>());
        else if(pieceType == "Cavalier")
            pieces_.push_back(std::make_unique<Cavalier>());
        if(pieces_.size() == 1){
            pieces_[0]->setEmplacement(emplacement);
            pieces_[0]->setBlack(isBlack);
        }
        else{
            pieces_[pieces_.size()-1]->setEmplacement(emplacement);
            pieces_[pieces_.size()-1]->setBlack(isBlack);
        }
        emit ajoutDUnePiece(pieceType, emplacement, isBlack);
    }
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

bool Game::isIllegalMove(std::unique_ptr<Piece>& piece, Emplacement positionFinale) const{
    bool isIllegal = false;
    if(piece->getTypeDePiece()=="Roi"){
        if(!dynamic_cast<Roi*>(&(*(piece)))->peutDeplacer(positionFinale)){
            isIllegal = true;
        }
    }
    else if(piece->getTypeDePiece()=="Tour"){
        if(!dynamic_cast<Tour*>(&(*(piece)))->peutDeplacer(positionFinale)){
            isIllegal = true;
        }
    }
    else if(piece->getTypeDePiece()=="Cavalier"){
        if(!dynamic_cast<Cavalier*>(&(*(piece)))->peutDeplacer(positionFinale)){
            isIllegal = true;
        }
    }
    return isIllegal;
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
        bool isIllegal = true;
        bool enEchec = false;
        {
            MoveTemporaire moveTemporaire(emplacementInteresser_, positionInitialOuFinal, this);
            enEchec = moveTemporaire.enEchec();
        }
        for(auto&& piece:echequier_->pieces_){
            if(piece->getEmplacement().convertHorizontalPos()==emplacementInteresser_.convertHorizontalPos()&&piece->getEmplacement().verticalPos==emplacementInteresser_.verticalPos){
                veutBouger_ = false;
                isIllegal = isIllegalMove(piece, positionInitialOuFinal);
                if(!enEchec && !isIllegal){
                    piece->setEmplacement(positionInitialOuFinal);
                    prochainEmplacement_ = positionInitialOuFinal;
                }
            }
        }
        return enEchec || isIllegal;
    }
};

MoveTemporaire::MoveTemporaire(Emplacement positionInitiale, Emplacement positionFinale, Game* game):positionInitiale_(positionInitiale), positionFinale_(positionFinale), game_(game){};

bool MoveTemporaire::enEchec(){
    Emplacement emplacementRoi = {'z', 9};
    int indexPiece = game_->getEchequier()->trouverPiece(positionInitiale_);
    bool enEchec = false;
    bool isRoiBlack = false;
    if(!game_->isIllegalMove(game_->getEchequier()->pieces_[indexPiece], positionFinale_)){
        game_->getEchequier()->pieces_[indexPiece]->setEmplacement(positionFinale_);
        for(auto&& piece:game_->getEchequier()->pieces_){
            if(piece->getTypeDePiece() == "Roi" && piece->getIsBlack() == game_->getEchequier()->pieces_[indexPiece]->getIsBlack()){
                emplacementRoi = piece->getEmplacement();
                isRoiBlack = piece->getIsBlack();
            }
        }
        for(auto&& piece:game_->getEchequier()->pieces_){
            if(piece->getIsBlack() != isRoiBlack && emplacementRoi.verticalPos != 9){
                if(piece->getTypeDePiece() == "Tour"){
                    if(dynamic_cast<Tour*>(&(*(piece)))->peutDeplacer(emplacementRoi))
                        enEchec = true;
                }
                else if(piece->getTypeDePiece() == "Cavalier"){
                    if(dynamic_cast<Cavalier*>(&(*(piece)))->peutDeplacer(emplacementRoi))
                        enEchec = true;;
                }
            }
        }
    }
    return enEchec;
};

MoveTemporaire::~MoveTemporaire(){
    int indexPiece =  game_->getEchequier()->trouverPiece(positionFinale_);
    game_->getEchequier()->pieces_[indexPiece]->setEmplacement(positionInitiale_);
};

}

