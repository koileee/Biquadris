#include <iostream>
#include <vector>
#include <string>
#include "block.h"
#include "inherit.h"

using namespace std;


J_Block::J_Block(char type_, int level_, string color_,
    int r_, int c_, int pieces_, int state_, bool isheavy_):
    Block(type_, level_, color_,
    r_, c_, pieces_, state_, isheavy_) {}


J_Block::~J_Block() {}

vector<vector<int>> J_Block::getCoord() {
    position.clear();
    if(state == 0){
        vector<int> pos1{r-1, c};
        vector<int> pos2{r, c};
        vector<int> pos3{r, c+1};
        vector<int> pos4{r, c+2};
        position.emplace_back(pos1);
        position.emplace_back(pos2);
        position.emplace_back(pos3);
        position.emplace_back(pos4);
    } else if (state == 1) {
	vector<int> pos1{r-2, c};
        vector<int> pos2{r-2, c+1};
        vector<int> pos3{r-1, c};
        vector<int> pos4{r, c};
        position.emplace_back(pos1);
        position.emplace_back(pos2);
        position.emplace_back(pos3);
        position.emplace_back(pos4);
   } else if (state == 2) {
          vector<int> pos1{r-1, c};
           vector<int> pos2{r-1, c+1};
           vector<int> pos3{r-1, c+2};
           vector<int> pos4{r, c+2};
           position.emplace_back(pos1);
           position.emplace_back(pos2);
           position.emplace_back(pos3);
           position.emplace_back(pos4);
   } else {
	      vector<int> pos1{r, c};
        vector<int> pos2{r, c+1};
        vector<int> pos3{r-1, c+1};
        vector<int> pos4{r-2, c+1};
        position.emplace_back(pos1);
        position.emplace_back(pos2);
        position.emplace_back(pos3);
        position.emplace_back(pos4);
   }
   return position;
}





I_Block::I_Block(char type_, int level_, string color_,
    int r_, int c_, int pieces_, int state_, bool isheavy_):
    Block(type_, level_, color_,
    r_, c_, pieces_, state_, isheavy_) {}


I_Block::~I_Block() {}


vector<vector<int>> I_Block::getCoord() {
    position.clear();
    if(state == 0 || state == 2){
        vector<int> pos1{r, c};
        vector<int> pos2{r, c+1};
        vector<int> pos3{r, c+2};
        vector<int> pos4{r, c+3};
        position.emplace_back(pos1);
        position.emplace_back(pos2);
        position.emplace_back(pos3);
        position.emplace_back(pos4);
    } else {
	vector<int> pos1{r, c};
        vector<int> pos2{r-1, c};
        vector<int> pos3{r-2, c};
        vector<int> pos4{r-3, c};
        position.emplace_back(pos1);
        position.emplace_back(pos2);
        position.emplace_back(pos3);
        position.emplace_back(pos4);
    }
    return position;
}


L_Block::L_Block(char type_, int level_, string color_,
    int r_, int c_, int pieces_, int state_, bool isheavy_):
    Block(type_, level_, color_, r_, c_, pieces_, state_, isheavy_) {}

L_Block::~L_Block() {}

vector<vector<int>> L_Block::getCoord() {
    position.clear();
    if(state == 0){
        vector<int> pos1{r-1, c+2};
        vector<int> pos2{r, c};
        vector<int> pos3{r, c+1};
        vector<int> pos4{r, c+2};
        position.emplace_back(pos1);
        position.emplace_back(pos2);
        position.emplace_back(pos3);
        position.emplace_back(pos4);
    } else if (state == 1) {
        vector<int> pos1{r-2, c};
        vector<int> pos2{r-1, c};
        vector<int> pos3{r, c};
        vector<int> pos4{r, c+1};
        position.emplace_back(pos1);
        position.emplace_back(pos2);
        position.emplace_back(pos3);
        position.emplace_back(pos4);

    } else if (state == 2) {
        vector<int> pos1{r-1, c+2};
        vector<int> pos2{r-1, c+1};
        vector<int> pos3{r-1, c};
        vector<int> pos4{r, c};
        position.emplace_back(pos1);
        position.emplace_back(pos2);
        position.emplace_back(pos3);
        position.emplace_back(pos4);
    } else {
	vector<int> pos1{r-2, c};
        vector<int> pos2{r-2, c+1};
        vector<int> pos3{r-1, c+1};
        vector<int> pos4{r, c+1};
        position.emplace_back(pos1);
        position.emplace_back(pos2);
        position.emplace_back(pos3);
        position.emplace_back(pos4);
    }
    return position;
}


O_Block::O_Block(char type_, int level_, string color_,
    int r_, int c_, int pieces_, int state_, bool isheavy_):
    Block(type_, level_, color_,
    r_, c_, pieces_, state_, isheavy_) {}

