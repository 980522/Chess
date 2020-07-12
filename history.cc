#include "history.h"
#include "piece.h"
using namespace std;
#include <iostream>

History::History() {

    vector<vector<vector<char>>> allPastGrids;
    vector<vector<vector<char>>> updatedGrids;
    vector<Info> commands;
    vector<int> updated_start;
    updated_start.emplace_back(0);

    vector<string> normal_output;
    vector<string> alg_output;
    vector<string> des_output;

}


string History::posn_to_cord(Posn pos) {
    char c1 = 'a' + pos.y;
    char c2 = '8' - pos.x;

    string s1{""};
    s1 += c1;
    string s2{""};
    s2 += c2;

    return s1+s2;
}


bool History::my_in(vector<Posn> posns , Posn pos) {
    for(auto p : posns) {
        if(pos == p) return true;
    }
    return false;
}


// Helper
vector<vector<char>> grid_to_chars(vector<vector<Piece*>> grid){
    vector<vector<char>> v;
    for(int i = 0; i < 8; i ++) {
        vector<char> v1;
        for(int j = 0; j < 8; j ++) {
            Piece* curr = grid[i][j];
            char c;
            int colour;
            if(curr){
                c = curr->getType();
                if(grid[i][j]->getColour() == Colour :: Black) colour = 0;
                else colour = 'a' - 'A';
            }
            if(curr) v1.emplace_back(c - colour);
            else v1.emplace_back(' ');
        }
        v.emplace_back(v1);
    }
    return v;
}


bool equal_char_grid(vector<vector<char>> g, vector<vector<char>> other) {
    for(int i = 0; i < 8; i ++) {
        for(int j = 0; j < 8; j ++) {
            if(g[i][j] != other[i][j]) return false;
        }
    }
    return true;
}




bool History::alarm() const {

    int count = 0;
    for(auto i : updatedGrids) {
        if (equal_char_grid(i, allPastGrids.back())) count++;
    }
    return count >= 3;
}

void History::undo(Grid& g, int n){

    int num_cmd = commands.size();

    vector<vector<vector<char>>> new_updated;
    int start, end;

    if(n > num_cmd - 1) throw "Undo out of range!";

    for(int i = 0; i < n; i ++){
        Info cmd = commands.back();
        commands.pop_back();
        allPastGrids.pop_back();
        g.undo_onestep(cmd);
        normal_output.pop_back();
        alg_output.pop_back();
        //des_output.pop_back();

        if (updatedGrids.size() != 1) {updatedGrids.pop_back();}
        else {
            end = updated_start.back();
            updated_start.pop_back();
            start = updated_start.back();
            for (int j {start}; j < end; j++) {
                updatedGrids.emplace_back(allPastGrids[j]);
            }
        }
    }
}


void History::update(Info info, vector<vector<Piece*>> theGrid, string alg, string des) {

    Posn p = info.p;
    Posn dest = info.dest;
    vector<vector<char>> v1 = grid_to_chars(theGrid);

    updatedGrids.emplace_back(v1);
    commands.emplace_back(info);
    allPastGrids.emplace_back(v1);

    normal_output.emplace_back(all_moves());
    alg_output.emplace_back(alg);
    des_output.emplace_back(des);


    if(info.transferred || info.passAttack || info.captured) {
        updatedGrids = vector<vector<vector<char>>>();
        updatedGrids.emplace_back(v1);
        updated_start.emplace_back(int(allPastGrids.size()) - 1);
    }
}


std::string History::all_moves() {
    Info cmd = commands.back();
    Posn p = cmd.p;
    Posn dest = cmd.dest;
    string s {""};
    if(dest.y == -1) {
        s = "Start:";
        return s;
    }
    s = "move ";
    s = s + History::posn_to_cord(p) + " " + History::posn_to_cord(dest);
    if(p.x == -1) s = "0-1";
    if(p.y == -1) s = "1-0";
    if(dest.x == -1) s = "1/2 - 1/2";
    return s;
}


