#include "grid.h"
#include <vector>
#include "piece.h"
#include "queen.h"
#include "king.h"
#include "pawn.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"
#include <map>
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include "score.h"
#include "history.h"
#include <iostream>
#include <string>
using namespace std;


// Helper function: erase Posn p from vector of Posn
void erase(vector<Posn>& v, Posn p) {
    int length = v.size();
    int pos = length;
    for(int i = 0; i < length; i ++) {
        if(v[i] == p){
            pos = i;
            break;
        }
    }

    for(int i = pos; i < length - 1; i ++) {
        v[i] = v[i + 1];
    }
    if(pos < length) v.pop_back();
}


// Helper function2: erase Piece* p from vector of Piece*
void erase(vector<Piece*>& v, Piece* p) {
    int length = v.size();
    int pos = length;
    for(int i = 0; i < length; i ++) {
        if(v[i] == p){
            pos = i;
            break;
        }
    }

    for(int i = pos; i < length - 1; i ++) {
        v[i] = v[i + 1];
    }
    if(pos < length) v.pop_back();
}

// Helper
string posn_to_cord(Posn pos) {
    char c1 = 'a' + pos.y;
    char c2 = '8' - pos.x;

    string s1{""};
    s1 += c1;
    string s2{""};
    s2 += c2;

    return s1+s2;
}

// Helper
bool my_in(vector<Posn> posns , Posn pos) {
    for(auto p : posns) {
        if(pos == p) return true;
    }
    return false;
}

// Helper
string posn_to_dnotation(Posn pos, Colour colour) {
    string first_part;
    string sec_part_black;
    string sec_part_white;
    if(pos.y == 0) first_part = "QR";
    else if (pos.y == 1) first_part = "QN";
    else if (pos.y == 2) first_part = "QB";
    else if (pos.y == 3) first_part = "Q";
    else if (pos.y == 4) first_part = "K";
    else if (pos.y == 5) first_part = "KB";
    else if (pos.y == 6) first_part = "KN";
    else if (pos.y == 7) first_part = "KR";
    else throw "Invalid Posn for descriptive notation.";

    if(pos.x == 0) sec_part_black = "1", sec_part_white = "8";
    else if (pos.x == 1) sec_part_black = "2", sec_part_white = "7";
    else if (pos.x == 2) sec_part_black = "3", sec_part_white = "6";
    else if (pos.x == 3) sec_part_black = "4", sec_part_white = "5";
    else if (pos.x == 4) sec_part_black = "5", sec_part_white = "4";
    else if (pos.x == 5) sec_part_black = "6", sec_part_white = "3";
    else if (pos.x == 6) sec_part_black = "7", sec_part_white = "2";
    else if (pos.x == 7) sec_part_black = "8", sec_part_white = "1";
    else throw "Invalid Posn for descriptive notation.";

    string white = first_part + sec_part_white;
    string black = first_part + sec_part_black;
    if (colour == Colour::Black) {return black;}
    return white;
}


Posn dnotation_to_posns(string d, Colour colour){
    Posn v;
    int x_black;
    int x_white;
    int y;
    int len = d.length();

    char last_bit = d[len - 1];

    if(last_bit == '1') x_black = 0, x_white = 7;
    else if (last_bit == '2') x_black = 1, x_white = 6;
    else if (last_bit == '3') x_black = 2, x_white = 5;
    else if (last_bit == '4') x_black = 3, x_white = 4;
    else if (last_bit == '5') x_black = 4, x_white = 5;
    else if (last_bit == '6') x_black = 5, x_white = 2;
    else if (last_bit == '7') x_black = 6, x_white = 1;
    else if (last_bit == '8') x_black = 7, x_white = 0;
    else throw "Invalid descriptive notation.";

    if(len == 3) {
        string first_bits = d.substr(0, 2);
        if (first_bits == "QR") y = 0;
        else if(first_bits == "QN") y = 1;
        else if(first_bits == "QB") y = 2;
        else if(first_bits == "KB") y = 5;
        else if(first_bits == "KN") y = 6;
        else if(first_bits == "KR") y = 7;
        else throw "Invalid descriptive notation.";
        Posn p_black = Posn{x_black, y};
        Posn p_white = Posn{x_white, y};
        if (colour == Colour::Black) {
            return p_black;
        } else {
            return p_white;
        }


    } else if (len == 2) {
        string first_bit = d.substr(0, 1);
        if(first_bit == "Q") {
            y = 3;
            Posn p_black = Posn{x_black, y};
            Posn p_white = Posn{x_white, y};
            if (colour == Colour::Black) {
                return p_black;
            } else {
                return p_white;
            }
        }
        else if (first_bit == "K") {
            y = 4;
            Posn p_black = Posn{x_black, y};
            Posn p_white = Posn{x_white, y};
            if (colour == Colour::Black) {
                return p_black;
            } else {
                return p_white;
            }
        }
        
        else throw "Invalid descriptive notation.";
    }
   
    return v;
}


Grid::Grid() {
    setted = false;

    // Set the default to theGrid
    for(int i = 0; i < 8; i ++) {
        vector<Piece*> v1;
        for(int j = 0; j < 8; j ++) {
            v1.emplace_back(nullptr);
        }
        theGrid.emplace_back(v1);
        defaultGrid.emplace_back(v1);
    }

    defaultGrid[0][0] = new Rook{Posn{0,0}, Colour::Black};
    defaultGrid[0][7] = new Rook{Posn{0,7}, Colour::Black};
    defaultGrid[0][1] = new Knight{Posn{0,1}, Colour::Black};
    defaultGrid[0][6] = new Knight{Posn{0,6}, Colour::Black};
    defaultGrid[0][2] = new Bishop{Posn{0,2}, Colour::Black};
    defaultGrid[0][5] = new Bishop{Posn{0,5}, Colour::Black};
    defaultGrid[0][3] = new Queen{Posn{0,3}, Colour::Black};
    defaultGrid[0][4] = new King{Posn{0,4}, Colour::Black};
    vector<Posn> b;
    b.emplace_back(Posn{0, 4});
    blackKingPosn = b;
    for(int i = 0; i < 8; i ++) {
        defaultGrid[1][i] = new Pawn{Posn{1,i}, Colour::Black};
        defaultGrid[6][i] = new Pawn{Posn{6,i}, Colour::White};
    }

    defaultGrid[7][0] = new Rook{Posn{7,0}, Colour::White};
    defaultGrid[7][7] = new Rook{Posn{7,7}, Colour::White};
    defaultGrid[7][1] = new Knight{Posn{7,1}, Colour::White};
    defaultGrid[7][6] = new Knight{Posn{7,6}, Colour::White};
    defaultGrid[7][2] = new Bishop{Posn{7,2}, Colour::White};
    defaultGrid[7][5] = new Bishop{Posn{7,5}, Colour::White};
    defaultGrid[7][3] = new Queen{Posn{7,3}, Colour::White};
    defaultGrid[7][4] = new King{Posn{7,4}, Colour::White};
    vector<Posn> w;
    w.emplace_back(Posn{7, 4});
    whiteKingPosn = w;

    // set allPieces
    vector<Piece*> black;
    vector<Piece*> white;
    for(int i = 0; i < 8; i ++) {
        black.emplace_back(defaultGrid[0][i]);
        black.emplace_back(defaultGrid[1][i]);
        white.emplace_back(defaultGrid[6][i]);
        white.emplace_back(defaultGrid[7][i]);
    }
    allPieces[Colour::Black] = black;
    allPieces[Colour::White] = white;

    justMovedPawn = nullptr;

    textDisplay = new TextDisplay();
    graphicsDisplay = new GraphicsDisplay();
    score = new Score();
    history = new History();
    gonePiece = vector<Piece*>();

}

