#ifndef _AI3_H_
#define _AI3_H_
#include "ai1.h"


class AI3 : public AI {


    int eval(const Grid&g, Colour colour);

public:
    AI3(bool b): AI {b} {}

    Info suggestMove(const Grid& ori, Colour colour, int step);
};


#endif

