#include <iostream>
#include <memory>
#include <string>
#include "grid.h"
#include "level.h"
#include "cell.h"
#include "block.h"
#include "inherit.h"
#include "subject.h"
#include "exception.h"
#include "observer.h"
#include "GraphicDisplay.h"


using namespace std;

class TextDisplay;
Grid::Grid(int p_, int l_, string input_, shared_ptr<TextDisplay> td, shared_ptr<GraphicDisplay> gd, int s = 1):
	p{p_}, lvl{l_}, levelscore{0}, hiScore{0}, heaviness{0}, numBlocks{0}, seed{s}, input{input_}, isRandom{false},
	isHeavy{false}, txtDis{td}, gdis{gd}, currBlock{nullptr},  nxtBlock{nullptr},  l{nullptr}  {
    l = Level::make_level(lvl);
    if (l_ >= 3) {
		isHeavy = true;
		heaviness = 1;
    }
    if (l_ > 0) {
		isRandom = true;
    }
	srand(seed);
}

Grid::~Grid() {}

void Grid::init(bool textOnly) {
    levelscore=0;
    grid = vector<vector<Cell>>(18, vector<Cell>(11, Cell(p)));
    for (int i = 0; i < 18; i++){
	for (int j = 0; j < 11; j++){
		if (i != 0) {
			grid[i][j].SetUpper(&(grid[i-1][j]));
		}
		if (p==1) {
		    grid[i][j].setCoord(i, j);
		} else {
		    grid[i][j].setCoord(i, j+16);
		}
		grid[i][j].attach(gdis);
		grid[i][j].attach(txtDis);

	}
    }
}

void Grid::restart() {
	levelscore = 0;
	for (int i = 0; i < 18; i++){
		for (int j = 0; j < 27; j++){
			grid[i][j].setOff();
		}
	}
}

void Grid::changeInputFile(string file) {
    if (lvl >= 3) {
    	input = file;
    	l = Level::make_level(lvl);
    	isRandom = false;
    } else {
	cout << "You're not in level 3 or level 4" << endl;
    }
}

bool Grid::valid(vector<vector<int>> pos){
	for (auto& it : pos) {
	    int r = it[0];
	    int c = it[1];
	    if (r < 0 || r > 17 || c < 0 || c > 10 || grid[r][c].isOn()) {
	        return false;
	    }
	}
	return true;
}

void Grid::createCurBlock() {
    char blockType=l->generateBlock(input,isRandom);
    if (blockType == 'S'){
         currBlock = make_shared<S_Block>(blockType, lvl, "red");
    } else if (blockType == 'Z'){
         currBlock = make_shared<Z_Block>(blockType, lvl, "orange");
    } else if (blockType == 'I'){
         currBlock = make_shared<I_Block>(blockType, lvl, "yellow");
    } else if (blockType == 'J') {
         currBlock = make_shared<J_Block>(blockType, lvl, "green");
    } else if (blockType == 'L') {
         currBlock = make_shared<L_Block>(blockType, lvl, "blue");
    } else if (blockType == 'O') {
         currBlock = make_shared<O_Block>(blockType, lvl, "black");
    }else if (blockType == 'T') {
         currBlock = make_shared<T_Block>(blockType, lvl, "grey");
    } else {
         currBlock = nullptr;
    }
    if (currBlock) {
        vector<vector<int>> pos = currBlock->getCoord();
        if (!valid(pos)) {throw GameOver("GameOver");}
        setBlock(currBlock, pos);
        showCell(pos);
    }
}

void Grid::createNextBlock() {
    char blockType=l->generateBlock(input, isRandom);
    if (blockType == 'S'){
        nxtBlock = make_shared<S_Block>(blockType, lvl, "red");
    } else if (blockType == 'Z'){
        nxtBlock = make_shared<Z_Block>(blockType, lvl, "orange");
    } else if (blockType == 'I'){
        nxtBlock = make_shared<I_Block>(blockType, lvl, "yellow");
    } else if (blockType == 'J') {
        nxtBlock = make_shared<J_Block>(blockType, lvl, "green");
    } else if (blockType == 'L') {
        nxtBlock = make_shared<L_Block>(blockType, lvl, "blue");
    } else if (blockType == 'O') {
        nxtBlock = make_shared<O_Block>(blockType, lvl, "black");
    }else if (blockType == 'T') {
        nxtBlock = make_shared<T_Block>(blockType, lvl, "grey");
    } else {
        nxtBlock = nullptr;
    }
}

char Grid::getNextBlock() {
	return nxtBlock->getType();
}

void Grid::dropOneBlock() {
    vector<vector<int>> prev = currBlock->getCoord();
	vector<vector<int>> curr = currBlock->getCoord();
	hideCell(prev);
	setBlock(nullptr, prev);
	while (valid(curr)) {
	    currBlock->down();
	    curr = currBlock->getCoord();
	}
	currBlock->up();
	vector<vector<int>> now = currBlock->getCoord();
	setBlock(currBlock, now);
	showCell(now);
	updateScore();
}