O_Block::~O_Block() {}

vector<vector<int>> O_Block::getCoord() {
    position.clear();
    vector<int> pos1{r, c};
    vector<int> pos2{r, c+1};
    vector<int> pos3{r-1, c};
    vector<int> pos4{r-1, c+1};
    position.emplace_back(pos1);
    position.emplace_back(pos2);
    position.emplace_back(pos3);
    position.emplace_back(pos4);
    return position;
}



Z_Block::Z_Block(char type_, int level_, string color_,
    int r_, int c_, int pieces_, int state_, bool isheavy_):
    Block(type_, level_, color_,
    r_, c_, pieces_, state_, isheavy_) {}

Z_Block::~Z_Block() {}

vector<vector<int>> Z_Block::getCoord() {
    position.clear();
    if(state == 0 || state == 2){
        vector<int> pos1{r-1, c};
        vector<int> pos2{r-1, c+1};
        vector<int> pos3{r, c+1};
        vector<int> pos4{r, c+2};
        position.emplace_back(pos1);
        position.emplace_back(pos2);
        position.emplace_back(pos3);
        position.emplace_back(pos4);
    } else {
	vector<int> pos1{r-2, c+1};
        vector<int> pos2{r-1, c};
        vector<int> pos3{r-1, c+1};
        vector<int> pos4{r, c};
        position.emplace_back(pos1);
        position.emplace_back(pos2);
        position.emplace_back(pos3);
        position.emplace_back(pos4);
    }
    return position;
}




T_Block::T_Block(char type_, int level_, string color_,
    int r_, int c_, int pieces_, int state_, bool isheavy_):
    Block(type_, level_, color_,
    r_, c_, pieces_, state_, isheavy_) {}

T_Block::~T_Block() {}

vector<vector<int>> T_Block::getCoord() {
    position.clear();
    if(state == 0){
        vector<int> pos1{r-1, c};
        vector<int> pos2{r-1, c+1};
        vector<int> pos3{r-1, c+2};
        vector<int> pos4{r, c+1};
        position.emplace_back(pos1);
        position.emplace_back(pos2);
        position.emplace_back(pos3);
        position.emplace_back(pos4);
    } else if (state == 1) {
	vector<int> pos1{r-2, c+1};
        vector<int> pos2{r-1, c};
        vector<int> pos3{r-1, c+1};
        vector<int> pos4{r, c+1};
        position.emplace_back(pos1);
        position.emplace_back(pos2);
        position.emplace_back(pos3);
        position.emplace_back(pos4);

    } else if (state == 2) {
	vector<int> pos1{r-1, c+1};
        vector<int> pos2{r, c};
        vector<int> pos3{r, c+1};
        vector<int> pos4{r, c+2};
        position.emplace_back(pos1);
        position.emplace_back(pos2);
        position.emplace_back(pos3);
        position.emplace_back(pos4);
    } else {
	vector<int> pos1{r-2, c};
        vector<int> pos2{r-1, c};
        vector<int> pos3{r-1, c+1};
        vector<int> pos4{r, c};
        position.emplace_back(pos1);
        position.emplace_back(pos2);
        position.emplace_back(pos3);
        position.emplace_back(pos4);
    }
    return position;
}


S_Block::S_Block(char type_, int level_, string color_,
    int r_, int c_, int pieces_, int state_, bool isheavy_):
    Block(type_, level_, color_,
    r_, c_, pieces_, state_, isheavy_) {}

S_Block::~S_Block() {}

vector<vector<int>> S_Block::getCoord() {
    position.clear();
    if(state == 0 || state == 2){
        vector<int> pos1{r, c};
        vector<int> pos2{r, c+1};
        vector<int> pos3{r-1, c+1};
        vector<int> pos4{r-1, c+2};
        position.emplace_back(pos1);
        position.emplace_back(pos2);
        position.emplace_back(pos3);
        position.emplace_back(pos4);
    } else {
	vector<int> pos1{r-2, c};
        vector<int> pos2{r-1, c};
        vector<int> pos3{r-1, c+1};
        vector<int> pos4{r, c+1};
        position.emplace_back(pos1);
        position.emplace_back(pos2);
        position.emplace_back(pos3);
        position.emplace_back(pos4);
    }
    return position;
}

One_Block::One_Block(char type_, int level_, string color_,
    int r_, int c_, int pieces_, int state_, bool isheavy_):
    Block(type_, level_, color_,
    r_, c_, pieces_, state_, isheavy_) {}


One_Block::~One_Block() {}


vector<vector<int>> One_Block::getCoord() {
        position.clear();
        vector<int> pos{r,c};
        position.emplace_back(pos);
        return position;
}