Grid::~Grid() {
    for(int i = 0; i < 8; i ++) {
        for(int j = 0; j < 8; j ++) {
            delete defaultGrid[i][j];
            defaultGrid[i][j] = nullptr;
            theGrid[i][j] = nullptr;
        }
    }
    for(int i = 0; i < int(transferred.size()); i ++){
        delete transferred[i];
    }
    delete textDisplay;
    delete graphicsDisplay;
    delete score;
    delete history;
}


void Grid::setup() {
    setted = true;
    for(int i = 0; i < 8; i ++) {
        for(int j = 0; j < 8; j ++) {
            delete defaultGrid[i][j];
            defaultGrid[i][j] = nullptr;
            theGrid[i][j] = nullptr;
        }
    }
    textDisplay->clean();
    graphicsDisplay->clean();
    vector<Piece*> v1;
    vector<Piece*> v2;
    allPieces[Colour::Black] = v1;
    allPieces[Colour::White] = v2;
    vector<Posn> v3;
    vector<Posn> v4;
    whiteKingPosn = v3;
    blackKingPosn = v4;
    // pointers left as original

}


void Grid::insertPiece(std::string type, Posn p) {

    int black_len = allPieces[Colour::Black].size();
    int white_len = allPieces[Colour::White].size();


    // If there already exist a piece on Posn p
    if (defaultGrid[p.x][p.y]) {
        for (int i = 0; i < black_len; i++) {

            if (allPieces[Colour::Black][i] == defaultGrid[p.x][p.y]) {
                // If it is a Black King
                if(defaultGrid[p.x][p.y]->getType() == 'k') {
                    erase(blackKingPosn, p);
                }

                erase(allPieces[Colour::Black], defaultGrid[p.x][p.y]);
                break;
            }
        }
        for (int i = 0; i < white_len; i++) {
            if (allPieces[Colour::White][i] == defaultGrid[p.x][p.y]) {
                // If it is a White King
                if(defaultGrid[p.x][p.y]->getType() == 'k') {
                    erase(whiteKingPosn, p);
                }
                erase(allPieces[Colour::White], defaultGrid[p.x][p.y]);
                break;
            }
        }
        delete defaultGrid[p.x][p.y];
        defaultGrid[p.x][p.y] = nullptr;
    }


    if (type == "K") {
        defaultGrid[p.x][p.y] = new King{Posn{p.x, p.y}, Colour::White};
        theGrid[p.x][p.y] = new King{Posn{p.x, p.y}, Colour::White};
        allPieces[Colour::White].emplace_back(defaultGrid[p.x][p.y]);
        whiteKingPosn.emplace_back(Posn{p.x, p.y});
    } else if (type == "k") {
        defaultGrid[p.x][p.y] = new King{Posn{p.x, p.y}, Colour::Black};
        theGrid[p.x][p.y] = new King{Posn{p.x, p.y}, Colour::Black};
        allPieces[Colour::Black].emplace_back(defaultGrid[p.x][p.y]);
        blackKingPosn.emplace_back(Posn{p.x, p.y});
    } else if (type == "R") {
        defaultGrid[p.x][p.y] = new Rook{Posn{p.x, p.y}, Colour::White};
        theGrid[p.x][p.y] = new Rook{Posn{p.x, p.y}, Colour::White};
        allPieces[Colour::White].emplace_back(defaultGrid[p.x][p.y]);
    } else if (type == "r") {
        defaultGrid[p.x][p.y] = new Rook{Posn{p.x, p.y}, Colour::Black};
        theGrid[p.x][p.y] = new Rook{Posn{p.x, p.y}, Colour::Black};
        allPieces[Colour::Black].emplace_back(defaultGrid[p.x][p.y]);
    } else if (type == "N") {
        defaultGrid[p.x][p.y] = new Knight{Posn{p.x, p.y}, Colour::White};
        theGrid[p.x][p.y] = new Knight{Posn{p.x, p.y}, Colour::White};
        allPieces[Colour::White].emplace_back(defaultGrid[p.x][p.y]);
    } else if (type == "n") {
        defaultGrid[p.x][p.y] = new Knight{Posn{p.x, p.y}, Colour::Black};
        theGrid[p.x][p.y] = new Knight{Posn{p.x, p.y}, Colour::Black};
        allPieces[Colour::Black].emplace_back(defaultGrid[p.x][p.y]);
    } else if (type == "B") {
        defaultGrid[p.x][p.y] = new Bishop{Posn{p.x, p.y}, Colour::White};
        theGrid[p.x][p.y] = new Bishop{Posn{p.x, p.y}, Colour::White};
        allPieces[Colour::White].emplace_back(defaultGrid[p.x][p.y]);
    } else if (type == "b") {
        defaultGrid[p.x][p.y] = new Bishop{Posn{p.x, p.y}, Colour::Black};
        theGrid[p.x][p.y] = new Bishop{Posn{p.x, p.y}, Colour::Black};
        allPieces[Colour::Black].emplace_back(defaultGrid[p.x][p.y]);
    } else if (type == "Q") {
        defaultGrid[p.x][p.y] = new Queen{Posn{p.x, p.y}, Colour::White};
        theGrid[p.x][p.y] = new Queen{Posn{p.x, p.y}, Colour::White};
        allPieces[Colour::White].emplace_back(defaultGrid[p.x][p.y]);
    } else if (type == "q") {
        defaultGrid[p.x][p.y] = new Queen{Posn{p.x, p.y}, Colour::Black};
        theGrid[p.x][p.y] = new Queen{Posn{p.x, p.y}, Colour::Black};
        allPieces[Colour::Black].emplace_back(defaultGrid[p.x][p.y]);
    } else if (type == "P") {
        defaultGrid[p.x][p.y] = new Pawn{Posn{p.x, p.y}, Colour::White};
        theGrid[p.x][p.y] = new Pawn{Posn{p.x, p.y}, Colour::White};
        allPieces[Colour::White].emplace_back(defaultGrid[p.x][p.y]);
    } else if (type == "p") {
        defaultGrid[p.x][p.y] = new Pawn{Posn{p.x, p.y}, Colour::Black};
        theGrid[p.x][p.y] = new Pawn{Posn{p.x, p.y}, Colour::Black};
        allPieces[Colour::Black].emplace_back(defaultGrid[p.x][p.y]);
    }
    else throw "Setup error: there is no such type of piece.";
    textDisplay->notify(defaultGrid, p);
    graphicsDisplay->notify(defaultGrid, p);
}


void Grid::deletePiece(Posn p) {
    if(!defaultGrid[p.x][p.y]) return;

    if(defaultGrid[p.x][p.y]->getType() == 'k') {
        if(defaultGrid[p.x][p.y]->getColour() == Colour::Black) {
            erase(blackKingPosn, p);
        } else {
            erase(whiteKingPosn, p);
        }
    }

    erase(allPieces[Colour::Black], defaultGrid[p.x][p.y]);
    erase(allPieces[Colour::White], defaultGrid[p.x][p.y]);

    delete defaultGrid[p.x][p.y];
    defaultGrid[p.x][p.y] = nullptr;
    textDisplay->notify(defaultGrid, p);
    graphicsDisplay->notify(defaultGrid, p);
}


