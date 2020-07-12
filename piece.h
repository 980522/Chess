#ifndef _PIECE_H_
#define _PIECE_H_
#include <vector>
#include "grid.h"
#include "posn.h"



class Piece {

    Posn p;
    Colour colour;
    bool New;
    char type;

    virtual void move(const Grid& g, Posn dest) = 0;
    virtual std::vector<Posn> amove(const Grid& g) const = 0;
    virtual bool check(const Grid& g, Posn dest) = 0;
    virtual std::vector<Posn> attack(const Grid& g) const = 0;
    virtual bool isK() = 0;

    void setPosn(Posn posn) {p = posn;}
    void setNew(bool b) {New = b;}

    friend class Grid;

    
protected:

 
    void setType(char t) {type = t;}

public:

    Piece(Posn posn, Colour c, bool New = true, char type = '0'): p {posn}, colour {c}, New {New}, type {type} {}
    Piece(const Piece& pp): p {pp.p}, colour {pp.colour}, New {pp.New}, type {pp.type} {}
    
    Piece& operator= (const Piece& pp) {
        if (this == &pp) return *this;
        p = pp.p;
        colour = pp.colour;
        New = pp.New;
        type = pp.type;
        return *this;
    }

    void movePiece(const Grid& g, Posn dest) {move(g, dest);}
    std::vector<Posn> moveable(const Grid& g) const {return amove(g);}
    std::vector<Posn> attackable(const Grid& g) const {return attack(g);}
    Posn getPosn() const {return p;}
    Colour getColour() const {return colour;}
    bool getNew() const {return New;}
    bool checkKing(const Grid& g, Posn dest) {return check(g, dest);}
    char getType() const {return type;}
    bool isKing() {return isK();}

    virtual ~Piece() {}
};


#endif