void Grid::placeBlock() {
    if (numBlocks%5==0 && lvl == 4  && numBlocks!=0) {
        currBlock = make_shared<One_Block>('*', lvl,"brown");
        dropOneBlock();
        numBlocks = 0;
    }

    currBlock = nxtBlock;
    createNextBlock();
    vector<vector<int>> pos = currBlock->getCoord();
    if (!valid(pos)) {
	throw GameOver("GameOver");
    } else {
    	setBlock(currBlock, pos);
        showCell(pos);
    }
}

void Grid::showCell(vector<vector<int>> pos){
	for (auto& it : pos){
		int x = it[0];
		int y = it[1];
		grid[x][y].setOn();
		//cout<<x<<", "<<y<<endl;
	}
}

void Grid::hideCell(vector<vector<int>> pos){
	for (auto& it : pos){
		int x = it[0];
		int y = it[1];
		grid[x][y].setOff();
	}
}

void Grid::setBlock(shared_ptr<Block> b, vector<vector<int>> pos ) {
    for (auto& it : pos){
		int r = it[0];
		int c = it[1];
		grid[r][c].setBlock(b);
	}
}


void Grid::clearRow(int row) {
    numBlocks = 0;
    if (row > 0) {
        for (int i = row; i > 0; i--) {
	    	for (int j = 0; j < 11; ++j) {
			if (grid[i][j].getBlock() != nullptr) {
				if (i == row) {
				auto b = grid[i][j].getBlock();
				b->losePiece();
// check if a whole block is diminished
				if (b->isCleared()) {
								levelscore += (b->getLevel() + 1)*(b->getLevel() + 1);
					}
                                }
					grid[i][j].CopyCell(&grid[i-1][j]) ;

			}

       	     	}
        }

    }

    for (int i = 0; i < 11; ++i) {
	grid[0][i].setOff();
    }

}

void Grid::updateScore() {
    	int rowscleared = 0;
    	bool clear = false;
	for (int i = 0; i < 18; i++) {
	    bool isClear = true;
	    for (int j = 0; j < 11; j++){
		// check if all the cell in the row are On
		if (!grid[i][j].isOn()) {
			isClear = false;
		}
	    }
	    if (isClear) {
	        clear = true;
	        clearRow(i);
	        ++rowscleared;
	    }
	}
	if (clear) {
	    levelscore += (lvl+rowscleared)*(lvl+rowscleared);
	    if (levelscore > hiScore) {hiScore = levelscore;}
	}

	if (rowscleared >= 2) {
	    throw SpecialAction{"SpecialAction"};
	}
}

void Grid::setLevel(int level) {
	l = Level::make_level(level);
}

int Grid::getPlayer() {
    return p;
}

//score
int Grid::getlevel() {
	return lvl;
}

int Grid::gethiscore(){
	return hiScore;
}

int Grid::getlvlscore(){
	return levelscore;
}

void Grid::cw(){
	vector<vector<int>> prev = currBlock->getCoord();
	currBlock->cw();
	vector<vector<int>> curr = currBlock->getCoord();
	hideCell(prev);
	if (valid(curr)){
	    if (isHeavy) {
	        currBlock->down();
	        if (!valid(currBlock->getCoord())) {
	            currBlock->up();
	            drop();
	            return;
		}
	    }
	    curr = currBlock->getCoord();
	    setBlock(nullptr, prev);
	    setBlock(currBlock, curr);
	    showCell(curr);
	} else {
	    currBlock->ccw();
            showCell(prev);
	}
}



void Grid::ccw(){
	vector<vector<int>> prev = currBlock->getCoord();
	currBlock->ccw();
	vector<vector<int>> curr = currBlock->getCoord();
	hideCell(prev);
	if (valid(curr)){
	    if (isHeavy) {
	        currBlock->down();
	        if (!valid(currBlock->getCoord())) {
	             currBlock->up();
	  	//reset heaviness
                     drop();
                     return;
	        }
	    }
	    curr = currBlock->getCoord();
	    setBlock(nullptr, prev);
	    setBlock(currBlock, curr);
	    showCell(curr);
	} else {
		currBlock->cw();
		showCell(prev);
	}
}

void Grid::right(){
	vector<vector<int>> prev = currBlock->getCoord();
	currBlock->right();
	vector<vector<int>> curr = currBlock->getCoord();
	hideCell(prev);
	if (valid(curr)){
	    if (isHeavy) {
	        for (int i = 0; i < heaviness + 1; i++) {
	            currBlock->down();
	            if (!valid(currBlock->getCoord())) {
	                currBlock->up();
	                drop();
	                break;
	            }
	        }
	    } else {
                for (int i = 0; i < heaviness; ++i) {
                     currBlock->down();
                     if (!valid(currBlock->getCoord())) {
                        currBlock->up();
                        drop();
                        break;
                     }
		}
            }
	    curr = currBlock->getCoord();
	    setBlock(nullptr, prev);
		setBlock(currBlock, curr);
		showCell(curr);
	} else {
		currBlock->left();
		showCell(prev);
	}
}

