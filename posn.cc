#include "posn.h"
#include <utility>
using namespace std;


Posn &Posn::operator= (const Posn& p) {
    x = p.x;
    y = p.y;
    return *this;
}

Posn& Posn::operator= (Posn&& p) {
    swap(x, p.x);
    swap(y, p.y);
    return *this;
}

Posn Posn::operator+ (const Posn& p) const {
    Posn tmp {0, 0};
    tmp.x = x + p.x;
    tmp.y = y + p.y;
    return tmp;
}

Posn Posn::operator- (const Posn& p) const {
    Posn tmp {0, 0};
    tmp.x = x - p.x;
    tmp.y = y - p.y;
    return tmp;
}

Posn& Posn::operator+= (const Posn& p) {
    x += p.x;
    y += p.y;
    return *this;
}

bool Posn::operator== (const Posn& p) const {
    return p.x == x && p.y == y;
}

bool Posn::operator!= (const Posn& p) const {
    return p.x != x || p.y != y;
}

void Posn::clockturn (int degree) {
    if (degree == 45) {
        if (x == 0 && y == -1) {
            x = -1;
        }
        else if (x == -1 && y == -1) {
            y = 0;
        }
        else if (x == -1 && y == 0) {
            y = 1;
        }
        else if (x == -1 && y == 1) {
            x = 0;
        }
        else if (x == 0 && y == 1) {
            x = 1;
        }
        else if (x == 1 && y == 1) {
            y = 0;
        }
        else if (x == 1 && y == 0) {
            y = -1;
        }
        else if (x == 1 && y == -1) {
            x = 0;
        }
    }
    else if (degree == 90) {
        swap(x, y);
        y = -y;
    }
}