bool Grid::setupCheck() {
    // check the number of king of both sides

    if (whiteKingPosn.size() != 1 || blackKingPosn.size() != 1) {return false;}


    for(int i = 0; i < 8; i+=7) {
        for(int j = 0; j < 8; j ++) {

            if(i == 0) {
                // check if exists a pawn in first row
                if(defaultGrid[i][j] && defaultGrid[i][j]->getType() == 'p') {
                    return false;
                }
            }
            if(i == 7) {
                // check if exists a pawn in last row
                if(defaultGrid[i][j] && defaultGrid[i][j]->getType() == 'p') {
                    return false;
                }
            }

        }
    }


    //check if a king is in check
    int black_len = allPieces[Colour::Black].size();
    int white_len = allPieces[Colour::White].size();
    for(int i = 0; i < black_len; i ++) {
        if(allPieces[Colour::Black][i]->checkKing(*this, whiteKingPosn[0])){
            return false;
        }
    }
    for(int i = 0; i < white_len; i ++) {
        if(allPieces[Colour::White][i]->checkKing(*this, blackKingPosn[0])){
            return false;
        }
    }
    return true;
}

// Initialize the theGrid ONLY
void Grid::init() {
    vector<Piece*> v1;
    vector<Piece*> v2;
    allPieces[Colour::Black] = v1;
    allPieces[Colour::White] = v2;
    vector<Posn> v3;
    vector<Posn> v4;
    whiteKingPosn = v3;
    blackKingPosn = v4;
    for (auto p : transferred) {
        delete p;
    }
    transferred = vector<Piece*>();
    justMovedPawn = nullptr;
    gonePiece = vector<Piece*>();
    delete history;
    history = new History();
    history->update(Info{0, 0, 0, -1}, theGrid, "Start:", "Start:");


    for(int i = 0; i < 8; i ++) {
        for(int j = 0; j < 8; j ++) {
            Piece* curr = defaultGrid[i][j];
            theGrid[i][j] = curr;
            if(curr){
                curr->setPosn(Posn{i, j});
                if (textDisplay) {curr->setNew(true);}
                if (curr->getColour() == Colour::Black) {
                    allPieces[Colour::Black].emplace_back(curr);
                }
                else if (curr->getColour() == Colour::White) {
                    allPieces[Colour::White].emplace_back(curr);
                }
            }
            if(curr && curr->getType() == 'k') {
                if(curr->getColour() == Colour::Black) {
                    blackKingPosn.emplace_back(Posn{i, j});
                } else {
                    whiteKingPosn.emplace_back(Posn{i, j});
                }
            }
            if (textDisplay) {
                textDisplay->notify(theGrid, Posn(i,j));
                graphicsDisplay->notify(theGrid, Posn(i,j));
            }
        }
    }

}


string Grid::to_alg_notation(Info cmd) const{
    Posn p = cmd.p;
    Posn dest = cmd.dest;

    char type;
    char transferred_to;
    vector<vector<Piece*>> currGrid = theGrid;

    string s = "";
    if(p.x == -1){
        s = "0-1";
        return s;
    }
    if(p.y == -1){
        s = "1-0";
        return s;
    }
    if(dest.x == -1){
        s = "1/2 - 1/2";
        return s;
    }


    Colour my_colour = currGrid.at(dest.x).at(dest.y)->getColour();
    Colour enemy_colour;
    Posn opp_king_pos;
    if(my_colour == Colour::Black) {
        enemy_colour = Colour :: White;
        opp_king_pos = whiteKingPosn[0];
    } else {
        enemy_colour = Colour ::Black;
        opp_king_pos = blackKingPosn[0];
    }


    if(cmd.castle) {
        if (dest.y - p.y == 2) {s = "0-0";}
        else {s = "0-0-0";}
        return s;
    }

    if(cmd.transferred) {
        type = 'p';
        transferred_to = currGrid.at(dest.x).at(dest.y)->getType();
        transferred_to = transferred_to - 'a' + 'A';
        s = posn_to_cord(dest) + "=" + transferred_to;
        bool check_king = false;
        bool can_escape = false;
        for(auto piece : allPieces.at(my_colour)) {
            if(piece -> checkKing(*this, opp_king_pos)) {check_king = true; break;}
        }
        if(check_king) {
            for(auto piece : allPieces.at(enemy_colour)) {
                Posn pos = piece->getPosn();
                vector<Posn> movable = theGrid.at(pos.x).at(pos.y) -> moveable(*this);
                if (movable.size() != 0) {can_escape = true;}
            }

            if(can_escape) {s += "+";}
            else {s += "#";}
        }
        return s;
    }


    type = currGrid.at(dest.x).at(dest.y)->getType();

    // check ambiguity
    bool ambiguity = false;
    vector<Posn> amb_piece_pos;

    for(auto piece : allPieces.at(my_colour)) {
        vector<Posn> movable = piece->moveable(*this);
        if(piece->getType() == type && my_in(movable, dest)) {
            ambiguity = true;
            amb_piece_pos.emplace_back(piece->getPosn());
        }
    }

    type = type - 'a' + 'A';
    string t {""};
    if (type != 'P') {t += type;}
    s += t;



    if(ambiguity) {
        string my_pos = posn_to_cord(p);
        char my_file = my_pos[0];
        char my_rank = my_pos[1];

        bool repeat_file = false;
        bool repeat_rank = false;

        for(auto pos : amb_piece_pos) {
            if (pos.x == p.x) repeat_rank = true;
            if (pos.y == p.y) repeat_file = true;
        }

        if(!repeat_file) {
            s += my_file;
        } else if (!repeat_rank) {
            s += my_rank;
        } else {
            s += my_file;
            s += my_rank;
        }

    }

    if(cmd.captured) {s += "x";}
    s += posn_to_cord(dest);

    bool check_king = false;
    bool can_escape = false;
    for(auto piece : allPieces.at(my_colour)) {
        if(piece -> checkKing(*this, opp_king_pos)) {check_king = true; break;}
    }
    if(check_king) {
        for(auto piece : allPieces.at(enemy_colour)) {
            Posn pos = piece->getPosn();
            vector<Posn> movable = theGrid.at(pos.x).at(pos.y) -> moveable(*this);
            if (movable.size() != 0) {can_escape = true;}
        }

        if(can_escape) {s += "+";}
        else {s += "#";}
    }

    return s;
}

