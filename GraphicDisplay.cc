#include <iostream>
#include <string>
#include <vector>
#include "GraphicDisplay.h"
#include "window.h"
#include "cell.h"
#include "subject.h"
#include "observer.h"
//#include "grid.h"

using namespace std;


GraphicDisplay::GraphicDisplay() {
    //win = make_shared<Xwindow>(27*30, 23*30); //two grids add the middle space
    for (int i = 0; i < 18; ++i) {
            vector<string> v;
            board.emplace_back(v);
            for (int j = 0; j < 11; ++j) {
                board[i].emplace_back("purple");
            }
    }
    for (int i = 0; i < 18; ++i) {
            vector<string> v;
            board.emplace_back(v);
            for (int j = 11; j < 16; ++j) {
                board[i].emplace_back("purple");
            }
    }
    for (int i = 0; i < 18; ++i) {
            vector<string> v;
            board.emplace_back(v);
            for (int j = 16; j < 27; ++j) {
                board[i].emplace_back("purple");
            }
    }

}



void GraphicDisplay::mustDraw(shared_ptr<Xwindow> &win, int i, int j) {
	string color = board[i][j];
        if (color == "red") {
                win->fillRectangle(j*31+1, i*31+101, 30,30, Xwindow::Red);
        }
        if (color == "black") {
                win->fillRectangle(j*31+1, i*31+101,  30,30, Xwindow::Black);
        }
        if (color == "yellow") {
                win->fillRectangle(j*31+1, i*31+101,  30,30, Xwindow::Yellow);
        }
        if (color == "orange") {
               win->fillRectangle(j*31+1, i*31+101,  30,30, Xwindow::Orange);
        }
        if (color == "blue") {
               win->fillRectangle(j*31+1, i*31+101,  30,30, Xwindow::Blue);
	}
	if (color == "green") {
               win->fillRectangle(j*31+1, i*31+101,  30,30, Xwindow::Green);
        }
        if (color == "brown") {
               win->fillRectangle(j*31+1, i*31+101,  30,30, Xwindow::Brown);
        }
        if (color == "grey") {
               win->fillRectangle(j*31+1, i*31+101,  30,30, Xwindow::Grey);
        }
        if (color == "white") {
               win->fillRectangle(j*31+1, i*31+101,  30,30, Xwindow::White);
        }

}





void GraphicDisplay::draw(shared_ptr<Xwindow> &win, int blindPlayer) {
	for (int i = 0; i < 18; ++i) {
		for (int j = 0; j < 27; ++j) {

				if (blindPlayer == 1) {
					if (j >= 2 && j < 9 && i>=5 && i < 15) {
            win->fillRectangle(j*31+1, i*31+101, 30,30, Xwindow::White);
						if (board[i][j] == "purple") {board[i][j] = "white";};
						win->drawString(j*31+10, i*31 + 120, "?");
					} else {
						mustDraw(win, i, j);
					}
				}
				if (blindPlayer == 2) {
					if (j >= 18 && j < 25 && i >= 5 && i <15) {
            win->fillRectangle(j*31+1, i*31+101, 30,30, Xwindow::White);
						if (board[i][j] == "purple") {board[i][j] = "white";}
						win->drawString(j*31+10, i*31 + 120, "?");
					} else {
						mustDraw(win, i, j);
					}
				} else {
				 	mustDraw(win, i, j);
				}
			}
	}
}

void GraphicDisplay::buildBoard(shared_ptr<Xwindow> &win) {
        //display the score board
        // for the first board
//       win->fillRectangle(0, 100, 900, 23*30, Xwindow::Purple); // set color for the background
       int leftOffset = 31*16;
       for (int i = 0; i < 12; ++i) {
            //topoffset is 100
            win->fillRectangle((30+1)*i, 100, 1, 30 * 18 + 19, 1);
            win->fillRectangle((30+1)*i + leftOffset, 100, 1, 30 * 18+19, 1);
       }
       for (int i = 0; i < 19; ++i) {
           win->fillRectangle(0, (30+1)*i+100, 30*11 + 12, 1, 1);
           win->fillRectangle(leftOffset, (30+1)*i+100, 30*11+12, 1, 1);
       }

}



void GraphicDisplay::update(Subject &s) {
    SInfo info = s.getInfo();
    string color = info.color;
    int i = info.row;
    int j = info.col;
    board[i][j] = color;
}




GraphicDisplay::~GraphicDisplay(){}

