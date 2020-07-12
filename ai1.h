#ifndef _AI1_H_
#define _AI1_H_
#include "ai.h"


class AI1 : public AI {

public:

    AI1(bool b): AI {b} {}
    Info suggestMove(const Grid& ori, Colour colour, int step) {

        Grid g {ori};
        std::vector<Info> infoArray;
        std::vector<Piece*> myPiece = g.getAllPiece()[colour];
        Info info;

        for (auto i : myPiece) {
            for (auto j : i->moveable(g)) {
                if (i->getType() == 'p' && (j.x == 0 || j.x == 7)) {
                    info = Info(i->getPosn(), j, true, false, false, false, false, t[rand() % 4]);
                    infoArray.emplace_back(info);
                }
                else  {
                    info = Info(i->getPosn(), j);
                    infoArray.emplace_back(info);
                }
            }
        }

        int n;
        while (true) {
            n = rand() % infoArray.size();
            try {g.movePiece(infoArray[n], colour);}
            catch (char const* c) {g = ori; continue;}
            break;
        }
        return infoArray[n];
    }
};


#endif
