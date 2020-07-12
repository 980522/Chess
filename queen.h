#ifndef _QUEEN_H_
#define _QUEEN_H_
#include <cstddef>
#include "piece.h"

class Queen : public Piece {

  void move(const Grid& g, Posn dest) override;    

  std::vector<Posn> amove(const Grid& g) const override;

  std::vector<Posn> attack(const Grid& g) const override;

  bool check(const Grid& g, Posn dest) override;


  bool isK() override {return false;}

public: 
  
  Queen(Posn posn, Colour c);

  Queen(const Queen& pp): Piece {pp} {}
  
  Queen& operator= (const Queen &pp) {
    if (this == &pp) return *this;
    Piece::operator=(pp);
    return *this;
  }

  ~Queen() override {}


};

#endif
