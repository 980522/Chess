#ifndef _BISHOP_H_
#define _BISHOP_H_
#include <cstddef>
#include "piece.h"

class Bishop : public Piece {

  void move(const Grid& g, Posn dest) override;    

  std::vector<Posn> amove(const Grid& g) const override;

  std::vector<Posn> attack(const Grid& g) const override;

  bool check(const Grid& g, Posn dest) override;

  bool isK() override {return false;}

public: 

  Bishop(Posn posn, Colour c);

  Bishop(const Bishop& pp): Piece {pp} {}
  
  Bishop& operator= (const Bishop &pp) {
    if (this == &pp) return *this;
    Piece::operator=(pp);
    return *this;
  }

  ~Bishop() override {}

};
#endif
