#include <iostream>
#include <vector>
#include <string>
#include "block.h"

using namespace std;

char Block::getType(){
	return type;
}

int Block::getLevel(){
	return level;
}


Block::Block(char type_, int level_, string color_,
    int r_, int c_, int pieces_, int state_, bool isheavy_):
    type{type_}, level{level_}, color{color_}, r{r_}, c{c_}, pieces{pieces_},
    state{state_}, isheavy{isheavy_} {
	if (level_ >= 3) {
		isheavy = true;
	}
}

Block::~Block(){}

bool Block::isHeavy(){
	return isheavy;
}

void Block::losePiece(){
	--pieces;
}

bool Block::isCleared(){
	return (pieces == 0);
}

void Block::up(){
	--r;
}
void Block::down(){
	++r;
}
void Block::left(){
	--c;
}
void Block::right(){
	++c;
}
void Block::cw(){
	state = (state+1)%4;
}
void Block::ccw(){
	state = (state+3)%4;
}

string Block::getColor(){
	return color;
}
