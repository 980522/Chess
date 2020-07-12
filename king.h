#ifndef _KING_H_
#define _KING_H_
#include <cstddef>
#include "piece.h"

class King : public Piece {

  void move(const Grid& g, Posn dest) override;   

  std::vector<Posn> amove(const Grid& g) const override;

  std::vector<Posn> attack(const Grid& g) const override;

  bool check(const Grid& g, Posn dest) override;

  bool isK() override {return true;}

public: 
  
  King(Posn posn, Colour c);

  King(const King& pp): Piece {pp} {}
  
  King& operator= (const King &pp) {
    if (this == &pp) return *this;
    Piece::operator=(pp);
    return *this;
  }

  ~King() override {}


};
#endif
