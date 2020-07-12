#ifndef _GRAPHICSDISPLAY_H_
#define _GRAPHICSDISPLAY_H_
#include "grid.h"
#include <vector>
#include "piece.h"
#include "window.h"


class GraphicsDisplay {
    Xwindow window;

public:

    GraphicsDisplay();

    void notify(std::vector<std::vector<Piece*>> theGrid, Posn p);

    void clean();

    void notifyFeatures(bool f[]);

};

#endif
