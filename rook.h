#ifndef _ROOK_H_
#define _ROOK_H_
#include <cstddef>
#include "piece.h"

class Rook : public Piece {

  void move(const Grid& g, Posn dest) override;  

  std::vector<Posn> amove(const Grid& g) const override;

  std::vector<Posn> attack(const Grid& g) const override;

  bool check(const Grid& g, Posn dest) override;

  bool isK() override {return false;}

public: 
  Rook(Posn posn, Colour c);

  Rook(const Rook& pp): Piece {pp} {}
  
  Rook& operator= (const Rook &pp) {
    if (this == &pp) return *this;
    Piece::operator=(pp);
    return *this;
  }

  ~Rook() override {}

};
#endif
