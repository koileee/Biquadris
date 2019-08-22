#include <iostream>
#include <utility>
#include "TextDisplay.h"
#include "sInfo.h"
#include "subject.h"
#include "observer.h"

using namespace std;




TextDisplay::TextDisplay(){
	// set up theDisplay
	for (int i = 0; i < 18; i++){
		vector<char> row;
		for (int j = 0; j < 27; j++){
			row.emplace_back(' ');
		}
		board.emplace_back(row);
	}
}


TextDisplay::~TextDisplay(){}


// Cells notyfies me their states changes
void TextDisplay::update(Subject & s) {
	// get the info of the changed cell
	SInfo info = s.getInfo();
	int i = info.row;
	int j = info.col;
	char t = info.type;
	board[i][j] = t;
}




// output td
void TextDisplay::display(ostream &out) {
    for (int i = 0; i < 18; i++){
        for (int j = 0; j < 27; j++){
            out << board[i][j];
        }
        out << endl;
    }
}


// output td
void TextDisplay::blindDis(ostream &out, int p) {
	for (int i = 0; i < 5; i++){
        for (int j = 0; j < 27; j++){
            out << board[i][j];
        }
        out << endl;
    }
	if (p == 1) {
	    for (int i = 5; i < 15; i++) {
	        for (int j = 0; j < 2; j++){
	            out<<board[i][j];
	        }
	        for (int j = 2; j < 9; j++){
	            out<<"?";
	        }
	        for(int j = 9; j < 27; j++){
	            out<<board[i][j];
	        }
	        out<<endl;
	    }
	} else {
	    for (int i = 5; i < 15; i++) {
	        for (int j = 0; j < 18; j++){
	            out<<board[i][j];
	        }
	        for (int j = 18; j < 25; j++){
	            out<<"?";
	        }
	        for (int j = 25; j < 27; j++){
	            out<<board[i][j];
	        }
	        out<<endl;
	    }
	}

	for (int i = 15; i < 18; i++){
	    for (int j = 0; j <27; j++){
	        out<<board[i][j];
	    }
	    out<<endl;
	}
}