string Grid::to_des_notation(Info cmd) const {
    Posn p = cmd.p;
    Posn dest = cmd.dest;

    char type;
    char transferred_to;
    vector<vector<Piece *>> currGrid = theGrid;

    string s {""};
    if (p.x == -1) {
        s = "0-1";
        return s;
    }
    if (p.y == -1) {
        s = "1-0";
        return s;
    }
    if (dest.x == -1) {
        s = "1/2 - 1/2";
        return s;
    }

    Colour my_colour = currGrid.at(dest.x).at(dest.y)->getColour();
    Colour enemy_colour;
    Posn opp_king_pos;
    if (my_colour == Colour::Black) {
        enemy_colour = Colour::White;
        opp_king_pos = whiteKingPosn[0];
    } else {
        enemy_colour = Colour::Black;
        opp_king_pos = blackKingPosn[0];
    }


    if (cmd.castle) {
        if (dest.y - p.y == 2) { s = "O-O"; }
        else { s = "O-O-O"; }
        return s;
    }

    if (cmd.transferred) {
        string type = "P-";
        transferred_to = currGrid.at(dest.x).at(dest.y)->getType();
        transferred_to = transferred_to - 'a' + 'A';
        s = type + posn_to_dnotation(dest, my_colour) + "=" + transferred_to;
        bool check_king = false;
        bool can_escape = false;
        for(auto piece : allPieces.at(my_colour)) {
            if(piece -> checkKing(*this, opp_king_pos)) {check_king = true; break;}
        }
        if(check_king) {
            for(auto piece : allPieces.at(enemy_colour)) {
                Posn pos = piece->getPosn();
                vector<Posn> movable = theGrid.at(pos.x).at(pos.y) -> moveable(*this);
                if (movable.size() != 0) {can_escape = true;}
            }

            if(can_escape) {s += "+";}
            else {s += "#";}
        }
        return s;
    }

    if (cmd.passAttack) {
        s += "e.p.PxP";
        return s;
    }

    type = currGrid.at(dest.x).at(dest.y)->getType();
    type = type - 'a' + 'A';
    string prev_p_dno = posn_to_dnotation(p, my_colour);
    string dest_dno = posn_to_dnotation(dest, my_colour);
    prev_p_dno = prev_p_dno.substr(0, 2);

    if (cmd.captured) {

        Piece *captured_piece = gonePiece.back();
        char captured_piece_type = captured_piece->getType();
        captured_piece_type = captured_piece_type - 'a' + 'A';
        s = prev_p_dno + type + "x" + captured_piece_type;
        return s;
    }


    // Normal move without capture
    s += type;
    s += "-";
    s += dest_dno;

    bool check_king = false;
    bool can_escape = false;
    for(auto piece : allPieces.at(my_colour)) {
        if(piece -> checkKing(*this, opp_king_pos)) {check_king = true; break;}
    }
    if(check_king) {
        for(auto piece : allPieces.at(enemy_colour)) {
            Posn pos = piece->getPosn();
            vector<Posn> movable = theGrid.at(pos.x).at(pos.y) -> moveable(*this);
            if (movable.size() != 0) {can_escape = true;}
        }

        if(can_escape) {s += "+";}
        else {s += "#";}
    }

    return s;

}

void Grid::movePiece(Info info, Colour colour) {

    // Info for notify history
    bool trans = false;
    bool passAttack = false;
    bool castle = false;
    bool captured = false;
    string type = "0";


    Posn p = info.p;
    Posn dest = info.dest;

    Piece* curr = theGrid[p.x][p.y];
    if(!curr) {throw "There is no piece on this position.";}

    Colour color1 = curr->getColour();

    if(color1 != colour) {throw "That is not your piece.";}

    Colour color2 = Colour::NoColour;
    if(theGrid[dest.x][dest.y]) {
        color2 = theGrid[dest.x][dest.y]->getColour();
    }

    if (color1 == color2) {throw "Conflict with your own piece.";}

    // 1. Check if it is a valid move
    try{
        curr->movePiece(*this, dest);
    } catch (char const* err){
        throw err;
    }

    Piece* this_piece = theGrid[p.x][p.y];
    Piece* dest_piece = theGrid[dest.x][dest.y];

    bool this_new = this_piece->getNew();
    bool dest_new = false;

    Piece* eaten_pawn = nullptr;
    Posn eaten_pawn_pos;

    Piece* new_piece = nullptr;


    Piece* cas_king = nullptr;
    Piece* cas_rook = nullptr;
    Posn cas_king_pos;
    Posn cas_rook_pos;
    Posn king_finish_pos;
    Posn rook_finish_pos;

    // 2. Capture opponents if exist
    if(dest_piece) {
        captured = true;
        gonePiece.emplace_back(dest_piece);
        dest_new = dest_piece->getNew();
        erase(allPieces[dest_piece->getColour()], dest_piece);
        if (curr->getType() == 'k') {
            if(colour == Colour::Black) {
                blackKingPosn[0] = dest;
            } else {
                whiteKingPosn[0] = dest;
            }
        }
    }


    // 3. Check if a pawn reaches end of opposite bottom line
    //     Move and ask for a new input
    if(curr->getType() == 'p' && (dest.x == 0 || dest.x == 7)) {
        gonePiece.emplace_back(theGrid[p.x][p.y]);
        trans = true;
        theGrid[p.x][p.y] = nullptr;
        string s;
        while(true) {
            if(info.transferred) {
                s = info.type;
            } else {
                cin >> s;
            }

            if (s == "Q") {
                new_piece = new Queen{dest, colour};
            } else if (s == "R") {
                new_piece = new Rook{dest, colour};
            } else if (s == "B") {
                new_piece = new Bishop{dest, colour};
            } else if (s == "N") {
                new_piece = new Knight{dest, colour};
            } else {continue;}
            type = s;
            transferred.emplace_back(new_piece);
            theGrid[dest.x][dest.y] = new_piece;
            theGrid[dest.x][dest.y]->setNew(false);
            theGrid[dest.x][dest.y]->setPosn(dest);
            theGrid[p.x][p.y] = nullptr;
            if (colour == Colour::White) {
                allPieces[Colour::White].emplace_back(new_piece);
                erase(allPieces[Colour::White], this_piece);
            } else {
                allPieces[Colour::Black].emplace_back(new_piece);
                erase(allPieces[Colour::Black], this_piece);
            }
            justMovedPawn = nullptr;
            break;
        }

        // 3. Castling
    } else if (!setted && curr->getType() == 'k' && dest.x == p.x && dest.y-p.y == 2) { //Move 2 steps right
        castle = true;
        cas_king = theGrid[p.x][4];
        cas_rook = theGrid[p.x][7];
        cas_king_pos = Posn{p.x, 4};
        cas_rook_pos = Posn{p.x, 7};
        king_finish_pos = Posn{p.x, 6};
        rook_finish_pos = Posn{p.x, 5};

        theGrid[p.x][5] = theGrid[p.x][7];
        theGrid[p.x][7] = nullptr;
        theGrid[p.x][5]->setNew(false);
        theGrid[p.x][5]->setPosn(Posn{p.x, 5});
        theGrid[p.x][6] = theGrid[p.x][4];
        theGrid[p.x][6]->setPosn(dest);
        theGrid[p.x][6]->setNew(false);
        theGrid[p.x][4] = nullptr;
        if(colour == Colour::Black) {
            blackKingPosn[0] = dest;
        } else {
            whiteKingPosn[0] = dest;
        }

    } else if (!setted && curr->getType() == 'k' && dest.y-p.y == -2) { //Move 2 steps left

        castle = true;
        cas_king = theGrid[p.x][4];
        cas_rook = theGrid[p.x][0];
        cas_king_pos = Posn{p.x, 4};
        cas_rook_pos = Posn{p.x, 0};
        king_finish_pos = Posn{p.x, 2};
        rook_finish_pos = Posn{p.x, 3};

        theGrid[p.x][3] = theGrid[p.x][0];
        theGrid[p.x][0] = nullptr;
        theGrid[p.x][3]->setNew(false);
        theGrid[p.x][3]->setPosn(Posn{p.x, 3});
        theGrid[p.x][2] = theGrid[p.x][4];
        theGrid[p.x][2]->setPosn(dest);
        theGrid[p.x][2]->setNew(false);
        theGrid[p.x][4] = nullptr;
        if(colour == Colour::Black) {
            blackKingPosn[0] = dest;
        } else {
            whiteKingPosn[0] = dest;
        }

        // 4. en passant
    } else if (curr->getType() == 'p' && abs(dest.x - p.x) == 1 && abs(dest.y - p.y) == 1) {
        captured = true;
        if (dest.y - p.y == 1 && justMovedPawn && theGrid[p.x][p.y + 1] == justMovedPawn) { // Move Right
            eaten_pawn = theGrid[p.x][p.y + 1];
            gonePiece.emplace_back(eaten_pawn);
            eaten_pawn_pos = Posn{p.x, p.y + 1};
            theGrid[p.x][p.y + 1] = nullptr;
            passAttack = true;

        } else if (dest.y - p.y == -1 && justMovedPawn && theGrid[p.x][p.y - 1] == justMovedPawn) { // Move left
            eaten_pawn = theGrid[p.x][p.y - 1];
            gonePiece.emplace_back(eaten_pawn);
            eaten_pawn_pos = Posn{p.x, p.y - 1};
            theGrid[p.x][p.y - 1] = nullptr;
            passAttack = true;
        }

        theGrid[dest.x][dest.y] = theGrid[p.x][p.y];
        theGrid[p.x][p.y] = nullptr;
        theGrid[dest.x][dest.y]->setPosn(dest);
        theGrid[dest.x][dest.y]->setNew(false);
        justMovedPawn = nullptr;
        if (colour == Colour::Black) {
            erase(allPieces[Colour::White], eaten_pawn);
        } else if (colour == Colour::White) {
            erase(allPieces[Colour::Black], eaten_pawn);
        }
    } else {
        // 5. Normal move
        theGrid[dest.x][dest.y] = curr;
        theGrid[dest.x][dest.y]->setPosn(dest);
        theGrid[p.x][p.y] = nullptr;
        if (curr->getType() == 'k') {
            if(colour == Colour::Black) {
                blackKingPosn[0] = dest;
            } else {
                whiteKingPosn[0] = dest;
            }
        }
    }


    // Determine whether king is in check after such move

    bool is_check = false;
    if (colour == Colour::White) {
        for(auto piece : allPieces[Colour::Black]) {
            if(piece->checkKing(*this, whiteKingPosn[0])){
                is_check = true;
                break;
            }
        }
    } else {
        for(auto piece : allPieces[Colour::White]) {
            if(piece->checkKing(*this, blackKingPosn[0])){
                is_check = true;
                break;
            }
        }
    }


    if(is_check) {
        theGrid[p.x][p.y] = this_piece;
        theGrid[dest.x][dest.y] = dest_piece;
        this_piece->setNew(this_new);

        // Pawn reach bottom line
        if(new_piece) {
            Piece* return_pawn = gonePiece.back();
            gonePiece.pop_back();
            allPieces[return_pawn->getColour()].emplace_back(return_pawn);
            erase(transferred, new_piece);
            if (colour == Colour::White) {
                erase(allPieces[Colour::White], new_piece);
            } else {
                erase(allPieces[Colour::Black], new_piece);
            }
            delete new_piece;
        }

        if(dest_piece) {
            gonePiece.pop_back();
            if(colour == Colour::Black) {
                allPieces[Colour::White].emplace_back(dest_piece);
            } else {
                allPieces[Colour::Black].emplace_back(dest_piece);
            }
            dest_piece->setNew(dest_new);
            dest_piece->setPosn(dest);
        }
        this_piece->setPosn(p);


        // en passent
        if(eaten_pawn) {
            gonePiece.pop_back();
            if(colour == Colour::Black) {
                allPieces[Colour::White].emplace_back(eaten_pawn);
            } else {
                allPieces[Colour::Black].emplace_back(eaten_pawn);
            }
            theGrid[eaten_pawn_pos.x][eaten_pawn_pos.y] = eaten_pawn;

        }


        // castling
        if(cas_rook) {
            theGrid[p.x][p.y] = cas_king;
            cas_king->setPosn(cas_king_pos);
            cas_king->setNew(true);
            theGrid[cas_rook_pos.x][cas_rook_pos.y] = cas_rook;
            cas_rook->setPosn(cas_rook_pos);
            cas_rook->setNew(true);
            theGrid[dest.x][dest.y] = nullptr;
            if(cas_rook_pos.y == 7) {
                theGrid[p.x][5] = nullptr;
            } else {
                theGrid[p.x][3] = nullptr;
            }

        }


        throw "Careful: your king would be in check after such move!";



    } else {
        Posn tmp = dest - p;
        if(this_piece->getType() == 'p' && this_piece->getNew() \
        && (tmp == Posn{2,0} || tmp == Posn{-2,0})){
            justMovedPawn = this_piece;
        } else {
            justMovedPawn = nullptr;
        }
        theGrid[dest.x][dest.y]->setNew(false);


        // en passent
        if(eaten_pawn) {
            if (textDisplay) {
                textDisplay->notify(theGrid, eaten_pawn_pos);
                graphicsDisplay->notify(theGrid, eaten_pawn_pos);
            }
        }

        // castling
        if(cas_rook) {
            if (textDisplay) {
                textDisplay->notify(theGrid, cas_king_pos);
                textDisplay->notify(theGrid, cas_rook_pos);
                textDisplay->notify(theGrid, king_finish_pos);
                textDisplay->notify(theGrid, rook_finish_pos);
                graphicsDisplay->notify(theGrid, cas_king_pos);
                graphicsDisplay->notify(theGrid, cas_rook_pos);
                graphicsDisplay->notify(theGrid, king_finish_pos);
                graphicsDisplay->notify(theGrid, rook_finish_pos);
            }
        }

    }


    if (textDisplay) {
        textDisplay->notify(theGrid, p);
        textDisplay->notify(theGrid, dest);
        graphicsDisplay->notify(theGrid, p);
        graphicsDisplay->notify(theGrid, dest);
    }
    if (history) {

        Info cmd = Info{p, dest, trans, passAttack, castle, captured, this_new, type, justMovedPawn};
        string alg_output = to_alg_notation(cmd);
        string des_output = to_des_notation(cmd);
        history->update(cmd, theGrid, alg_output, des_output);
    }

}


