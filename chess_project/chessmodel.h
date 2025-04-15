#ifndef CHESSMODEL_H
#define CHESSMODEL_H
#include <QObject>
#include <memory>
#include <vector>

/*
 * Module pour faire le modèle Logique du jeu
**/

int const TAILLEECHEQUIER = 8;


namespace logic{
struct Emplacement;
class Piece;
struct Echequier;
class Game;
}

struct Emplacement{
    char horizontalPos;
    int verticalPos;
    int convertHorizontalPos();
};

class Piece{
public:
    Piece();
    Piece(Emplacement emplacement, bool isBlack);
    Emplacement getEmplacement() const;
    void setEmplacement(Emplacement emplacement);
    bool getIsBlack() const ;
    void setBlack(bool isBlack);
    virtual bool peutDeplacer(Emplacement emplacementFuture) = 0;
    virtual ~Piece() = default;
protected:
    Emplacement emplacement_;
    bool isBlack_;
};

struct Roi:public Piece{
    Roi();
    Roi(Emplacement emplacement, bool isBlack);
    bool peutDeplacer(Emplacement emplacementFutur);
    std::string typeDePiece_;
    static int nbrRois_;
};

struct Tour:public Piece{
    Tour();
    Tour(Emplacement emplacement, bool isBlack);
    bool peutDeplacer(Emplacement emplacementFutur);
    std::string typeDePiece_;
};

struct Cavalier:public Piece{
    Cavalier();
    Cavalier(Emplacement emplacement, bool isBlack);
    bool peutDeplacer(Emplacement emplacementFutur);
    std::string typeDePiece_;
};

struct  Echequier:public QObject{
    Q_OBJECT
public:
    Echequier();
    bool isTherePiece(Emplacement emplacement);
    std::vector<std::unique_ptr<Tour>> pieces_;
public slots:
    void ajouterPiece(std::string pieceType, Emplacement emplacement, bool isBlack);
    // mettre un enleverPiece
signals:
    void ajoutDUnePiece(Emplacement emplacement, bool isBlack);
};


class Game:public QObject{
    Q_OBJECT
public:
    Game();
    void setEmplacementInteresser(Emplacement emplacementInteresser);
    void setProchainEmplacement(Emplacement prochainEmplacement);
    std::shared_ptr<Echequier> getEchequier() const;
    bool getVeutBouger() const;
    // check s'il y a une piece à l'emplacement. Si oui, donner à cette pièce l'emplacement prochain
public slots:
    bool move(Emplacement positionInitialOuFinal);
signals:
    void pieceMoved(Emplacement emplacementInteresser, Emplacement prochainEmplacement);
private:
    std::shared_ptr<Echequier> echequier_;
    Emplacement emplacementInteresser_;
    Emplacement prochainEmplacement_;
    bool veutBouger_;
};


#endif // CHESSMODEL_H
