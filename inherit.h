#ifndef _INHERI_BLOCK_H_
#define _INHERI_BLOCK_H_
#include <iostream>
#include <string>
#include "block.h"


class I_Block : public Block{
public:
    I_Block(char type_, int level_, std::string color_,
    int r_ = 3, int c_ = 0, int pieces_ = 4, int state_ = 0, bool isheavy_ = false);
    ~I_Block();
    std::vector<std::vector<int>> getCoord() override;
//    void I_Block::changeType(char type_);    
};


class J_Block : public Block{
public:
    J_Block(char type_, int level_, std::string color_,
    int r_ = 3, int c_ = 0, int pieces_ = 4, int state_ = 0, bool isheavy_ = false);
    ~J_Block();
    std::vector<std::vector<int>> getCoord() override;
//    void J_Block::changeType(char type_);
};

class L_Block : public Block{
public:
    L_Block(char type_, int level_, std::string color_,
    int r_ = 3, int c_ = 0, int pieces_ = 4, int state_ = 0, bool isheavy_ = false);
    ~L_Block();
    std::vector<std::vector<int>> getCoord() override;
//    void L_Block::changeType(char type_) override;
};

class S_Block : public Block{
public:
    S_Block(char type_, int level_, std::string color_,
    int r_ = 3, int c_ = 0, int pieces_ = 4, int state_ = 0, bool isheavy_ = false);
    ~S_Block();
    std::vector<std::vector<int>> getCoord() override;
//    void S_Block::changeType(char type_) override;
};

class T_Block : public Block{
public:
    T_Block(char type_, int level_, std::string color_,
    int r_ = 3, int c_ = 0, int pieces_ = 4, int state_ = 0, bool isheavy_ = false);
    ~T_Block();
    std::vector<std::vector<int>> getCoord() override;
//    void T_Block::changeType(char type_) override;
};


class O_Block : public Block{
public:
    O_Block(char type_, int level_, std::string color_,
    int r_ = 3, int c_ = 0, int pieces_ = 4, int state_ = 0, bool isheavy_ = false);
    ~O_Block();
    std::vector<std::vector<int>> getCoord() override;
//    void O_Block::changeType(char type_) override;
};


class Z_Block : public Block{
public:
    Z_Block(char type_, int level_, std::string color_,
    int r_ = 3, int c_ = 0, int pieces_ = 4, int state_ = 0, bool isheavy_ = false);
    ~Z_Block();
    std::vector<std::vector<int>> getCoord() override;
//    void Z_Block::changeType(char type_) override;;
};

class One_Block : public Block{
public:
    One_Block(char type_ = '*', int level_ = 4, std::string color_="Brown",
    int r_ = 0, int c_ = 5, int pieces_ = 1, int state_ = 0, bool isheavy_ = false);
    ~One_Block();
    std::vector<std::vector<int>> getCoord() override;
};


#endif