void Grid::left(){
	vector<vector<int>> prev = currBlock->getCoord();
	currBlock->left();
	vector<vector<int>> curr = currBlock->getCoord();
	hideCell(prev);
	if (valid(curr)){
	    if (isHeavy) {
	        for (int i = 0; i < heaviness + 1; i++) {
	            currBlock->down();
	            if (!valid(currBlock->getCoord())) {
	                currBlock->up();
	                drop();
	                break;
	            }
	        }
	    } else {
                for (int i = 0; i < heaviness; ++i) {
                     currBlock->down();
                     if (!valid(currBlock->getCoord())) {
                        currBlock->up();
                        drop();
                        break;
                     }
		}
            }
	    curr = currBlock->getCoord();
	    setBlock(nullptr, prev);
		setBlock(currBlock, curr);
		showCell(curr);
	} else {
		currBlock->right();
		showCell(prev);
	}
}

void Grid::up(){
    vector<vector<int>> prev = currBlock->getCoord();
	currBlock->up();
	vector<vector<int>> curr = currBlock->getCoord();
	hideCell(prev);
	curr = currBlock->getCoord();
	setBlock(nullptr, prev);
	setBlock(currBlock, curr);
	showCell(curr);
}


// ?
void Grid::down(){
    vector<vector<int>> prev = currBlock->getCoord();
	currBlock->down();
	vector<vector<int>> curr = currBlock->getCoord();
	hideCell(prev);
	if (valid(curr)){
	    curr = currBlock->getCoord();
	    setBlock(nullptr, prev);
	    setBlock(currBlock, curr);
	    showCell(curr);
	} else {
	    currBlock->up();
	    showCell(prev);
	}
}

void Grid::drop(){
	heaviness = 0;
        ++numBlocks;
	vector<vector<int>> prev = currBlock->getCoord();
	vector<vector<int>> curr = currBlock->getCoord();
	hideCell(prev);
	setBlock(nullptr, prev);
	while (valid(curr)) {
	    currBlock->down();
	    curr = currBlock->getCoord();
	}
	currBlock->up();
	vector<vector<int>> now = currBlock->getCoord();
	setBlock(currBlock, now);
	showCell(now);
	updateScore();
	throw SwitchPlayer{"SwitchPlayer"};
}

void Grid::levelup() {
	if (lvl < 4) {
	   ++lvl;
	    setLevel(lvl);
	    if (lvl >= 3){
	        isHeavy = true;
	    } else {
	        isHeavy = false;
	    }
	} else {
	    cout << "Cannnot level up. Highest level reached." << endl;
	}
}

void Grid::leveldown(){
    if (lvl > 0) {
        --lvl;
        setLevel(lvl);
        if (lvl >= 3){
        	isHeavy = true;
	} else {
   		isHeavy = false;
	}
    } else {
        cout << "Cannot level down. Lowest level reached." << endl;
    }
}

void Grid::setHeavy(){
   if(lvl>=3){ isHeavy = true;}
    heaviness += 2;
}

void Grid::setNotHeavy(){
    if (lvl < 3) {
        isHeavy = false;
	heaviness = 0;
    } else {
        isHeavy = true;
        --heaviness;
    }
}

void Grid::setRandom(){
    isRandom = true;
}

void Grid::NoRandom(){
    isRandom = false;
}

void Grid::ChangeCurBlock(char t) {
        vector<vector<int>> prev = currBlock->getCoord();
        shared_ptr<Block> newBlock;
        if (t == 'S'){
            newBlock = make_shared<S_Block>(t, lvl, "red");
        } else if (t == 'Z') {
            newBlock = make_shared<Z_Block>(t, lvl, "orange");
        } else if (t == 'I') {
            newBlock = make_shared<I_Block>(t, lvl, "yellow");
        } else if (t == 'J') {
            newBlock = make_shared<J_Block>(t, lvl, "green");
        } else if (t == 'L') {
            newBlock = make_shared<L_Block>(t, lvl, "blue");
        } else if (t == 'O') {
            newBlock = make_shared<O_Block>(t, lvl, "black");
        }else if (t == 'T') {
            newBlock = make_shared<T_Block>(t, lvl, "grey");
        } else {
            cout << "Unknown Block Type" << endl;
            return;
        }
        vector<vector<int>> curr = newBlock->getCoord();
				setBlock(nullptr, prev);
        hideCell(prev);
        if (valid(curr)) {
                currBlock = newBlock; // copy
								setBlock(currBlock, curr);
                showCell(curr);
        } else {
						setBlock(currBlock, prev);
            showCell(prev);
        }
}

void Grid::sethiscore(int new_score) {
	hiScore = new_score;
}
