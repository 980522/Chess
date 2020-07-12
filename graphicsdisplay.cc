#include "graphicsdisplay.h"
#include <vector>
#include <iostream>
using namespace std;


GraphicsDisplay::GraphicsDisplay() {

    const string featuresName[6] {"Openning move", "Undo", \
    "Dynamic Input", "History", "Alarm", "Suggestion"};
    window.fillRectangle(0,0,500,500,Xwindow::Orange);
    window.drawLine(40, 40, 450, 40);
    window.drawLine(40, 40, 40, 450);
    window.drawLine(49, 49, 49, 449);
    window.drawLine(450, 50, 450, 450);
    window.drawLine(49, 49, 449, 49);
    window.drawLine(50, 450, 450, 450);
    window.drawBigString(200, 30, "Chess");
    
    string s;
    for (int i {0}; i < 8; i ++) {
        s = '8' - i;
        window.drawString(20, 80 + i * 50, s);
        s = 'a' + i;
        window.drawString(75 + i * 50, 465, s);
        for (int j {0}; j < 8; j ++) {
            if ((i+j) % 2 == 0) {
                window.fillRectangle(50+j*50,50+i*50,50,50,Xwindow::White);
            }
            else if ((i+j) % 2 == 1) {
                window.fillRectangle(50+j*50,50+i*50,50,50,Xwindow::Black);
            }

            if (i == 0 || i == 1) {
                window.fillCircle(75+50*j,75+50*i,45, Xwindow::White);
                window.fillCircle(75+50*j,75+50*i,43, Xwindow::Black);
                if (i == 0 && (j == 0 || j == 7)) {window.drawBigString(67+50*j,85+50*i,"r",Xwindow::White);}
                else if (i == 0 && (j == 1 || j == 6)) {window.drawBigString(67+50*j,85+50*i,"n",Xwindow::White);}
                else if (i == 0 && (j == 2 || j == 5)) {window.drawBigString(67+50*j,85+50*i,"b",Xwindow::White);}
                else if (i == 0 && j == 3) {window.drawBigString(67+50*j,85+50*i,"q",Xwindow::White);}
                else if (i == 0 && j == 4) {window.drawBigString(67+50*j,85+50*i,"k",Xwindow::White);}
                else if (i == 1) {window.drawBigString(67+50*j,85+50*i,"p",Xwindow::White);}
            }
            else if (i == 6 || i == 7) {
                window.fillCircle(75+50*j,75+50*i,45, Xwindow::Black);
                window.fillCircle(75+50*j,75+50*i,43, Xwindow::White);
                if (i == 7 && (j == 0 || j == 7)) {window.drawBigString(67+50*j,85+50*i,"R",Xwindow::Black);}
                else if (i == 7 && (j == 1 || j == 6)) {window.drawBigString(67+50*j,85+50*i,"N",Xwindow::Black);}
                else if (i == 7 && (j == 2 || j == 5)) {window.drawBigString(67+50*j,85+50*i,"B",Xwindow::Black);}
                else if (i == 7 && j == 3) {window.drawBigString(67+50*j,85+50*i,"Q",Xwindow::Black);}
                else if (i == 7 && j == 4) {window.drawBigString(67+50*j,85+50*i,"K",Xwindow::Black);}
                else if (i == 6) {window.drawBigString(67+50*j,85+50*i,"P",Xwindow::Black);}
            }
        }
    }

    for (int i {0}; i < 3; i++) {
        window.fillRectangle(160 * i + 20, 470, 10, 10, Xwindow::Red);
        window.drawString(160 * i + 35, 480, featuresName[i]);
    }
    for (int i {0}; i < 3; i++) {
        window.fillRectangle(160 * i + 20, 485, 10, 10, Xwindow::Red);
        window.drawString(160 * i + 35, 495, featuresName[i+3]);
    }

}

void GraphicsDisplay::notify(std::vector<std::vector<Piece*>> theGrid, Posn p) {
    string s;
    if ((p.x+p.y) % 2 == 0) {
        window.fillRectangle(50+p.y*50,50+p.x*50,50,50,Xwindow::White);
    }
    else if ((p.x+p.y) % 2 == 1) {
        window.fillRectangle(50+p.y*50,50+p.x*50,50,50,Xwindow::Black);
    }
    if (theGrid[p.x][p.y] && theGrid[p.x][p.y]->getColour() == Colour::White) {
        window.fillCircle(75+50*p.y,75+50*p.x,45, Xwindow::Black);
        window.fillCircle(75+50*p.y,75+50*p.x,43, Xwindow::White);
        s = theGrid[p.x][p.y]->getType() - 'a' + 'A';
        window.drawBigString(67+50*p.y,85+50*p.x,s,Xwindow::Black);
    }
    else if (theGrid[p.x][p.y] && theGrid[p.x][p.y]->getColour() == Colour::Black) {
        window.fillCircle(75+50*p.y,75+50*p.x,45, Xwindow::White);
        window.fillCircle(75+50*p.y,75+50*p.x,43, Xwindow::Black);
        s = theGrid[p.x][p.y]->getType();
        window.drawBigString(67+50*p.y,85+50*p.x,s,Xwindow::White);
    }
}

void GraphicsDisplay::clean() {
    for (int i {0}; i < 8; i ++) {
        for (int j {0}; j < 8; j ++) {
            if ((i+j) % 2 == 0) {
                window.fillRectangle(50+j*50,50+i*50,50,50,Xwindow::White);
            }
            else if ((i+j) % 2 == 1) {
                window.fillRectangle(50+j*50,50+i*50,50,50,Xwindow::Black);
            }
        }
    }   
}

void GraphicsDisplay::notifyFeatures(bool f[]) { 
    for (int i {0}; i < 3; i++) {
        if (f[i]) {window.fillRectangle(160 * i + 20, 470, 10, 10, Xwindow::Green);}
        else {window.fillRectangle(160 * i + 20, 470, 10, 10, Xwindow::Red);}
    }
    for (int i {3}; i < 6; i++) {
        if (f[i]) {window.fillRectangle(160 * (i-3) + 20, 485, 10, 10, Xwindow::Green);}
        else {window.fillRectangle(160 * (i-3) + 20, 485, 10, 10, Xwindow::Red);}
    }
}




