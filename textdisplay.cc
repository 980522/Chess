#include "textdisplay.h"
#include <iostream>
using namespace std;



TextDisplay::TextDisplay()  {
    theDisplay = vector<vector<char>>();
    vector<char> tmp;
    for (int i {0}; i < size; i++) {
        tmp = vector<char>();
        for (int j {0}; j < size; j++) {
            if ((i + j) % 2) {tmp.emplace_back('-');}
            else if (!((i + j) % 2)) {tmp.emplace_back(' ');}
        }
        theDisplay.emplace_back(tmp);
    }

    theDisplay[7][0] = 'R';
    theDisplay[7][7] = 'R';
    theDisplay[7][1] = 'N';
    theDisplay[7][6] = 'N';
    theDisplay[7][2] = 'B';
    theDisplay[7][5] = 'B';
    theDisplay[7][3] = 'Q';
    theDisplay[7][4] = 'K';
    theDisplay[6][0] = 'P';
    theDisplay[6][1] = 'P';
    theDisplay[6][2] = 'P';
    theDisplay[6][3] = 'P';
    theDisplay[6][4] = 'P';
    theDisplay[6][5] = 'P';
    theDisplay[6][6] = 'P';
    theDisplay[6][7] = 'P';

    theDisplay[0][0] = 'r';
    theDisplay[0][7] = 'r';
    theDisplay[0][1] = 'n';
    theDisplay[0][6] = 'n';
    theDisplay[0][2] = 'b';
    theDisplay[0][5] = 'b';
    theDisplay[0][3] = 'q';
    theDisplay[0][4] = 'k';
    theDisplay[1][0] = 'p';
    theDisplay[1][1] = 'p';
    theDisplay[1][2] = 'p';
    theDisplay[1][3] = 'p';
    theDisplay[1][4] = 'p';
    theDisplay[1][5] = 'p';
    theDisplay[1][6] = 'p';
    theDisplay[1][7] = 'p';
}

void TextDisplay::clean() {
    for (int i {0}; i < size; i++) {
        for (int j {0}; j < size; j++) {
            if ((i + j) % 2) {theDisplay[i][j] = '-';}
            else if (!((i + j) % 2)) {theDisplay[i][j] = ' ';}
        }
    }
}



void TextDisplay::notify(std::vector<std::vector<Piece*>> theGrid, Posn i) {
    char type;
    Colour c;
    if (!theGrid[i.x][i.y]) {
        if ((i.x + i.y) % 2) {type = '-';}
        else if (!((i.x + i.y) % 2)) {type = ' ';}
    }
    else {
        type = theGrid[i.x][i.y]->getType();
        c = theGrid[i.x][i.y]->getColour();
        if (c == Colour::White) type = type - 'a' + 'A';
    }
    theDisplay[i.x][i.y] = type;
}



ostream& operator<< (ostream& out, const TextDisplay& d) {
    int index = 0;
    for (auto &i : d.theDisplay) {
        out << 8-index << " ";
        for (auto j : i) {
            out << j;
        }
        out << endl;
        index++;
    }
    out << endl << "  abcdefgh";
    return out;
}

