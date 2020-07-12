#ifndef _TEXTDISPLAY_H_
#define _TEXTDISPLAY_H_
#include "grid.h"
#include <vector>
#include "piece.h"


class TextDisplay {
    std::vector<std::vector<char>> theDisplay;
    int size = 8;

public:

    TextDisplay();

    void clean();
    void notify(std::vector<std::vector<Piece*>> theGrid, Posn p);

    friend std::ostream& operator<< (std::ostream& out, const TextDisplay& d);

};

#endif


