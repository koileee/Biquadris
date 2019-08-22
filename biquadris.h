#ifndef __QUADRIS_H__
#define __QUADRIS_H__
#include <vector>
#include <memory>
#include <iostream>
#include "grid.h"
#include "TextDisplay.h"
#include "window.h"
#include "GraphicDisplay.h"
#include "inherit.h"

class Biquadris{
    std::shared_ptr<Grid> CurGrid; // the grid for the current turn player
    std::shared_ptr<Grid> OtherGrid; // the other grid
    std::shared_ptr<TextDisplay> td;
    std::shared_ptr<GraphicDisplay> gd;
    std::shared_ptr<Xwindow> xw;
    bool textOnly; // will not show graphical display if false
	int seed;
	std::string file1; // the sequence file for player1. default is sequence1.txt
	std::string file2; // the sequence file for player2. default is sequence2.txt
	int startLevel; // the starting level for both player. changed by command-line interface
    int blindplayer; // indicate which player is currently blind
	int heavyplayer; // indicate which player has been applied heavy effect
    void restart(); // restart the game. re-construct everything except the highest score. Will by called in play()
    void runtxtDis(std::ostream &out, int BlindPlayer, std::shared_ptr<Grid> Grid1, std::shared_ptr<Grid> Grid2); // call txtDis. Grid1 can represent player1 or 2. Same for Grid2. If Grid1 is player2, the order of Grid1 and Grid2 will be swapped
    void txtDis(std::ostream &out, int BlindPlayer, std::shared_ptr<Grid> Player1Grid, std::shared_ptr<Grid> Player2Grid); //  print the two grids where player1 on the left and player2 on the right
    void runSequence(std::string fileName); // run the commands in the file called fileName
    void runCommand(std::string command); // run the command other than sequence
    void printSpace(std::ostream &out, int space); // print whitespaces with the number of space
    void printLine(std::ostream &out); // draw line to separate the scoreboard and the grid.
    void runDropException(std::exception &e); // will do specific actions to the thrown exception e. e can be GameOver, SwitchPlayer, or SpecialAction
    void findMultiplierInCommand(std::string &command, std::string &multiStr, int &multi); // change multiStr and multi where multiStr is the actual command part of string command and multi is the number of times the command will be run based on string command
    bool CompareStr(std::string Str1, std::string Str2); // return true if the two strings have the same first two characters. Uppercase and lowercase represent the same letter
    std::vector<std::vector<int>> getCoord(char type);
    void graphDisplay(std::shared_ptr<Xwindow> &win);
    int change_to(char t);
    void clearNext(std::shared_ptr<Xwindow> &win);

    public:
    Biquadris(bool textOnly, int seed, std::string file1, std::string file2, int startLevel);
    ~Biquadris();
    void play(); // take from input to play the game
};

#endif
