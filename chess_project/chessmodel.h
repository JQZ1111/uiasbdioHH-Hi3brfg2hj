#ifndef CHESSMODEL_H
#define CHESSMODEL_H
#include <QObject>
#include <memory>
#include <vector>

/*
 * Module pour faire le modèle Logique du jeu
**/



namespace logic{
//class Chessmodel;
struct Emplacement;
class Piece;
class Roi;
class Tour;
class Cavalier;
class Echequier;
//class Move;
}
/*
class Chessmodel
{
public:
    Chessmodel();
};
*/

struct Emplacement{
    Emplacement();
    Emplacement(char horizontalPos, int verticalPos);
    int convertCharToInt();
    char horizontalPos_;
    int verticalPos_;
};

class Piece{
    // Si tu veux mettre le Q_OBJECT, faut absolument que la classe hérite d'une classe commençant par Q (QObject par exemple)
    Q_OBJECT
public:
    Piece();
    Piece(Emplacement position, bool isBlack);
    void changerPosition(Emplacement nouvellePosition);
    Emplacement getEmplacement() const;
protected:
    Emplacement position_;
    bool isBlack_;
};

class Roi: public Piece{
    Q_OBJECT
public:
    Roi();
    Roi(Emplacement position, bool isBlack);
    bool canMoveTo(Emplacement nouvellePosition);
protected:
    static int nbrRois_;
};

class Tour:public Piece{
    Q_OBJECT
public:
    Tour();
    Tour(Emplacement position, bool isBlack);
    bool canMoveTo(Emplacement nouvellePosition);
};

class Cavalier:public Piece{
    Q_OBJECT
public:
    Cavalier();
    Cavalier(Emplacement position, bool isBlack);
    bool canMoveTo(Emplacement nouvellePosition);
};

class Echequier{
    Q_OBJECT
public:
    Echequier();
    ~Echequier();
    void placerPiece(Piece& pieceAPlacer, Emplacement emplacementAPlacer);
    void deplacer(Piece& pieceADeplacer, Emplacement emplacementFinale);
private:
    std::vector<std::unique_ptr<Roi>> rois_;
    std::vector<std::unique_ptr<Tour>> tours_;
    std::vector<std::unique_ptr<Cavalier>> cavaliers_;
signals:
    // Signal qu'on assigne une position à une certaine pièce
    void assignerPosition();
    // Signal qu'on enlève une pièce d'une certaine position
    void enleverDeLaPosition();
};
/*
class Move{
public:
    // Ne devrait pas avoir de constructeur par défaut, car on crée la class seulement pour savoir si on bouge ou pas
    Move(Echequier& echequier, Piece& pieceABouger, Emplacement& positionFinale);

    void bouger();
private:
    Echequier& echequier_;
    Piece& pieceABouger_;
    Emplacement& positionFinale_;
signals:
};
*/



#endif // CHESSMODEL_H
