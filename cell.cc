#include "cell.h"
#include <iostream>
#include <vector>
#include "subject.h"
#include "TextDisplay.h"
#include "sInfo.h"
#include "block.h"
#include "observer.h"

using namespace std;



Cell::Cell(int p):
	OnState{false}, letter{' '}, levelcreate{0}, x{0}, y{0}, p{p}, width{0},color{"white"}, uppcell{nullptr}, block{nullptr} {}
Cell::~Cell() {
}
void Cell::setBlock(shared_ptr<Block> b) {
    block = b;
}
shared_ptr<Block> Cell::getBlock(){
	return block;
}
void Cell::setOn() {
	OnState = true;
	if(block){
			letter = block->getType();
			color = block->getColor();
	} else {
			letter = ' ';
			color = "white";
	}
	notifyObservers();
}


void Cell::setOff() {
	letter = ' ';
	levelcreate = 0;
	OnState = false;
	color = "white";
	notifyObservers();
}


void Cell::CopyCell(Cell *upper) {
	if (x > 0) {
	    block = upper->block;
	    OnState = upper->OnState;
	    letter = upper->letter;
	    uppcell = upper->uppcell;
	    levelcreate = upper->levelcreate;
	    color = upper->color;
	}

	notifyObservers();
}

void Cell::SetUpper(Cell *upper) {
	uppcell = upper;
}


char Cell::getLetter() {
	return letter;
}
bool Cell::isOn() {
	return OnState;
}
void Cell::setCoord(int xcoord,int ycoord) {
	x = xcoord;
	y = ycoord;
}

SInfo Cell::getInfo(){
	SInfo info;
	info.row = x;
	info.col = y;
	info.type = letter;
    info.p = p;
		info.color=color;
	return info;
}

int Cell::getrow() {
	return x;
}
int Cell::getcol() {
	return y;
}