void Grid::resign(Colour colour) {
    if(colour == Colour::White){
        score->notify(1);
        Info cmd = {-1, 0, 0, 0};
        string alg = to_alg_notation(cmd);
        string des = to_des_notation(cmd);
        history->update(cmd, theGrid, alg, des);
    } else {
        Info cmd = {0, -1, 0, 0};
        string alg = to_alg_notation(cmd);
        string des = to_des_notation(cmd);
        history->update(cmd, theGrid, alg, des);
        score->notify(-1);
    }
}


ostream &operator<<(ostream &out, const Grid &g){
    out << *g.textDisplay;
    return out;
}


Grid::Grid(const Grid &other) {
    setted = other.setted;
    vector<Piece*> trans;
    transferred = trans;
    textDisplay = nullptr;
    graphicsDisplay = nullptr;
    score = nullptr;
    history = nullptr;
    gonePiece = vector<Piece*>();

    whiteKingPosn = other.whiteKingPosn;
    blackKingPosn = other.blackKingPosn;

    Piece* new_piece;
    vector<Piece*> black;
    vector<Piece*> white;

    for(int i = 0; i < 8; i ++) {
        vector<Piece*> v1, v2;
        for(int j = 0; j < 8; j ++) {
            if (!other.theGrid.at(i).at(j)) {new_piece = nullptr;}
            else if (other.theGrid.at(i).at(j)->getType() == 'p') {
                new_piece = new Pawn(*(dynamic_cast<Pawn*>(other.theGrid.at(i).at(j))));
            }
            else if (other.theGrid.at(i).at(j)->getType() == 'n') {
                new_piece = new Knight(*(dynamic_cast<Knight*>(other.theGrid.at(i).at(j))));
            }
            else if (other.theGrid.at(i).at(j)->getType() == 'r') {
                new_piece = new Rook(*(dynamic_cast<Rook*>(other.theGrid.at(i).at(j))));
            }
            else if (other.theGrid.at(i).at(j)->getType() == 'q') {
                new_piece = new Queen(*(dynamic_cast<Queen*>(other.theGrid.at(i).at(j))));
            }
            else if (other.theGrid.at(i).at(j)->getType() == 'k') {
                new_piece = new King(*(dynamic_cast<King*>(other.theGrid.at(i).at(j))));
            }
            else if (other.theGrid.at(i).at(j)->getType() == 'b') {
                new_piece = new Bishop(*(dynamic_cast<Bishop*>(other.theGrid.at(i).at(j))));
            }
            v1.emplace_back(new_piece);
            v2.emplace_back(nullptr);

        }
        defaultGrid.emplace_back(v1);
        theGrid.emplace_back(v2);
    }

    init();

    if(other.justMovedPawn) {
        Posn justMovedPawn_posn = other.justMovedPawn->getPosn();
        justMovedPawn = theGrid[justMovedPawn_posn.x][justMovedPawn_posn.y];
    }
    else {justMovedPawn = nullptr;}

}


