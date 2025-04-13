#include "chessmodel.h"

/*
Chessmodel::Chessmodel(){

};
*/

Emplacement::Emplacement():horizontalPos_('a'), verticalPos_(0){};

Emplacement::Emplacement(char horizontalPos, int verticalPos):horizontalPos_(horizontalPos), verticalPos_(verticalPos){};

int Emplacement::convertCharToInt(){
    return int(horizontalPos_) - int('a');
}

Piece::Piece():position_(),isBlack_(true){};

Piece::Piece(Emplacement position, bool isBlack):position_(position), isBlack_(isBlack){};

void Piece::changerPosition(Emplacement nouvellePosition){
    position_ = nouvellePosition;
}

Emplacement Piece::getEmplacement() const {return position_;}

int Roi::nbrRois_ = 0;

Roi::Roi():Piece(){nbrRois_+=1;};

Roi::Roi(Emplacement position, bool isBlack):Piece(position, isBlack){nbrRois_+=1;};

bool Roi::canMoveTo(Emplacement nouvellePosition){
    if (abs(nouvellePosition.verticalPos_ - position_.horizontalPos_)<=1 && abs(nouvellePosition.convertCharToInt() - position_.convertCharToInt())<=1)
        return true;
    else
        return false;
};

Tour::Tour():Piece(){};

Tour::Tour(Emplacement position, bool isBlack):Piece(position, isBlack){};

bool Tour::canMoveTo(Emplacement nouvellePosition){
    if (abs(position_.verticalPos_ - nouvellePosition.verticalPos_) == 0 || abs(position_.convertCharToInt() - nouvellePosition.convertCharToInt()) == 0)
        return true;
    else
        return false;
}

Cavalier::Cavalier():Piece(){};

Cavalier::Cavalier(Emplacement position, bool isBlack): Piece(position, isBlack){};

bool Cavalier::canMoveTo(Emplacement nouvelleEmplacement){
    if (abs(position_.verticalPos_ - nouvelleEmplacement.verticalPos_) == 3 && abs(position_.convertCharToInt() - nouvelleEmplacement.convertCharToInt())==2)
        return true;
    else if (abs(position_.verticalPos_ - nouvelleEmplacement.verticalPos_) == 2 && abs(position_.convertCharToInt() - nouvelleEmplacement.convertCharToInt())==3)
        return true;
    else
        return false;
}

Echequier::Echequier(){};

Echequier::~Echequier(){};

void Echequier::placerPiece(Piece& pieceAPlacer, Emplacement emplacementAPlacer){

}

void Echequier::deplacer(Piece& pieceADeplacer, Emplacement emplacementFinale){
    pieceADeplacer.changerPosition(emplacementFinale);
}


