#include "ai3.h"
using namespace std;



int AI3::eval(const Grid& g, Colour colour) {

    int sum = 0;
    vector<Posn> mable;
    vector<Posn> aable;
    vector<Posn> attackedEnemy;
    vector<Posn> attackedMine;
    Colour enemy;
    
    bool b = false;

    vector<Piece*> myPiece = g.getAllPiece()[colour];
    if (colour == Colour::White) {enemy = Colour::Black;}
    else if (colour == Colour::Black) {enemy = Colour::White;}
    vector<Piece*> enemyPiece = g.getAllPiece()[enemy];

    for (auto piece : myPiece) {


        mable = piece->moveable(g);
        aable = piece->attackable(g);
        int move_size = mable.size();
        int att_size = aable.size();

        
        sum += move[piece->getType()] * (move_size - att_size);
        
        for(auto pos : aable) {
            for (auto i: attackedEnemy) {
                if (i == pos) {
                    b = true;
                    break;
                }
            }
            if (b) {continue;}
            Piece* curr_piece = g.getTheGrid()[pos.x][pos.y];
            sum += attack[curr_piece->getType()];
            attackedEnemy.emplace_back(pos);
        }
    }
    for (auto piece : myPiece) {
        sum += (exist[piece->getType()]);
    }
    b = false;
    for (auto piece : enemyPiece) {

        mable = piece->moveable(g);
        aable = piece->attackable(g);
        int move_size = mable.size();
        int att_size = aable.size();

        sum += move[piece->getType()] * (move_size - att_size) * -1;
        
        for(auto pos : aable) {
            for (auto i: attackedMine) {
                if (i == pos) {
                    b = true;
                    break;
                }
            }
            if (b) {continue;}
            Piece* curr_piece = g.getTheGrid()[pos.x][pos.y];
            if (curr_piece) {sum += attack[curr_piece->getType()] * -100;}
            else {sum += attack['p'] * -100;}
            attackedMine.emplace_back(pos);
        }
    }
    for (auto piece : enemyPiece) {
        sum += (exist[piece->getType()] * -1);
    }

    return sum;
}


Info AI3::suggestMove(const Grid& ori, Colour colour, int step) {

    Grid g {ori};
    bool b = true;
    if (openningMove && step < 3) {
        try {g.movePiece(Spanish_opening[colour][step], colour);}
        catch (char const* c) {b = false;}
        if (b) return Spanish_opening[colour][step];
    }

    AI1 ai1(openningMove);
    std::vector<Info> infoArray;
    std::vector<Piece*> myPiece = g.getAllPiece()[colour];
    Info info;

    for (auto i : myPiece) {
        for (auto j : i->moveable(g)) {
            if (i->getType() == 'p' && (j.x == 0 || j.x == 7)) {
                for (int n {0}; n < 4; n++) {
                    info = Info(i->getPosn(), j, true, false, false, false, false, t[rand() % 4]);
                    infoArray.emplace_back(info);
                }
            }
            else  {
                info = Info(i->getPosn(), j);
                infoArray.emplace_back(info);
            }
        }
    }


    int mark;
    int maxmark = -1000000;
    int index = 0;
    int maxindex = -1;

    for (auto info : infoArray) {
        try {g.movePiece(info, colour);}
        catch (char const* c) {g = ori; index++; continue;}
        
        mark = eval(g, colour);

        if (maxmark < mark) {
            maxindex = index;
            maxmark = mark;
        }
        index++;
        g = ori;
    }

    if (maxindex == -1) {return ai1.suggestMove(ori, colour, step);}
    return infoArray[maxindex];
}