Grid& Grid::operator=(const Grid &other) {
    Grid tmp {other};
    gonePiece = vector<Piece*>();
    swap(tmp);
    return *this;
}

int Grid::whoWon(Colour colour) const {
    Piece* king = nullptr;
    Posn kingPosn;
    int n;
    vector<Piece*> myPiece = allPieces.at(colour);
    vector<Piece*> enemy;
    Colour enemyColour;

    if (colour == Colour::White) {
        kingPosn = blackKingPosn.at(0);
        enemyColour = Colour::Black;
        n = -1;
    }
    else if (colour == Colour::Black) {
        kingPosn = whiteKingPosn.at(0);
        enemyColour = Colour::White;
        n = 1;
    }
    enemy = allPieces.at(enemyColour);
    king = theGrid[kingPosn.x][kingPosn.y];

    bool check = false;
    for (auto i : myPiece) {
        if (i->checkKing(*this, kingPosn)) {
            check = true;
            break;
        }
    }
    if (check) {
        if (king->moveable(*this).size()) return n;
        for (auto p: enemy) {
            for (auto i: p->moveable(*this)) {
                Grid g {*this};
                try {g.movePiece(Info(p->getPosn(), i), enemyColour);}
                catch (const char*) {continue;}
                return n;
            }
        }
        if (score) {
            score->notify(n);
        }
        if (history){

            if(n == 1) {
                Info cmd = {-1, 0, 0, 0};
                string alg_output = to_alg_notation(cmd);
                string des_output = to_des_notation(cmd);
                history->update(cmd, theGrid, alg_output, des_output);
            }
            if(n == -1) {
                Info cmd = {0, -1, 0, 0};
                string alg_output = to_alg_notation(cmd);
                string des_output = to_des_notation(cmd);
                history->update(cmd, theGrid, alg_output, des_output);
            }
        }
        return 2*n;
    }
    else {
        bool notMoveable = true;
        for (auto p : enemy) {
            if (p->moveable(*this).size()) {notMoveable = false; break;}
        }
        if (notMoveable) {
            if (score) {
                score->notify(0);
            }
            if(history){
                string alg_output = to_alg_notation(Info{0, 0, -1, 0});
                string des_output = to_des_notation(Info{0, 0, -1, 0});
                history->update(Info{0, 0, -1, 0}, theGrid, alg_output, des_output);
            }
            return 3;
        }
        else return 0;
    }
}


// White win -2
// Black win 2
// Tie 3


char safeback(string s) {
    if (s == "") {throw 1;}
    else {return s.back();}
}

char safefirst(string s) {
    if (s == "") {throw 1;}
    else {return s[0];}
}

///////////
void Grid::alg_input(string input, Colour colour) {

    // 1. castling
    Posn p;
    Posn dest;

    if (input == "0-0") {
        if (colour == Colour::Black) {
            p = blackKingPosn[0];
        } else {
            p = whiteKingPosn[0];
        }
        try {
            this->movePiece(Info{p.x, p.y, p.x, p.y + 2}, colour);
        } catch (char const *err) {
            throw err;
        }
        return;


    } else if (input == "0-0-0") {
        if (colour == Colour::Black) {
            p = blackKingPosn[0];
        } else {
            p = whiteKingPosn[0];
        }
        try {
            this->movePiece(Info{p.x, p.y, p.x, p.y - 2}, colour);
        } catch (char const *err) {
            throw err;
        }
        return;
    }
    
    char promotion = '0';
    bool promoted = false;
    char dest_x = 'i', dest_y = '9';
    char last_bit;
    char type = 'p';
    int p_x = -1;
    int p_y = -1;
    vector<Posn> amove;
    vector<Posn> goodPiece;

    while (true) { 
        try {last_bit = safeback(input);}
        catch (int i) {throw "Invalid alg input: length error";}

        if (last_bit == 'B' || last_bit == 'R' || last_bit == 'N' || last_bit == 'Q') {
            promotion = last_bit;
            input.pop_back();
            try {last_bit = safeback(input);}
            catch (int i) {throw "Invalid alg input: length error";}
            if (last_bit != '=') {throw "Invalid alg input: promotion error";}
            promoted = true;
            input.pop_back();
        }
        else if (last_bit == '+' || last_bit ==  '#') {
            input.pop_back();
        }

        try {dest_y = safeback(input);}
        catch (int i) {throw "Invalid alg input: length error";}
        input.pop_back();
        try {dest_x = safeback(input);}
        catch (int i) {throw "Invalid alg input: length error";}
        input.pop_back();

        if (dest_y > '8' || dest_y < '1' || dest_x > 'h' || dest_x < 'a') {
            throw "Invalid alg input: destination position error.";
        }

        dest = Posn('8' - dest_y, dest_x - 'a');
    

        try {last_bit = safeback(input);}
        catch (int i) {break;}

        if (last_bit == 'x') {
            if (theGrid[dest.x][dest.y] && theGrid[dest.x][dest.y]->getColour() != colour) {
                input.pop_back();
            }
            else {throw "Invalid alg input: destination is not enemy.";}
        }

        try {last_bit = safeback(input);}
        catch (int i) {break;}
        bool b = true;
        bool b1 = false;

        while (b) {
            if (last_bit == 'P' || last_bit == 'B' || last_bit == 'Q' || last_bit == 'N'\
            || last_bit == 'K' || last_bit == 'R') {
                type = last_bit + 'a' - 'A';
                input.pop_back();
                try {last_bit = safeback(input);}
                catch (int i) {b = false; break;}
                throw "Invalid alg input: un-recognized infomation detected.";
            }

            else if (last_bit >= 'a' && last_bit <= 'h') {
                if (p_y != -1) {throw "Invalid alg input: double file detected.";}
                p_y = last_bit - 'a';
                try {last_bit = safeback(input);}
                catch (int i) {b = false; b1 = true; break;}
            }

            else if (last_bit >= '1' && last_bit <= '8') {
                if (!b1) {throw "Error: position coordination error.";}
                if (p_x != -1) {throw "Invalid alg input: double rank detected.";}
                p_x = '8' - last_bit;
                try {last_bit = safeback(input);}
                catch (int i) {b = false; break;}
            }

            else {throw "Invalid alg input: un-recognized infomation detected.";}
            input.pop_back();
        }
        break;
    }

    p = Posn{p_x, p_y};

    for (auto myPiece : allPieces[colour]) {
        if (myPiece->getType() == type) {
            if ((p.x != -1 && myPiece->getPosn().x != p.x) || 
            (p.y != -1 && myPiece->getPosn().y != p.y)) {continue;}
            amove = myPiece->moveable(*this);
            if (my_in(amove, dest)) {goodPiece.emplace_back(myPiece->getPosn());}
        }
    }

    Info info;
    string t;
    if (goodPiece.size() == 1) {
        if (promoted) {
            t = promotion;
            if ((goodPiece.back().x != 7 || dest.x != 8) && (goodPiece.back().x != 1 || dest.x != 0)\
            && type != 'p') {throw "Invalid alg input: promotion not properly.";}
            info = Info(goodPiece.back(), dest, true, false, false, false, false, t);
        }
        else info = Info(goodPiece.back(), dest);
        try {movePiece(info, colour);}
        catch (char const* c) {throw c;}
    }
    else if (goodPiece.size() == 0) {
        throw "Invalid alg input: No proper Piece.";
    }
    else {throw "Invalid alg input: Ambiguity.";}

}


