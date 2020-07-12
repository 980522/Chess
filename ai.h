#ifndef _AI_H_
#define _AI_H_
#include "piece.h"
#include "grid.h"
#include "info.h"
#include "posn.h"
#include <vector>
#include <string>
#include <iostream>
#include <map>


class AI {

protected:

    bool openningMove;
    std::map<Colour, std::vector<Info>> Spanish_opening;
    std::map<char, int> exist;
    std::map<char, int> attack;
    std::map<char, int> move;
    std::string t[4] {"Q", "R", "B", "N"};
    
public:
    AI(bool b) {
        openningMove = b;
        Info i1{6, 4, 4, 4};
        Spanish_opening[Colour::White].emplace_back(i1);
        Info i2{7, 6, 5, 5};
        Spanish_opening[Colour::White].emplace_back(i2);
        Info i3{7, 5, 3, 1};
        Spanish_opening[Colour::White].emplace_back(i3);
        Info i4{1, 4, 3, 4};
        Spanish_opening[Colour::Black].emplace_back(i4);
        Info i5{0, 1, 2, 2};
        Spanish_opening[Colour::Black].emplace_back(i5);
        Info i6{0, 5, 3, 2};
        Spanish_opening[Colour::Black].emplace_back(i6);

        exist['k'] = 100000;
        exist['q'] = 90000;
        exist['r'] = 80000;
        exist['b'] = 80000;
        exist['n'] = 70000;
        exist['p'] = 20000;

        attack['k'] = 1000;
        attack['q'] = 900;
        attack['r'] = 800;
        attack['b'] = 800;
        attack['n'] = 700;
        attack['p'] = 200;

        move['k'] = 6;
        move['q'] = 5;
        move['r'] = 4;
        move['b'] = 4;
        move['n'] = 3;
        move['p'] = 1;

    }

};


#endif
