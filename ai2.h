#ifndef _AI2_H_
#define _AI2_H_
#include "ai1.h"


class AI2 : public AI {


    int eval(const Grid&g, Colour colour);

public:
    AI2(bool b): AI {b} {}

    Info suggestMove(const Grid& ori, Colour colour, int step);
};


#endif