void Grid::dsp_input(string input, Colour colour) {

    Posn p {-1, -1};
    Posn dest {-1, -1};
    // 1. castling
    if (input == "O-O") {
        if (colour == Colour::Black) {
            Posn p = blackKingPosn[0];
        } else {
            Posn p = whiteKingPosn[0];
        }
        try {
            this->movePiece(Info{p.x, p.y, p.x, p.y + 2}, colour);
        } catch (char const *err) {
            throw err;
        }
        return;


    } else if (input == "O-O-O") {
        if (colour == Colour::Black) {
            Posn p = blackKingPosn[0];
        } else {
            Posn p = whiteKingPosn[0];
        }
        try {
            this->movePiece(Info{p.x, p.y, p.x, p.y - 2}, colour);
        } catch (char const *err) {
            throw err;
        }
        return;
    }

    char first_char;
    char p_type = '0';
    char dest_type = '0';
    char promotion = '0';
    bool capture = false;
    bool promoted = true;
    string pname = "";
    string destname = "";
    vector<Posn> amove;
    vector<Posn> goodPiece;

    try {first_char = safefirst(input);}
    catch (int i) {throw "Invalid des Input: length error.";}

    if (first_char != 'P' && first_char != 'B' && first_char != 'Q' && first_char != 'N' && \
    first_char != 'K' && first_char != 'R') {throw "Invalid des Input: piece type error.";}
    else {p_type = first_char; input.erase(0, 1);}

    try {first_char = safefirst(input);}
    catch (int i) {throw "Invalid des Input: length error.";}

    if (first_char == '(') {

        input.erase(0, 1);
        try {first_char = safefirst(input);}
        catch (int i) {throw "Invalid des Input: length error.";}

        while (first_char != ')') {
            pname += first_char;

            input.erase(0, 1);
            try {first_char = safefirst(input);}
            catch (int i) {throw "Invalid des Input: length error.";}
        }

        try {p = dnotation_to_posns(pname, colour);}
        catch (char const* c) {throw c;}
        input.erase(0, 1);
    }

    try {first_char = safefirst(input);}
    catch (int i) {throw "Invalid des Input: length error.";}

    if (first_char == '-') {

        input.erase(0, 1);
        try {first_char = safefirst(input);}
        catch (int i) {throw "Invalid des Input: piece posn error.";}

        while (first_char != '=') {
            destname += first_char;

            input.erase(0, 1);
            try {first_char = safefirst(input);}
            catch (int i) {break;}
        }

        try {dest = dnotation_to_posns(destname, colour);}
        catch (char const* c) {throw c;}
    }

    else if (first_char == 'x') {

        capture = true;
        bool b = false;

        input.erase(0, 1);
        try {first_char = safefirst(input);}
        catch (int i) {throw "Invalid des Input: length error.";}

        if (first_char != 'P' && first_char != 'B' && first_char != 'Q' && first_char != 'N' && \
        first_char != 'K' && first_char != 'R') {throw "Invalid des Input: piece type error.";}
        else {dest_type = first_char; input.erase(0, 1);}

        try {first_char = safefirst(input);}
        catch (int i) {}

        if (first_char == '=') {}

        else if (first_char == '(') {
            b = true;
            input.erase(0, 1);
            try {first_char = safefirst(input);}
            catch (int i) {throw "Invalid des Input: dest posn error.";}
        }

        else {throw "Invalid des Input: un-recognized infomation detected.";}

        while (b && first_char != ')') {
            destname += first_char;
            input.erase(0, 1);
            try {first_char = safefirst(input);}
            catch (int i) {throw "Invalid des Input: enemy posn error.";}
        }

        if (b) {
            try {dest = dnotation_to_posns(destname, colour);}
            catch (char const* c) {throw c;}
            input.erase(0, 1);
        }
    }


    try {first_char = safefirst(input);}
    catch (int i) {promoted = false;} 
    p_type = p_type + 'a' - 'A';
    dest_type = dest_type + 'a' - 'A';

    if (promoted) {
        if (first_char != '=') {throw "Invalid des Input: un-recognized infomation detected.";}

        input.erase(0, 1);
        try {first_char = safefirst(input);}
        catch (int i) {throw "Invalid des Input: length error.";}

        if (first_char != 'P' && first_char != 'B' && first_char != 'Q' && first_char != 'N' && \
        first_char != 'K' && first_char != 'R') {throw "Invalid des Input: promotion type error.";}
        else {promotion = first_char; input.erase(0, 1);}

        if (input.size() != 0) {throw "Invalid des Input: length error.";}
    }


    if (capture) {
        for (auto myPiece : allPieces[colour]) {
            if (myPiece->getType() == p_type) {
                if ((p.x != -1 && myPiece->getPosn().x != p.x) || 
                (p.y != -1 && myPiece->getPosn().y != p.y)) {continue;}
                amove = myPiece->attackable(*this);
                if (my_in(amove, dest)) {
                    if (theGrid[dest.x][dest.y] && theGrid[dest.x][dest.y]->getType() == dest_type) {
                        goodPiece.emplace_back(myPiece->getPosn());
                    }
                    else if (!theGrid[dest.x][dest.y] && dest_type == 'p') {
                        goodPiece.emplace_back(myPiece->getPosn());
                    }
                }
                else if (dest == Posn(-1, -1)) {
                    for (auto pos : amove) {
                        if (theGrid[pos.x][pos.y] && theGrid[pos.x][pos.y]->getType() == dest_type) {
                            goodPiece.emplace_back(myPiece->getPosn());
                            dest = theGrid[pos.x][pos.y]->getPosn();
                            break;
                        }
                    }
                }
            }
        }
    }

    else {
        for (auto myPiece : allPieces[colour]) {
            if (myPiece->getType() == p_type) {
                if ((p.x != -1 && myPiece->getPosn().x != p.x) || 
                (p.y != -1 && myPiece->getPosn().y != p.y)) {continue;}
                amove = myPiece->moveable(*this);
                if (my_in(amove, dest)) {
                    if (theGrid[dest.x][dest.y]) {throw "Invalid des Input: destination is not empty.";}
                    goodPiece.emplace_back(myPiece->getPosn());
                }
            }
        }
    }

    Info info;
    string t;
    if (goodPiece.size() == 1) {
        if (promoted) {
            t = promotion;
            if ((goodPiece.back().x != 7 || dest.x != 8) && (goodPiece.back().x != 1 || dest.x != 0)\
            && p_type != 'p') {throw "Invalid des input: promotion not properly.";}
            info = Info(goodPiece.back(), dest, true, false, false, false, false, t);
        }
        else info = Info(goodPiece.back(), dest);
        try {movePiece(info, colour);}
        catch (char const* c) {throw c;}
    }
    else if (goodPiece.size() == 0) {
        throw "Invalid des input: No proper Piece.";
    }
    else {throw "Invalid des input: Ambiguity.";}

}


