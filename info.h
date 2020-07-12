#ifndef _INFO_H_
#define _INFO_H_
#include "posn.h"
#include <string>

class Piece;

struct Info {
    Posn p;
    Posn dest;
    bool transferred;
    bool passAttack;
    bool castle;
    bool captured;
    bool newed;
    std::string type;
    Piece* justMovedPawn;


    Info() = default;

    Info(int x1, int y1, int x2, int y2, bool transferred = false,\
     bool passAttack = false, bool castle = false, bool captured = false, bool newed = false, std::string type = "0", Piece* justMovedPawn = nullptr): \
        p {Posn(x1, y1)}, dest {Posn(x2, y2)},\
        transferred {transferred},  passAttack {passAttack}, castle {castle}, captured {captured}, newed {newed}, type {type}, justMovedPawn {justMovedPawn} {}

    Info(Posn p, Posn dest, bool transferred = false, bool passAttack = false, bool castle = false, bool captured = false, \
    bool newed = false, std::string type = "0", Piece* justMovedPawn = nullptr): \
        p {p}, dest {dest}, transferred {transferred},\
        passAttack {passAttack}, castle {castle}, captured {captured}, newed {newed}, type {type}, justMovedPawn {justMovedPawn} {}

    Info& operator= (Info info) {
        Info tmp {info};
        std::swap(p, tmp.p);
        std::swap(dest, tmp.dest);
        std::swap(transferred, tmp.transferred);
        std::swap(passAttack, tmp.passAttack);
        std::swap(castle, tmp.castle);
        std::swap(captured, tmp.captured);
        std::swap(newed, tmp.newed);
        std::swap(type, tmp.type);
        std::swap(justMovedPawn, tmp.justMovedPawn);
        return *this;
    }

};

#endif
