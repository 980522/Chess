#ifndef _KNIGHT_H_
#define _KNIGHT_H_
#include <cstddef>
#include "piece.h"

class Knight : public Piece {

  void move(const Grid& g, Posn dest) override;   

  std::vector<Posn> amove(const Grid& g) const override;

  std::vector<Posn> attack(const Grid& g) const override;

  bool check(const Grid& g, Posn dest) override;

  bool isK() override {return false;}

public: 
  
  Knight(Posn posn, Colour c);

  Knight(const Knight& pp): Piece {pp} {}
  
  Knight& operator= (const Knight &pp) {
    if (this == &pp) return *this;
    Piece::operator=(pp);
    return *this;
  }

  ~Knight () override {}


};
#endif

