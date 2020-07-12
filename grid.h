#ifndef _GRID_H_
#define _GRID_H_
#include <vector>
#include <map>
#include <cstddef>
#include "posn.h"
#include <string>
#include <utility>
#include "info.h"

class TextDisplay;
class GraphicsDisplay;
class Score;
class History;
class Piece;
class Bishop;
class Queen;
class Knight;
class Rook;
class King;
class Pawn;
class Score;


enum class Colour { NoColour, Black, White};

class Grid {

    std::vector<std::vector<Piece*>> theGrid;
    std::vector<std::vector<Piece*>> defaultGrid;

    std::map<Colour , std::vector<Piece*>> allPieces;
    std::vector<Posn> whiteKingPosn, blackKingPosn;

    std::vector<Piece*> transferred;
    Piece* justMovedPawn;
    std::vector<Piece*> gonePiece;
    bool setted;
    TextDisplay* textDisplay;
    GraphicsDisplay* graphicsDisplay;
    Score* score;
    History* history;

private:
    std::string to_alg_notation(Info cmd) const;
    std::string to_des_notation(Info cmd) const;

    void alg_input(std::string input, Colour colour);
    void dsp_input(std::string input, Colour colour);

    void swap(Grid &other) {
        using std::swap;
        swap(setted, other.setted);
        swap(theGrid, other.theGrid);
        swap(defaultGrid, other.defaultGrid);
        swap(allPieces, other.allPieces);
        swap(whiteKingPosn, other.whiteKingPosn);
        swap(blackKingPosn, other.blackKingPosn);
        swap(transferred, other.transferred);
        swap(justMovedPawn, other.justMovedPawn);
        swap(textDisplay, other.textDisplay);
        swap(graphicsDisplay, other.graphicsDisplay);
        swap(score, other.score);
        swap(history, other.history);
    }

public:

    Grid();
    Grid(const Grid &other);

    Grid &operator=(const Grid& other);

    

    ~Grid();

    int whoWon(Colour colour) const;

    std::vector<std::vector<Piece*>> getTheGrid() const {return theGrid;}
    Piece* getJustMovedPawn() const {return justMovedPawn;}
    std::map<Colour , std::vector<Piece*>> getAllPiece() const {return allPieces;}
    Score* getScore() const {return score;}
    bool getSetted() const {return setted;}


    void setup();
    void insertPiece(std::string type, Posn p);
    void deletePiece(Posn p);
    bool setupCheck();

    Posn getBlackKingPos() const {return blackKingPosn[0];};

    Posn getWhiteKingPos() const {return whiteKingPosn[0];};


    void init();
    void movePiece(Info info, Colour colour);

    std::vector<std::string> returnHistory(std::string choice);
    void resign(Colour colour);
    void undo_onestep(Info cmd);
    void undo(int step);
    void dynamicInput(std::string, Colour colour);
    bool alarm();

    void notifyFeatures(bool features[]);
    void notifyScore();
    void notifyHistory();


    friend std::ostream &operator<<(std::ostream &out, const Grid &g);

};


#endif

