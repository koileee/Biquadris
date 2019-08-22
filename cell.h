#ifndef __CELL_H__
#define __CELL_H__
#include <vector>
#include <iostream>
#include "subject.h"
#include "TextDisplay.h"
#include "sInfo.h"
#include "block.h"


class Cell: public Subject {
	bool OnState;
	char letter;
	int levelcreate;
	int x;
	int y;
	int p;
	int width;
	std::string color;
	Cell *uppcell;
	std::shared_ptr<Block> block;
public:
	Cell(int p);
	~Cell();
	void setBlock(std::shared_ptr<Block>); // change the block field to the argument
	std::shared_ptr<Block> getBlock(); // return the block field
	void setOn(); // change the cell to the state that there is a block on it
	void setOff(); // change the cell that nothing is on it
	void CopyCell(Cell *upper); // when call this, the coordinates are all set up. CopyCell will copy all contents of the Cell pointer upper except x, y, width
	void SetUpper(Cell *upper); // set the uppcell field to the input upper
	char getLetter(); // return the field letter
	bool isOn(); // return the field OnState
	void setCoord(int xcoord,int ycoord); // change the field x and y
	int getrow(); // return the field x
	SInfo getInfo(); // return a SInfo containing x, y, letter, p, color
	int getcol(); // return the field y
};

#endif
