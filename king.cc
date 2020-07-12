#include "king.h"
#include <cstddef>
#include <iostream>
using namespace std;

King::King(Posn posn, Colour colour): Piece(posn, colour) {setType('k');}

void King::move(const Grid& g, Posn dest) {

    Posn p = getPosn();
    Posn direction = dest - p; 
    Posn tmp;
    int col = dest.x;
    int index;
    bool b = false;
    col = 0;
    vector<Piece*> enemy;

    if (getColour() == Colour::White) {enemy = g.getAllPiece()[Colour::Black]; col = 7;}
    else if (getColour() == Colour::Black) enemy = g.getAllPiece()[Colour::White];


    if (direction.x < 2 && direction.x > -2 && direction.y < 2 && direction.y > -2) {
 
    
        if (g.getTheGrid()[dest.x][dest.y] \
        && g.getTheGrid()[dest.x][dest.y]->getColour() == getColour())\
         throw "Destination error: destination is ally.";

        b = false;
        for (auto i : enemy) {
            b = b || i->checkKing(g, p + direction);
        }

        if (b) throw "King move error: destination is checked by enemy.";

    }

    else if (g.getSetted()) {return;}

    
    else if (direction == Posn{0, -2}) {

        if (!getNew()) throw "Castelling error: King is not new.";

        if (g.getTheGrid()[col][0] && g.getTheGrid()[col][0]->getNew()) {
            direction = {0, -1};
            tmp = p;
            index = 4;
            while (index > 0) {
                if (tmp != p && g.getTheGrid()[tmp.x][tmp.y]) \
                throw "Castelling error: pass is blocked.";
                b = false;
                if (index >= 2) {
                    for (auto i : enemy) {
                        b = b || i->checkKing(g, tmp);
                    }
                }

                if (b) throw "Castelling error: king is checked on the pass.";
                tmp += direction;
                index--;
            }
        }

        else throw "Castelling error: no new rook corresponds.";
    }

    else if (direction == Posn{0, 2}) {

        if (!getNew()) throw "Castelling error: King is not new.";

        if (g.getTheGrid()[col][7] && g.getTheGrid()[col][7]->getNew()) {
            direction = {0, 1};
            tmp = p;
            index = 3;
            while (index > 0) {
                if (tmp != p && g.getTheGrid()[tmp.x][tmp.y]) \
                throw "Castelling error: pass is blocked.";

                b = false;
                if (index >= 1) {
                    for (auto i : enemy) {
                        b = b || i->checkKing(g, tmp);
                    }
                }

                if (b) throw "Castelling error: king is checked on the pass.";
                tmp += direction;
                index--;
            }
        }

        else throw "Castelling error: no new rook corresponds.";
    }
    else throw "Destination error: wrong direction.";
}


vector<Posn> King::amove(const Grid& g) const {

    bool b = false;
    int col = 0;
    Posn p = getPosn();
    Posn direction, tmp;
    int index = 3;
    vector<Piece*> enemy;
    if (getColour() == Colour::White) {enemy = g.getAllPiece()[Colour::Black]; col = 7;}
    else if (getColour() == Colour::Black) enemy = g.getAllPiece()[Colour::White];

    vector<Posn> v;
    Posn startDirection {-1, -1};
    direction = startDirection;
    int i {0};

    while (i < 8) {

        tmp = p + direction;
        if (tmp.x < 0 || tmp.x > 7 || tmp.y < 0 || tmp.y > 7) {
            direction.clockturn(45);
            i++;
            continue;
        }
        if (g.getTheGrid()[tmp.x][tmp.y] && g.getTheGrid()[tmp.x][tmp.y]->getColour() == getColour()) {
            i++;
            direction.clockturn(45);
            continue;
        }

        b = false;
        for (auto i : enemy) {
            b = b || i->checkKing(g, tmp);
        }
        if (!b) v.emplace_back(tmp);

        direction.clockturn(45);
        i++;

    }

    if (g.getSetted() || !getNew()) return v;

    if (g.getTheGrid()[col][0] && g.getTheGrid()[col][0]->getNew()) {
        direction = {0, -1};
        tmp = p;
        index = 4;
        while (index > 0) {
            if (tmp == p) {b = false;}
            else  {b = g.getTheGrid()[tmp.x][tmp.y];}

            if (index >= 2) {
                for (auto i : enemy) {
                    b = b || i->checkKing(g, tmp);
                }
            }

            if (b) break;
            tmp += direction;
            index--;
        }
        if (!b) v.emplace_back(tmp - direction);
    }

    if (g.getTheGrid()[col][7] && g.getTheGrid()[col][7]->getNew()) {
        direction = {0, 1};
        tmp = p;
        index = 3;
        while (index > 0) {
            if (tmp == p) {b = false;}
            else {b = g.getTheGrid()[tmp.x][tmp.y];}

            if (index >= 1) {
                for (auto i : enemy) {
                    b = b || i->checkKing(g, tmp);
                }
            }

            if (b) break;
            tmp += direction;
            index--;
        }
        if (!b) v.emplace_back(tmp - direction);
    }

    return v;
}



vector<Posn> King::attack(const Grid& g) const {

    bool b = false;
    Posn p = getPosn();
    Posn direction, tmp;
    vector<Piece*> enemy;
    if (getColour() == Colour::White) {enemy = g.getAllPiece()[Colour::Black];}
    else if (getColour() == Colour::Black) enemy = g.getAllPiece()[Colour::White];

    vector<Posn> v;
    Posn startDirection {-1, -1};
    direction = startDirection;
    int i {0};

    while (i < 8) {

        tmp = p + direction;
        if (tmp.x < 0 || tmp.x > 7 || tmp.y < 0 || tmp.y > 7) {
            direction.clockturn(45);
            i++;
            continue;
        }
        if (!g.getTheGrid()[tmp.x][tmp.y]) {
            direction.clockturn(45);
            i++;
            continue;
        }
        if (g.getTheGrid()[tmp.x][tmp.y]->getColour() == getColour()) {
            direction.clockturn(45);
            i++;
            continue;
        }
        
        b = false;
        for (auto i : enemy) {
            b = b || i->checkKing(g, tmp);
        }

        if (!b) {v.emplace_back(tmp);}
        i++;
        direction.clockturn(45);

    }
    return v;
}



bool King::check(const Grid& g, Posn dest) {

    Posn p = getPosn();
    Posn direction = dest - p;
    return (direction.x < 2 && direction.x > -2 && direction.y < 2 && direction.y > -2);
}
