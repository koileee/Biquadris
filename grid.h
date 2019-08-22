#ifndef __GRID_H__
#define __GRID_H__
#include <vector>
#include <memory>
#include <iostream>
#include <string>
#include "level.h"
#include "subject.h"
#include "cell.h"


class Block;
class TextDisplay;
class GraphicDisplay;

//class Xwindow;
//class GraphicDisplay;
class Level;
class Grid{
    int p, lvl, levelscore,  hiScore, heaviness, numBlocks, seed;
    std::string input;
    bool isRandom;
    bool isHeavy;
    std::shared_ptr<TextDisplay> txtDis;  // textdisplay
    std::shared_ptr<GraphicDisplay> gdis; //graphicdisplay
    std::shared_ptr<Block> currBlock;   //current block
    std::shared_ptr<Block> nxtBlock;   //next block
    std::shared_ptr<Level> l;     // current level
    std::vector<std::vector<Cell>> grid;  //the grid


    void updateCell( int row);
    bool valid(std::vector<std::vector<int>>); //checks if the move is valid
    void setBlock(std::shared_ptr<Block> b, std::vector<std::vector<int>> pos);  //sets the cells on the grid at pos to be block b
    void showCell(std::vector<std::vector<int>> pos); // shows the cells at positions pos
    void hideCell(std::vector<std::vector<int>> pos); // hides the cells at positions pos
    void clearRow(int row); //clears the row of the grid at row
    void updateScore(); //updates the score based on how many rows/blocks cleared
    void dropOneBlock(); //drops one block



public:
    Grid(int p, int l, std::string input, std::shared_ptr<TextDisplay> td, std::shared_ptr<GraphicDisplay> gd, int);  //ctor
    void init(bool);  //initializes the grid with boolean argument textOnly
    void changeInputFile(std::string); //changes input file for the grid
    void createCurBlock();  //creates the current block
    void createNextBlock(); //creates the next block
    void placeBlock(); //creates two blocks, places current one on top of the board
    void setLevel(int); //sets the grid's level
    int getPlayer(); //gets which player the grid belongs to
    int getlevel(); // gets grid's current level
    int gethiscore(); // gets hi score
    int getlvlscore(); //gets level score
    void cw(); // clockwise rotate
    void ccw(); //counter clockwise rotate
    void drop(); // drops the block
    void right(); // moves block right
    void left(); // moves block left
    void down(); // moves block down
    void up(); // moves block up
    void restart(); // clears grid, resets level, restarts the game
    void leveldown(); //level up the grid
    void levelup(); // level down the grid
    void setRandom(); //used in level3, sets random
    void NoRandom(); //sets grid to be not random
    void ChangeCurBlock(char t); // changes current block to be type t
    void setHeavy(); //apply grid heavy attack
    void setNotHeavy(); //sets grid free from heavy attack
	void sethiscore(int new_score); // set the highest score for this grid.
    ~Grid();
    char getNextBlock();
};

#endif
