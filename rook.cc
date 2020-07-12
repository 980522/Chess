#include "rook.h"
#include <vector>
#include <cstddef>
#include <iostream>
using namespace std;

Rook::Rook(Posn posn, Colour colour): Piece(posn, colour) {setType('r');}

void Rook::move(const Grid& g, Posn dest) {

    Posn p = getPosn();
    Posn direction;
    Posn copy {p};
    if (dest.x - p.x == 0 && dest.y < p.y) direction = {0, -1} ;
    else if (dest.x - p.x == 0 && dest.y > p.y) direction = {0, 1} ;
    else if (dest.y - p.y == 0 && dest.x < p.x) direction = {-1, 0} ;
    else if (dest.y - p.y == 0 && dest.x > p.x) direction = {1, 0} ;
    else throw "Destination error: wrong direction.";

    copy += direction;
    while (copy != dest) {
        if (g.getTheGrid()[copy.x][copy.y]) throw "Destination error: pass is blocked.";
        copy += direction;
    }

    if (!g.getTheGrid()[copy.x][copy.y] || g.getTheGrid()[copy.x][copy.y]->getColour() != getColour()) {
        return;
    }

    else throw "Destination error: destination is ally.";

}

vector<Posn> Rook::amove(const Grid& g) const {

    Posn p = getPosn();
    vector<Posn> v;
    Posn startDirection {0, 1};
    Posn direction {startDirection};

    int i {0};

    Posn tmp {p + direction};
    while (i < 4) {
        while (tmp.x >= 0 && tmp.x < 8 && tmp.y >= 0 && tmp.y < 8) {
            if (!g.getTheGrid()[tmp.x][tmp.y]) v.emplace_back(tmp);
            else if (g.getTheGrid()[tmp.x][tmp.y]->getColour() != getColour()) {
                v.emplace_back(tmp);
                break;
            }
            else break;
            tmp += direction;
        }
        direction.clockturn(90);
        tmp = p + direction;
        i++;
    }
    return v;
}


vector<Posn> Rook::attack(const Grid& g) const {

    Posn p = getPosn();
    vector<Posn> v;
    Posn startDirection {0, 1};
    Posn direction {startDirection};
    
    int i {0};

    Posn tmp {p + direction};
    while (i < 4) {
        while (tmp.x >= 0 && tmp.x < 8 && tmp.y >= 0 && tmp.y < 8) {
            if (!g.getTheGrid()[tmp.x][tmp.y]) {
                tmp += direction;
                continue;
            }
            else if (g.getTheGrid()[tmp.x][tmp.y]->getColour() != getColour()) {
                v.emplace_back(tmp);
                break;
            }
            else break;
        }
        direction.clockturn(90);
        tmp = p + direction;
        i++;
    }
    return v;
}

bool Rook::check(const Grid& g, Posn dest) {

    Posn p = getPosn();
    Posn direction;

    if (dest.x - p.x == 0 && dest.y < p.y) direction = {0, -1} ;
    else if (dest.x - p.x == 0 && dest.y > p.y) direction = {0, 1} ;
    else if (dest.y - p.y == 0 && dest.x < p.x) direction = {-1, 0} ;
    else if (dest.y - p.y == 0 && dest.x > p.x) direction = {1, 0} ;
    else return false;

    Posn copy {p};
    copy += direction;
    while (copy != dest) {
        if (g.getTheGrid()[copy.x][copy.y] \
        && (g.getTheGrid()[copy.x][copy.y]->isKing() &&\
        g.getTheGrid()[copy.x][copy.y]->getColour() != getColour())) {copy += direction; continue;}
        else if (g.getTheGrid()[copy.x][copy.y]) return false;
        copy += direction;
    }
    
    return true;

}
