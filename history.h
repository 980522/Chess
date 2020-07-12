//
// Created by Annalice Zhuang on 2019-04-02.
//

#ifndef CHESS_HISTORY_H
#define CHESS_HISTORY_H

#include "grid.h"

class History {

    std::vector<std::vector<std::vector<char>>> allPastGrids;
    std::vector<std::vector<std::vector<char>>> updatedGrids;
    std::vector<Info> commands;
    std::vector<int> updated_start;

    std::vector<std::string> normal_output;
    std::vector<std::string> alg_output;
    std::vector<std::string> des_output;

private:
    std::string posn_to_cord(Posn pos);
    bool my_in(std::vector<Posn> posns , Posn pos);


    std::string all_moves();

public:
    History();

    bool alarm() const;
    void undo(Grid &g, int n);
    void update(Info info, std::vector<std::vector<Piece*>> theGrid, std::string alg, std::string des);

    std::vector<std::string> get_normal_output() {return normal_output;}
    std::vector<std::string> get_alg_output() {return alg_output;}
    std::vector<std::string> get_des_output() {return des_output;}

};


#endif //CHESS_HISTORY_H
