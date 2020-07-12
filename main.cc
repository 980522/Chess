#include <iostream>
#include <string>
#include <vector>
#include "grid.h"
#include "score.h"
#include "info.h"
#include "ai2.h"
#include "ai4.h"
using namespace std;


int main() {
    srand(time(NULL));
    cin.exceptions(ios::eofbit|ios::failbit);
    string cmd, fplayer, splayer, curplayer, curColour, s, type, feature, style;
    Colour colour = Colour::White;
    Colour defaultColour = Colour::White;
    vector<string> historyOutput;
    int result, step;
    double cycle = 0;
    Grid g;
    char c, from, to;
    int v;
    int alarm = 0;
    Info info;
    bool resign = false;
    bool setted = false;
    bool features[6] {false, false, false, false, false, false};
    const string featuresName[6] {"Opening move: ", "Undo: ", \
    "Dynamic Input: ", "History: ", "Alarm: ", "Suggestion: "};


    try {
    while (true) {
        cin >> cmd;
        if (cmd == "setup") {
            g.setup();
            setted = true;
            features[0] = false;
            g.notifyFeatures(features);
            while (true) {
                cout << g << endl;
                cin >> s;

                if (s == "+") {
                    cin >> type;
                    cin >> c;
                    cin >> v;
                    if (type != "R" && type != "r" && type != "N" && type != "n" &&\
                    type != "B" && type != "b" && type != "Q" && type != "q" &&\
                    type != "K" && type != "k" && type != "P" && type != "p") {
                        cout << "Error: Type error" << endl;
                        continue;
                    }
                    if (c < 'a' || c > 'h' || v < 1 || v > 8) {
                        cout << "Error: Coordination error" << endl;
                        continue;
                    }
                    g.insertPiece(type, Posn{8-v, c - 'a'});
                }

                else if (s == "-") {
                    cin >> c;
                    cin >> v;
                    if (c < 'a' || c > 'h' || v < 1 || v > 8) {
                        cout << "Error: Coordination error" << endl;
                        continue;
                    }
                    g.deletePiece(Posn{8-v, c - 'a'});
                    continue;
                }

                else if (s == "=") {
                    cin >> curColour;
                    if (curColour == "Black") {defaultColour = Colour::Black;}
                    else if (curColour == "White") {defaultColour = Colour::White;}
                    else cout << "Error: wrong colour." << endl;
                }

                else if (s == "done") {
                    if (g.setupCheck()) {
                        cout << "Setup succeed!" << endl;
                        break;
                    }
                    else cout << "Setup error." << endl;
                }

                else {
                    cout << "Setup error: invalid input." << endl;
                    continue;
                }
            }
        }

        else if (cmd == "features") {
            
            while (true) {
                cout << "++++++++++++++++++++++++++++++++" << endl;
                for (int i {0}; i < 6; i ++) {
                    cout << featuresName[i];
                    if (features[i]) cout << "abled" << endl;
                    else cout << "unabled" << endl;
                }
                cout << "++++++++++++++++++++++++++++++++" << endl;
                cin >> cmd;
                if (cmd == "able" || cmd == "unable") {
                    cin >> feature;
                    if (feature == "openingmove") {
                        if (cmd == "able" && setted) {
                            cout << \
                            "Features error: setted configuation cannot able opening move" \
                            << endl;
                        }
                        else {features[0] = (cmd == "able");}
                    }
                    else if (feature == "undo") features[1] = (cmd == "able");
                    else if (feature == "dynamicinput") features[2] = (cmd == "able");
                    else if (feature == "history") features[3] = (cmd == "able");
                    else if (feature == "alarm") features[4] = (cmd == "able");
                    else if (feature == "suggestion") features[5] = (cmd == "able");
                    else {cout << "Error: Feature type error." << endl;}
                    g.notifyFeatures(features);
                    continue;
                }
                else if (cmd == "done") break;
                else {
                    cout << "Error: Feature Error." << endl;
                    continue;
                }
            }
        }

        else if (cmd == "history") {
            cin >> style;
            if (!features[3]) {
                cout << "Error: History feature unabled." << endl;
                continue;
            }
            else {
                try {historyOutput = g.returnHistory(style);}
                catch (char const* c) {
                    cout << c << endl;
                    continue;
                }
                for (auto i : historyOutput) {
                    cout << i << endl;
                }
                continue;
            }

        }

        else if (cmd == "game") {
            alarm = 0;
            cycle = 0;
            resign = false;
            AI1 ai1(features[0]);
            AI2 ai2(features[0]);
            AI3 ai3(features[0]);
            AI4 ai4(features[0]);
            cin >> fplayer;
            cin >> splayer;
            if (((fplayer != "human") && (fplayer != "computer1") && (fplayer != "computer2")\
            && (fplayer != "computer3") && (fplayer != "computer4")) || \
                ((splayer != "human") && (splayer != "computer1") && (splayer != "computer2")\
            && (splayer != "computer3") && (splayer != "computer4"))) {
                cout << "Error: player error." << endl;
                continue;
            }
            g.init();
            colour = defaultColour;
            cout << g << endl;
            curplayer = fplayer;

            while (true) {
                step = cycle;
                if (curplayer == "computer1") {
                    info = ai1.suggestMove(g, colour, step);
                    g.movePiece(info, colour);
                }
                else if (curplayer == "computer2") {
                    info = ai2.suggestMove(g, colour, step);
                    g.movePiece(info, colour);
                }
                else if (curplayer == "computer3") {
                    info = ai3.suggestMove(g, colour, step);
                    g.movePiece(info, colour);
                }
                else if (curplayer == "computer4") {
                    info = ai4.suggestMove(g, colour, step);
                    g.movePiece(info, colour);
                }
                else if (curplayer == "human") {
                    while (true) {
                        cin >> cmd;
                        if (cmd == "move") {
                            cin >> c;
                            cin >> v;
                            Posn p {8-v, c-'a'};
                            cin >> c;
                            cin >> v;
                            Posn dest = {8-v, c-'a'};
                            if (p.x < 0 || p.x > 7 || p.y < 0 || p.y > 7 ||\
                            dest.x < 0 || dest.x > 7 || dest.y < 0 || dest.y > 7) {
                                cout << "Error: Coordination error" << endl;
                                continue;
                            }
                            info = Info(p, dest);
                            try {g.movePiece(info, colour);}
                            catch(char const* msg) {
                                cout << msg << endl << g << endl; continue;
                            }
                            break;
                        }

                        else if (cmd == "suggestion") {
                            if (!features[5]) {
                                cout << "Error: Suggestion feature unabled." << endl;
                                continue;
                            }
                            else {
                                info = ai4.suggestMove(g, colour, step);
                                from = 'a' + info.p.y;
                                to = 'a' + info.dest.y;
                                cout << "Suggestted move: " << from << 8-info.p.x << " "\
                                << to << 8-info.dest.y << endl;
                                continue;
                            }
                        }
                        
                        else if (cmd == "resign") {
                            resign = true;
                            break;
                        }
                        
                        else if (cmd == "undo") {
                            cin >> v;
                            if (!features[1]) {
                                cout << "Error: undo feature unabled." << endl;
                                continue;
                            }
                            if (v <= 0) {
                                cout << "Error: undo step is not legal.";
                                continue;
                            }
                            else {
                                g.undo(2 * v);
                                cout << g << endl;
                                continue;
                            }
                        }
                        else if (cmd == "history") {
                            cin >> style;
                            if (!features[3]) {
                                cout << "Error: History feature unabled." << endl;
                                continue;
                            }
                            else {
                                try {historyOutput = g.returnHistory(style);}
                                catch (char const* c) {
                                    cout << c << endl;
                                    continue;
                                }
                                for (auto i : historyOutput) {
                                    cout << i << endl;
                                }
                                continue;
                            }

                        }
                        else {
                            if (!features[2]) {
                                cout << "Error: Dynamic input feature unabled." << endl;
                            }
                            else {
                                try {g.dynamicInput(cmd, colour);}
                                catch (string c) {cout << c << endl; continue;}
                                catch (char const* c) {cout << c << endl; continue;}
                                break;
                            }
                        }
                    }

                    if (resign) {g.resign(colour); resign = true; break;}
                }
                if (resign) {break;}
                cout << g << endl;
                if (features[4] && g.alarm()) {
                        alarm++;
                        cout << "Alarrrrrrrrrrrrrrrm!" << endl;
                }
                result = g.whoWon(colour);
                if (alarm >= 3) {
                    cout << "Too many alarms" << endl;
                    cout << "Stalemate!" << endl;
                    g.notifyScore();
                    break;
                }
                if (result == -2) {
                    cout << "Checkmate! White wins!" << endl;
                    break;
                }
                else if (result == -1) {
                    cout << "Black is in check." << endl;
                }
                else if (result == 1) {
                    cout << "White is in check." << endl;
                }
                else if (result == 2) {
                    cout << "Checkmate! Black wins!" << endl;
                    break;
                }
                else if (result == 3) {
                    cout << "Stalemate!" << endl;
                    break;
                }
                cycle += 0.5;
                if (colour == Colour::White) {colour = Colour::Black;}
                else if (colour == Colour::Black) {colour = Colour::White;}
                if (curplayer == fplayer) {curplayer = splayer;}
                else if (curplayer == splayer) {curplayer = fplayer;}
            }
        }
        else {
            cout << "Error: invalid input." << endl;
            continue;
        }
    }
    }
    catch (ios::failure &) {cout << *g.getScore() << endl;}
}

