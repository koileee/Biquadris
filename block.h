#ifndef _BLOCK_H_
#define _BLOCK_H_
#include <iostream>
#include <vector>
#include <string>

//don't show cell

class Block{
protected:
    char type;
    int level;
    std::string color;
    int r;
    int c;
    int pieces;
    int state;
    bool isheavy;
    std::vector<std::vector<int>> position;

public:
    Block(char type_, int level_, std::string color_,
    int r_ = 3, int c_ = 0, int pieces_ = 4, int state_ = 0, bool isheavy_ = false);
    virtual ~Block();
    virtual std::vector<std::vector<int>> getCoord() = 0;
    virtual char getType();       // get type
    virtual int getLevel();       //get level
    virtual void losePiece();     //reduce one piece from the block
    virtual bool isCleared();     //checks if block is cleared
    virtual bool isHeavy();       //checks if the block is heavy
    virtual void up();
    virtual void down();
    virtual void left();
    virtual void right();
    virtual void cw();
    virtual void ccw();
    virtual std::string getColor();
};

#endif
