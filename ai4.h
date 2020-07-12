#ifndef _AI4_H_
#define _AI4_H_
#include "ai3.h"



class AI4Node : public AI {

    Info info;
    Grid grid;
    AI4Node* kid1;
    AI4Node* kid2;
    Colour colour;
    int deepth;

    int eval(const Grid& g);
    friend class AI4;

public:

    AI4Node(Info info, const Grid& g, Colour colour): AI {false}, info {info}, grid {g}, 
        kid1 {nullptr}, kid2 {nullptr}, colour {colour}, deepth {0} {}

    ~AI4Node() {
        delete kid1;
        delete kid2;
    }

    int maxMark();

};

class AI4 : public AI {

    AI4Node* kid;

public:
    AI4(bool b): AI {b}, kid {nullptr} {}
    ~AI4() {delete kid;}

    Info suggestMove(const Grid& ori, Colour colour, int step);
};


#endif
