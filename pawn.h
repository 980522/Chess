#ifndef _PAWN_H_
#define _PAWN_H_
#include <cstddef>
#include "piece.h"

class Pawn : public Piece {

  void move(const Grid& g, Posn dest) override;    

  std::vector<Posn> amove(const Grid& g) const override;

  std::vector<Posn> attack(const Grid& g) const override;

  bool check(const Grid& g, Posn dest) override;

  bool isK() override {return false;}

public: 
  Pawn(Posn posn, Colour c);

  Pawn(const Pawn& pp): Piece {pp} {}
  
  Pawn& operator= (const Pawn &pp) {
    if (this == &pp) return *this;
    Piece::operator=(pp);
    return *this;
  }

  ~Pawn() override {}

};
#endif