void Grid::dynamicInput(std::string input, Colour colour) {
    string alg_error = "";
    string des_error = "";
    try {alg_input(input, colour);}
    catch (char const *c) {
        alg_error = c;
        try {dsp_input(input, colour);}
        catch (char const *c) {
            cout << alg_error << endl;
            throw c;}
        return;
    }
    if (des_error.empty()) {return;}
    else {throw des_error;}
}


void Grid::undo_onestep(Info cmd) {
    Piece* captured_piece = nullptr;
    justMovedPawn = cmd.justMovedPawn;

    Posn p = cmd.p;
    Posn dest = cmd.dest;

    Colour return_colour = theGrid[dest.x][dest.y]->getColour();
    Colour enemy_colour;
    if (return_colour == Colour::Black) enemy_colour = Colour::White;
    else if (return_colour == Colour::White) enemy_colour = Colour::Black;

    if(cmd.castle) {
        // 1. If last step is a castling
        Posn king_old_pos = Posn{p.x, 4};
        Posn king_new_pos = dest;
        Posn rook_old_pos;
        Posn rook_new_pos;

        if(dest.y - p.y == 2) {
            rook_old_pos = Posn{p.x, 7};
            rook_new_pos = Posn{p.x, 5};
        } else {
            rook_old_pos = Posn{p.x, 0};
            rook_new_pos = Posn{p.x, 3};
        }

        theGrid[rook_old_pos.x][rook_old_pos.y] = theGrid[rook_new_pos.x][rook_new_pos.y];
        theGrid[rook_new_pos.x][rook_new_pos.y] = nullptr;
        Piece* rook = theGrid[rook_old_pos.x][rook_old_pos.y];
        rook->setNew(true);
        rook->setPosn(rook_old_pos);

        theGrid[king_old_pos.x][king_old_pos.y] = theGrid[king_new_pos.x][king_new_pos.y];
        theGrid[king_new_pos.x][king_new_pos.y] = nullptr;
        Piece* king = theGrid[king_old_pos.x][king_old_pos.y];
        king->setNew(true);
        king->setPosn(king_old_pos);

        if(p.x == 0) {
            blackKingPosn[0] = king_old_pos;
        } else {
            whiteKingPosn[0] = king_old_pos;
        }

        if (textDisplay) {
            textDisplay->notify(theGrid, rook_new_pos);
            textDisplay->notify(theGrid, rook_old_pos);
            textDisplay->notify(theGrid, king_new_pos);
            textDisplay->notify(theGrid, king_old_pos);
            graphicsDisplay->notify(theGrid, rook_new_pos);
            graphicsDisplay->notify(theGrid, rook_old_pos);
            graphicsDisplay->notify(theGrid, king_new_pos);
            graphicsDisplay->notify(theGrid, king_old_pos);
        }

    } else if (cmd.transferred) {
        // 2. If last step is a pawn promotion
        Piece* new_piece = transferred.back();
        Piece* return_piece = gonePiece.back();
        gonePiece.pop_back();

        erase(allPieces[return_colour], new_piece);
        allPieces[return_colour].emplace_back(return_piece);
        theGrid[p.x][p.y] = return_piece;
        return_piece->setPosn(p);
        theGrid[dest.x][dest.y] = nullptr;

        delete new_piece;
        transferred.pop_back();

        if (cmd.captured) {
            captured_piece = gonePiece.back();
            gonePiece.pop_back();
            allPieces[enemy_colour].emplace_back(captured_piece);
            theGrid[dest.x][dest.y] = captured_piece;
            captured_piece->setPosn(dest);
        }

        if (textDisplay) {
            textDisplay->notify(theGrid, dest);
            textDisplay->notify(theGrid, p);
            graphicsDisplay->notify(theGrid, dest);
            graphicsDisplay->notify(theGrid, p);
        }


    } else if (cmd.passAttack) {
        // 3. If last step is a en passant
        Piece* eaten_pawn = gonePiece.back();
        gonePiece.pop_back();

        Posn eaten_pawn_pos = eaten_pawn->getPosn();
        allPieces[enemy_colour].emplace_back(eaten_pawn);
        eaten_pawn->setNew(false);

        justMovedPawn = eaten_pawn;
        theGrid[eaten_pawn_pos.x][eaten_pawn_pos.y] = eaten_pawn;

        theGrid[p.x][p.y] = theGrid[dest.x][dest.y];
        theGrid[dest.x][dest.y] = nullptr;
        Piece* move_piece = theGrid[p.x][p.y];
        move_piece->setNew(cmd.newed);
        move_piece->setPosn(p);


        if (textDisplay) {
            textDisplay->notify(theGrid, dest);
            textDisplay->notify(theGrid, p);
            textDisplay->notify(theGrid, eaten_pawn_pos);
            graphicsDisplay->notify(theGrid, dest);
            graphicsDisplay->notify(theGrid, p);
            graphicsDisplay->notify(theGrid, eaten_pawn_pos);
        }

    } else if (cmd.captured) {
        captured_piece = gonePiece.back();
        gonePiece.pop_back();
        allPieces[enemy_colour].emplace_back(captured_piece);
        theGrid[p.x][p.y] = theGrid[dest.x][dest.y];
        Piece* move_piece = theGrid[p.x][p.y];
        theGrid[dest.x][dest.y] = captured_piece;
        captured_piece->setPosn(dest);
        move_piece->setNew(cmd.newed);
        move_piece->setPosn(p);

        if(move_piece->getType() == 'k') {
            if(return_colour == Colour::Black) {
                blackKingPosn[0] = p;
            } else {
                whiteKingPosn[0] = p;
            }
        }

        if (textDisplay) {
            textDisplay->notify(theGrid, dest);
            textDisplay->notify(theGrid, p);
            graphicsDisplay->notify(theGrid, dest);
            graphicsDisplay->notify(theGrid, p);
        }

    } else {
        theGrid[p.x][p.y] = theGrid[dest.x][dest.y];
        Piece* move_piece = theGrid[p.x][p.y];
        theGrid[dest.x][dest.y] = nullptr;
        move_piece->setNew(cmd.newed);
        move_piece->setPosn(p);

        if(move_piece->getType() == 'k') {
            if(return_colour == Colour::Black) {
                blackKingPosn[0] = p;
            } else {
                whiteKingPosn[0] = p;
            }
        }

        if (textDisplay) {
            textDisplay->notify(theGrid, dest);
            textDisplay->notify(theGrid, p);
            graphicsDisplay->notify(theGrid, dest);
            graphicsDisplay->notify(theGrid, p);
        }
    }
}

void Grid::undo(int step) {
    history->undo(*this, step);
}


bool Grid::alarm() {return history->alarm();}

void Grid::notifyScore() {score->notify(0);}
void Grid::notifyHistory() {
    Info cmd = {0, 0, -1, 0};
    string alg = to_alg_notation(cmd);
    string des = to_des_notation(cmd);
    history->update(cmd, theGrid, alg, des);
}

void Grid::notifyFeatures(bool features[]) {
    graphicsDisplay->notifyFeatures(features);
}


vector<string> Grid::returnHistory(string choice) {
    vector<string> v;
    if(choice == "normal") {
        v = history->get_normal_output();
    } else if (choice == "alg") {
        v = history->get_alg_output();
    } else if (choice == "des") {
        v = history->get_des_output();
    } else {
        throw "It is not one of the standard choice for output.";
    }
    return v;
}
