#ifndef _POSN_H_
#define _POSN_H_

struct Posn {
    int x;
    int y;

    Posn() = default;
    Posn(int x, int y): x {x}, y {y} {}
    Posn(const Posn& p): x {p.x}, y {p.y} {}
    Posn(Posn&& p): x {p.x}, y {p.y} {}
    
    Posn &operator= (const Posn& p);
    Posn &operator= (Posn&& p);

    Posn operator+ (const Posn& p) const;
    Posn operator- (const Posn& p) const;

    Posn& operator+= (const Posn& p);

    bool operator== (const Posn& p) const;
    bool operator!= (const Posn& p) const;

    void clockturn (int degree);

    ~Posn() = default;
};


#endif
