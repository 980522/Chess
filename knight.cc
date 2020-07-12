#include "knight.h"
#include <cstddef>
#include <iostream>
using namespace std;

Knight::Knight(Posn posn, Colour colour): Piece(posn, colour) {setType('n');}

void Knight::move(const Grid& g, Posn dest) {

    Posn p = getPosn();
    Posn direction = dest - p;
    if (direction.x * direction.y != -2 && direction.x * direction.y != 2)\
     throw "Destination error: wrong direction.";

    if (!g.getTheGrid()[dest.x][dest.y] || g.getTheGrid()[dest.x][dest.y]->getColour() != getColour()) return;

    else throw "Destination error: destination is ally.";

}

vector<Posn> Knight::amove(const Grid& g) const {

    Posn p = getPosn();
    vector<Posn> v;
    Posn startDirection {-2, -1};
    Posn direction {startDirection};
    int i {0};
    Posn tmp {p};
    while (i < 4) {
        tmp = p + direction;
        if (tmp.x < 0 || tmp.x > 7 || tmp.y < 0 || tmp.y > 7) {
            direction.clockturn(90);
            i++;
            continue;
        }
        if (!g.getTheGrid()[tmp.x][tmp.y]) v.emplace_back(tmp);
        else if (g.getTheGrid()[tmp.x][tmp.y]->getColour() != getColour()) v.emplace_back(tmp);
        direction.clockturn(90);
        i++;
    }
    startDirection = {-2, 1};
    direction = startDirection;
    i = 0;
    while (i < 4) {
        tmp = p + direction;
        if (tmp.x < 0 || tmp.x > 7 || tmp.y < 0 || tmp.y > 7) {
            direction.clockturn(90);
            i++;
            continue;
        }
        if (!g.getTheGrid()[tmp.x][tmp.y]) v.emplace_back(tmp);
        else if (g.getTheGrid()[tmp.x][tmp.y]->getColour() != getColour()) v.emplace_back(tmp);
        direction.clockturn(90);
        i++;
    }
    return v;
}


vector<Posn> Knight::attack(const Grid& g) const {

    Posn p = getPosn();
    vector<Posn> v;
    Posn startDirection {-2, -1};
    Posn direction {startDirection};
    int i {0};
    Posn tmp {p};
    
    while (i < 4) {
        tmp = p + direction;
        if (tmp.x < 0 || tmp.x > 7 || tmp.y < 0 || tmp.y > 7) {
            direction.clockturn(90);
            i++;
            continue;
        }
        if (!g.getTheGrid()[tmp.x][tmp.y]) {
            direction.clockturn(90);
            i++;
            continue;
        }
        if (g.getTheGrid()[tmp.x][tmp.y]->getColour() != getColour()) v.emplace_back(tmp);
        direction.clockturn(90);
        i++;
    }

    startDirection = {-2, 1};
    direction = startDirection;
    i = 0;
    while (i < 4) {
        tmp = p + direction;
        if (tmp.x < 0 || tmp.x > 7 || tmp.y < 0 || tmp.y > 7) {
            direction.clockturn(90);
            i++;
            continue;
        }
        if (!g.getTheGrid()[tmp.x][tmp.y]) {
            direction.clockturn(90);
            i++;
            continue;
        }
        if (g.getTheGrid()[tmp.x][tmp.y]->getColour() != getColour()) v.emplace_back(tmp);
        direction.clockturn(90);
        i++;
    }
    return v;
}


bool Knight::check(const Grid& g, Posn dest) {

    Posn p = getPosn();

    Posn direction = dest - p;
    return (direction.x * direction.y == -2 || direction.x * direction.y == 2);

}

