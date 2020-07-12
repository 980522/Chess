#include "pawn.h"
#include <cstddef>
#include <iostream>
using namespace std;

Pawn::Pawn(Posn posn, Colour colour): Piece(posn, colour) {setType('p');}

void Pawn::move(const Grid& g, Posn dest) {

    Posn p = getPosn();
    Posn direction, tmp, passAttack;
    Piece* justMovedPawn = g.getJustMovedPawn();

    if (getColour() == Colour::White) direction = {-1, 0};
    else if (getColour() == Colour::Black) direction = {1, 0};

    if (dest - p == direction) {
        if (g.getTheGrid()[dest.x][dest.y]) \
        throw "Pawn Destination error: destination is not empty.";
        return;
    }

    direction.y = -1;
    passAttack = {p.x, p.y + direction.y};

    if (dest - p == direction) {
        if (g.getTheGrid()[dest.x][dest.y] && g.getTheGrid()[dest.x][dest.y]->getColour() != getColour()) {return;}
        else if (!(g.getTheGrid()[dest.x][dest.y])) {
            if (g.getTheGrid()[passAttack.x][passAttack.y] \
            && g.getTheGrid()[passAttack.x][passAttack.y]->getColour() != getColour() && \
            g.getTheGrid()[passAttack.x][passAttack.y]->getType() == 'p' && \
             justMovedPawn && justMovedPawn->getPosn() == passAttack)  {return;}
            throw "Pass attack error: only just 2-square moved pawn is attackable by pass attack.";
        }
        else throw "Destination error: destination is ally.";
    }

    direction.y = 1;
    passAttack = {p.x, p.y + direction.y};


    if (dest - p == direction) {
        if (g.getTheGrid()[dest.x][dest.y] && g.getTheGrid()[dest.x][dest.y]->getColour() != getColour()) return;
        else if (!(g.getTheGrid()[dest.x][dest.y])) {
            if (g.getTheGrid()[passAttack.x][passAttack.y] \
            && g.getTheGrid()[passAttack.x][passAttack.y]->getColour() != getColour() && \
            g.getTheGrid()[passAttack.x][passAttack.y]->getType() == 'p' && \
             justMovedPawn && justMovedPawn->getPosn() == passAttack)  {return;}
            throw "Pass attack error: only just 2-square moved pawn is attackable by pass attack.";
        }
        else throw "Destination error: destination is ally.";
    }

    direction.y = 0;
    passAttack = p + direction;
    direction = direction + direction;

    if (dest - p == direction) {
        if (!getNew()) throw "Pawn error: operation is avaliable for new pawn only.";
        if (g.getTheGrid()[passAttack.x][passAttack.y]) throw "Destination error: pass is blocked.";
        if (g.getTheGrid()[dest.x][dest.y]) throw "Pawn Destination error: destination is not empty.";

        return;
    }

    throw "Destination error: wrong direction.";
}


vector<Posn> Pawn::amove(const Grid& g) const {

    Posn p = getPosn();
    Posn direction, tmp, passAttack;
    Piece* justMovedPawn = g.getJustMovedPawn();

    if (getColour() == Colour::White) direction = {-1, 0};
    else if (getColour() == Colour::Black) direction = {1, 0};

    vector<Posn> v;
    tmp = p + direction;


    if (tmp.x >= 0 && tmp.x < 8 && !g.getTheGrid()[tmp.x][tmp.y]) {
        v.emplace_back(tmp);
        tmp = tmp + direction;
        if (tmp.x >= 0 && tmp.x < 8 && getNew() && !g.getTheGrid()[tmp.x][tmp.y]) {
            v.emplace_back(tmp);
        }
    }
    direction = {direction.x, -1};
    tmp = p + direction;
    passAttack = tmp - Posn{direction.x, 0};


    if (tmp.x >= 0 && tmp.x < 8 && tmp.y >= 0 && tmp.y < 8 \
    && ((g.getTheGrid()[tmp.x][tmp.y] && g.getTheGrid()[tmp.x][tmp.y]->getColour() != getColour()) \
     || (justMovedPawn && justMovedPawn->getColour() != getColour() && justMovedPawn->getPosn() == passAttack))) {
        v.emplace_back(tmp);
    }


    direction = {direction.x, 1};
    tmp = p + direction;
    passAttack = tmp - Posn{direction.x, 0};

    if (tmp.x >= 0 && tmp.x < 8 && tmp.y >= 0 && tmp.y < 8 \
    && ((g.getTheGrid()[tmp.x][tmp.y] && g.getTheGrid()[tmp.x][tmp.y]->getColour() != getColour()) \
     || (justMovedPawn && justMovedPawn->getColour() != getColour() && justMovedPawn->getPosn() == passAttack))) {
        v.emplace_back(tmp);
    }

    return v;
}



vector<Posn> Pawn::attack(const Grid& g) const {

    vector<Posn> v;
    Posn p = getPosn();
    Posn direction, tmp, passAttack;
    Piece* justMovedPawn = g.getJustMovedPawn();

    if (getColour() == Colour::White) direction = {-1, 0};
    else if (getColour() == Colour::Black) direction = {1, 0};

    direction = {direction.x, -1};
    tmp = p + direction;
    passAttack = tmp - Posn{direction.x, 0};

    if (tmp.x >= 0 && tmp.x < 8 && tmp.y >= 0 && tmp.y < 8 \
    && ((g.getTheGrid()[tmp.x][tmp.y] && g.getTheGrid()[tmp.x][tmp.y]->getColour() != getColour()) \
     || (justMovedPawn && justMovedPawn->getColour() != getColour() && justMovedPawn->getPosn() == passAttack))) {
        v.emplace_back(tmp);
    }

    direction = {direction.x, 1};
    tmp = p + direction;
    passAttack = tmp - Posn{direction.x, 0};

    if (tmp.x >= 0 && tmp.x < 8 && tmp.y >= 0 && tmp.y < 8 \
    && ((g.getTheGrid()[tmp.x][tmp.y] && g.getTheGrid()[tmp.x][tmp.y]->getColour() != getColour()) \
     || (justMovedPawn && justMovedPawn->getColour() != getColour() && justMovedPawn->getPosn() == passAttack))) {
        v.emplace_back(tmp);
    }

    return v;
}



bool Pawn::check(const Grid& g, Posn dest) {

    Posn p = getPosn();
    Posn direction;

    if (getColour() == Colour::White) direction = {-1, 0};
    else if (getColour() == Colour::Black) direction = {1, 0};

    return dest - p == Posn{direction.x, -1} || dest - p == Posn{direction.x, 1};


}

