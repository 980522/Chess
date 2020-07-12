#ifndef _SCORE_H_
#define _SCORE_H_
#include <iostream>

class Score {

    double wscore;
    double bscore;

public:
    
    Score(): wscore {0}, bscore {0} {}
    void notify(int n) {
        if (n == -1) {wscore += 1;} 
        else if (n == 1) {bscore += 1;} 
        else {wscore += 0.5; bscore += 0.5;}
    }

    friend std::ostream& operator<< (std::ostream& out, const Score& s) {
        out << "Final Score:" << std::endl;
        out << "White: " << s.wscore << std::endl;
        out << "Black: " << s.bscore;
        return out;
    }
};

#endif
