#include "ai4.h"
using namespace std;



int AI4Node::eval(const Grid& g) {

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
            if (curr_piece) {sum += attack[curr_piece->getType()];}
            else {sum += attack['p'];}
            attackedEnemy.emplace_back(pos);
        }
    }

    b = false;
    for (auto piece : myPiece) {
        sum += (exist[piece->getType()]);
    }

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


int AI4Node::maxMark() {

    int mymark = eval(grid);

    if (deepth == 3) return mymark;

    AI3 ai3(openningMove);

    Grid g {grid};
    int side {0};
    
    Colour enemyColour;
    if (colour == Colour::White) {
        enemyColour = Colour::Black;
        side = -1;
    }
    else if (colour == Colour::Black) {
        enemyColour = Colour::White;
        side = 1;
    }

    int won = g.whoWon(enemyColour);

    if (won == side * -2) {
        return -10000000;
    }
    else if (won == 3) {
        return 0;
    }

    std::vector<Info> infoArray;
    std::vector<Piece*> myPiece = g.getAllPiece()[colour];
    Info tmpinfo;


    for (auto i : myPiece) {

            for (auto j : i->moveable(g)) {
            if (i->getType() == 'p' && (j.x == 0 || j.x == 7)) {
                for (int n {0}; n < 4; n++) {
                    tmpinfo = Info(i->getPosn(), j, true, false, false, false, false, t[rand() % 4]);
                    infoArray.emplace_back(tmpinfo);
                }
            }
            else  {
                tmpinfo = Info(i->getPosn(), j);
                infoArray.emplace_back(tmpinfo);
            }
        }
    }

    int mark;
    int maxmark1 = -10000000;
    int maxmark2 = -10000000;

    Info info1 = Info(-1,-1,-1,-1);
    Info info2 = Info(-1,-1,-1,-1);

    for (auto tmp : infoArray) {
        try {g.movePiece(tmp, colour);}
        catch (char const* c) {
            g = grid; 
            continue;}

        mark = eval(g);

        if (maxmark1 <= maxmark2) {

            if (mark >= maxmark1) {
                maxmark1 = mark;
                info1 = tmp;
            }
        }

        else  {
            
            if (mark >= maxmark2) {
                maxmark2 = mark;
                info2 = tmp;
            }
        }

        g = grid;
    }

    
    g.movePiece(info1, colour);

    won = g.whoWon(colour);

    if (won == side * 2) {
        if (info.p.x == -1) {
            info = info1;
        }
        return 10000000;
    }
    else if (won == 3) {
        if (info.p.x == -1) {
            info = info1;
        }
        return 0;
    }

    Info info3 {ai3.suggestMove(g, enemyColour, 3)};
    g.movePiece(info3, enemyColour);
    kid1 = new AI4Node(info1, g, colour);
    kid1->deepth = deepth+1;
    

    if (info2.p.x != -1) {
        g = grid;
        g.movePiece(info2, colour);

        won = g.whoWon(colour);

        if (won == side * 2) {
            if (info.p.x == -1) {
                info = info2;
            }
            return 10000000;
        }
        else if (won == 3) {
            if (info.p.x == -1) {
                info = info2;
            }
            return 0;
        }

        Info info4 {ai3.suggestMove(g, enemyColour, 3)};
        g.movePiece(info4, enemyColour);
        kid2 = new AI4Node(info2, g, colour);
        kid2->deepth = deepth+1;
    }

    int kid1mark;
    if (kid1) {kid1mark = kid1->maxMark();}
    else {kid1mark = -10000000;}
    int kid2mark;
    if (kid2) {kid2mark = kid2->maxMark();}
    else {kid2mark = -10000000;}

    if (kid1mark > kid2mark) {
        if (info.p.x == -1) {
            info = info1;
        }
        return kid1mark;
    }
    else {
        if (info.p.x == -1) {
            info = info2;
        }
        return kid2mark;
    }
}



Info AI4::suggestMove(const Grid& ori, Colour colour, int step) {

    Grid g {ori};
    bool b = true;
    if (openningMove && step < 3) {
        try {g.movePiece(Spanish_opening[colour][step], colour);}
        catch (char const* c) {b = false;}
        if (b) return Spanish_opening[colour][step];
    }

    AI4Node* k = new AI4Node(Info(-1, -1, -1, -1), g, colour);
    delete kid;
    kid = k;
    kid->maxMark();
    return kid->info;
}


