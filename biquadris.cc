#include "biquadris.h"
#include <memory>
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define DOWN "down"
#define LEFT "left"
#define RIGHT "right"
#define DROP "drop"
#define CLOCKWISE "clockwise"
#define CW "cw"
#define COUNTERCLOCKWISE "counterclockwise"
#define CCW "ccw"
#define LEVELUP1 "levelup"
#define LEVELUP2 "levelu"
#define LEVELDOWN1 "leveldown"
#define LEVELDOWN2 "leveld"
#define SEQUENCE "sequence"
#define RANDOM "random"
#define NORANDOM "norandom"
#define RESTART "restart"
#define BLIND "blind"
#define HEAVY "heavy"
#define FORCE "force"

using namespace std;

class Exception {
public:
   Exception(const string& msg) : msg_(msg) {}
  ~Exception() {}
   string getType() const {return(msg_);}
private:
   string msg_;
};

Biquadris::Biquadris(bool textOnly, int seed, string file1, string file2, int startLevel):
    textOnly{textOnly},
    seed{seed},
    file1{file1},
    file2{file2},
    startLevel{startLevel},
    blindplayer{0},
    heavyplayer{0}
    {
    td = make_shared<TextDisplay>();
    gd = make_shared<GraphicDisplay>();
    if (!textOnly) {xw = make_shared<Xwindow>();} else {xw = nullptr;}


    CurGrid = make_shared<Grid>(1, startLevel, file1, td, gd, seed);
    OtherGrid = make_shared<Grid>(2, startLevel, file2, td, gd, seed);
    CurGrid->init(textOnly);
    OtherGrid->init(textOnly);
    }

Biquadris::~Biquadris() {
}

vector<vector<int>> Biquadris::getCoord(char type) {
    vector<vector<int>> i(4, vector<int>(2,1));
    if (type == 'S') {
        S_Block b = S_Block{'s',0,"white"};
        i = b.getCoord();
    }
    if (type == 'Z') {
        Z_Block b = Z_Block{'Z',0,"white"};
        i = b.getCoord();
    }
    if (type == 'I') {
        I_Block b = I_Block{'I',0,"white"};
        i = b.getCoord();
    }
    if (type == 'J') {
        J_Block b = J_Block{'J',0,"white"};
        i = b.getCoord();
    }
    if (type == 'L') {
        L_Block b = L_Block{'L',0,"white"};
        i = b.getCoord();
    }
    if (type == 'O') {
        O_Block b = O_Block{'O',0,"white"};
        i = b.getCoord();
    }
    if (type == 'T') {
        T_Block b = T_Block{'T',0,"white"};
        i = b.getCoord();
    }
    return i;
}

void Biquadris::graphDisplay(shared_ptr<Xwindow> &win){
  int p1l;
  int p2l;
  int p1his;
  int p2his;
  int p1s;
  int p2s;
  if (CurGrid->getPlayer() == 1) {
    p1l=CurGrid->getlevel();
    p1his = CurGrid->gethiscore();
    p1s = CurGrid->getlvlscore();
    p2l=OtherGrid->getlevel();
    p2his = OtherGrid->gethiscore();
    p2s = OtherGrid->getlvlscore();
  } else {
    p2l=CurGrid->getlevel();
    p2his = CurGrid->gethiscore();
    p2s = CurGrid->getlvlscore();
    p1l=OtherGrid->getlevel();
    p1his = OtherGrid->gethiscore();
    p1s = OtherGrid->getlvlscore();

  }
  win->fillRectangle(0, 0, 900, 100, 0);
  win->drawString(10, 20, "Player1");
  win->drawString(31*16, 20, "Player2");
  win->drawString(10,  40, "hiScore:");
  win->drawString(70, 40, to_string(p1his));
  win->drawString(31*16, 40, "hiScore:");
  win->drawString(31*16+60, 40, to_string(p2his));
  win->drawString(10, 60, "score:");
  win->drawString(70, 60, to_string(p1s));
  win->drawString(31*16, 60, "score:");
  win->drawString(31*16+60, 60, to_string(p2s));
  win->drawString(10, 80, "level:");
  win->drawString(70, 80, to_string(p1l));
  win->drawString(31*16,80,"level:");
  win->drawString(31*16+60, 80, to_string(p2l));
  gd->draw(win, blindplayer);
  win->drawString(0, 150+30*18, "Next:");
  win->drawString(31*16, 150+30*18, "Next:");
  char type_1, type_2;
  if (CurGrid->getPlayer() == 1) {
    type_1 = CurGrid->getNextBlock();
    type_2 = OtherGrid->getNextBlock();
  } else {
    type_2 = CurGrid->getNextBlock();
    type_1 = OtherGrid->getNextBlock();
  }
  int Color_1 = change_to(type_1);
  int Color_2 = change_to(type_2);

  //find the coordinates
  vector<vector<int>> curr = getCoord(type_1);
  vector<vector<int>> other = getCoord(type_2);
  for (auto& it : curr) {
	    int r = it[0];
	    int c = it[1];
      win->fillRectangle(c*31, (r+21)*31, 30, 30, Color_1);
    }
  for (auto& it : other) {
        int r = it[0];
        int c = it[1];
        win->fillRectangle((c+16)*31, (r+21)*31, 30, 30, Color_2);
    }
}

int  Biquadris::change_to(char t) {
        if (t == 'S') {
              return 2;
        }
        if (t == 'O') {
              return 1;
        }
        if (t == 'I') {
              return 8;
        }
        if (t == 'Z') {
              return 5;
        }
        if (t == 'L') {
              return 4;
        }
        if (t == 'J') {
              return 3;
        }
        if (t == 'T') {
              return 6;
        } else {
            return 7;
        }
}

void Biquadris::clearNext(shared_ptr<Xwindow> &win){
  char type_1, type_2;
  if (CurGrid->getPlayer() == 1) {
    type_1 = CurGrid->getNextBlock();
    type_2 = OtherGrid->getNextBlock();
  } else {
    type_2 = CurGrid->getNextBlock();
    type_1 = OtherGrid->getNextBlock();
  }

  vector<vector<int>> curr = getCoord(type_1);
  vector<vector<int>> other = getCoord(type_2);
  for (auto& it : curr) {
      int r = it[0];
      int c = it[1];
      win->fillRectangle(c*31, (r+21)*31, 30, 30, 0);
    }
  for (auto& it : other) {
        int r = it[0];
        int c = it[1];
        win->fillRectangle((c+16)*31, (r+21)*31, 30, 30, 0);
    }

}

string lowerCase(string str) {
	string result;
	for (auto c:str) {
		if ((c >= 'A') && (c <= 'Z')) {
		    c = c + 'a' - 'A';
		}
		result = result + c;
	}
	return result;
}

bool Biquadris::CompareStr(string Str1, string Str2) {
	string str = lowerCase(Str1);
	if (Str1.length() < 2 || Str2.length() < 2) {
		return false;
	} else if ((str[0] != Str2[0]) || (str[1] != Str2[1])) {
		return false;
	} else {
		return true;
	}
}



void Biquadris::play() {
	string command;
	string multiStr;
    int multi = 1;

	CurGrid->createCurBlock();
	CurGrid->createNextBlock();
    OtherGrid->createCurBlock();
    OtherGrid->createNextBlock();

    runtxtDis(cout, blindplayer, CurGrid, OtherGrid);
    if (!textOnly) {
        gd->buildBoard(xw);
        graphDisplay(xw);
    }

    while(true) {
    	cout << "Input a command for player" << CurGrid->getPlayer() << endl;
        cin >> command;
        if (cin.eof() || cin.fail()) break;

        findMultiplierInCommand(command, multiStr, multi);

        if (CompareStr(command, SEQUENCE)) {
        	cin >> command;
        	for (int i = 0; i < multi; ++i) {
        		runSequence(command);
        	}
        } else if (CompareStr(command, RESTART) || CompareStr(command, NORANDOM) || CompareStr(command, RANDOM)) {
        	runCommand(command);
        } else {
        	for (int i = 0; i < multi; ++i) {
				runCommand(command);
			}
        }

        multiStr = "";
        multi = 1;
    }
}

void Biquadris::runSequence(string fileName) {
	ifstream myfile{fileName};
	string command;
	string multiStr;
    int multi = 1;

	while (myfile >> command) {
		findMultiplierInCommand(command, multiStr, multi);

		if (CompareStr(command, SEQUENCE)) {
        	myfile >> command;
        	for (int i = 0; i < multi; ++i) {
        		runSequence(command);
        	}
        } else if (CompareStr(command, RESTART) || CompareStr(command, RANDOM)) {
        	runCommand(command);
        } else if (CompareStr(command, NORANDOM)) {
        	if (CurGrid->getlevel() < 3) {
				cout << "Randomness is not relevant in the current level" << endl;
			} else {
			    myfile >> command;
				CurGrid->changeInputFile(command);
				cout << "Randomness is disable" << endl;
				runtxtDis(cout, blindplayer, CurGrid, OtherGrid);
    		if (!textOnly) {
          graphDisplay(xw);
        }
			}
        } else {
        	for (int i = 0; i < multi; ++i) {
				runCommand(command);
			}
        }

		multiStr = "";
        multi = 1;
	}
}

void Biquadris::findMultiplierInCommand(string &command, string &multiStr, int &multi) {
	while (command[0] <= '9' && command[0] >= '0') {
    	multiStr = multiStr + command[0];
    	command = command.substr(1);
    }

    if (multiStr.length() > 0) {
    	istringstream iss{multiStr};
    	iss >> multi;
    }
}

void Biquadris::runCommand(string command) {
    if (lowerCase(command) == LEVELUP1 || lowerCase(command) == LEVELUP2) {
    	CurGrid->levelup();
    } else if (lowerCase(command) == LEVELDOWN1 || lowerCase(command) == LEVELDOWN2) {
    	CurGrid->leveldown();
    } else if (CompareStr(command, DOWN)) {
    	CurGrid->down();
    } else if (CompareStr(command, LEFT)) {
    	try {
    		CurGrid->left();
    	}
    	catch (exception &e) {
    		runDropException(e);
    	}
    } else if (CompareStr(command, RIGHT)) {
    	try {
    		CurGrid->right();
    	}
    	catch (exception &e) {
    		runDropException(e);
    	}
    } else if (CompareStr(command, CLOCKWISE) || (lowerCase(command) == CW)) {
    	try {
    		CurGrid->cw();
    	}
    	catch (exception &e) {
    		runDropException(e);
    	}
    } else if (CompareStr(command, COUNTERCLOCKWISE) || (lowerCase(command) == CCW)) {
    	try {
    		CurGrid->ccw();
    	}
    	catch (exception &e) {
    		runDropException(e);
    	}
    }  else if (CompareStr(command, RESTART)) {
		restart();
    } else if ((command == "I") || (command == "J") || (command == "L") || (command == "O") || (command == "S")
    			|| (command == "Z") || (command == "T")) {
    	CurGrid->ChangeCurBlock(command[0]);
    } else if (CompareStr(command, RANDOM)) {
		if (CurGrid->getlevel() < 3) {
			cout << "Randomness is not relevant in the current level" << endl;
		} else {
			CurGrid->setRandom();
			cout << "Randomness is enable" << endl;
		}
	} else if (CompareStr(command, NORANDOM)) {
		if (CurGrid->getlevel() < 3) {
			cout << "Randomness is not relevant in the current level" << endl;
		} else {
		    cin >> command;
			CurGrid->changeInputFile(command);
			cout << "Randomness is disable" << endl;
		}
	} else if (CompareStr(command, DROP)) {
		try {
			CurGrid->drop();
		}
		catch (exception &e){
      		if(!textOnly){clearNext(xw);}
          runDropException(e);
		}
	} else {
		cout << "Invalid input" << endl;
		return;
	}
	runtxtDis(cout, blindplayer, CurGrid, OtherGrid);
	if (!textOnly) {
    graphDisplay(xw);
  }
}

void Biquadris::runtxtDis(ostream &out, int BlindPlayer, std::shared_ptr<Grid> Grid1, std::shared_ptr<Grid> Grid2) {
        if (Grid1->getPlayer() == 1) {
            txtDis(out, BlindPlayer, Grid1, Grid2);
        } else {
            txtDis(out, BlindPlayer, Grid2, Grid1);
        }
}

void Biquadris::runDropException(exception &e) {
	blindplayer = 0;
	if (CurGrid->getPlayer() == heavyplayer) {
		CurGrid->setNotHeavy();
		heavyplayer = 0;
	}

	try {
		CurGrid->placeBlock();
	}
	catch (exception &e1){
	    if (string(e1.what()) == "GameOver") {
	      cout<< "GameOver. Player" << OtherGrid->getPlayer() << " wins." << endl;
	      restart();
	      return;
	    }
	}

	if (string(e.what())== "SwitchPlayer") {
			CurGrid.swap(OtherGrid);
	} else if (string(e.what())== "SpecialAction") {
		runtxtDis(cout, blindplayer, CurGrid, OtherGrid);
    if (!textOnly) {
      graphDisplay(xw);
    }
		cout << "Input a special effect to affect player" << OtherGrid->getPlayer() << endl;
		string command;
		cin >> command;

		if (CompareStr(command, BLIND)) {
			blindplayer = OtherGrid->getPlayer();
		} else if (CompareStr(command, HEAVY)) {
			heavyplayer = OtherGrid->getPlayer();
			OtherGrid->setHeavy();
		} else if (CompareStr(command, FORCE)) {
			char block_type;
			cin >> block_type;
			OtherGrid->ChangeCurBlock(block_type);
		}
		CurGrid.swap(OtherGrid);
	}
}

void Biquadris::restart() {
	int tmp1_hiscore = CurGrid->gethiscore();
    int CurPlayer = CurGrid->getPlayer();
    int tmp2_hiscore = OtherGrid->gethiscore();

   	blindplayer = 0;
   	heavyplayer = 0;
   	td = make_shared<TextDisplay>();
   	gd= make_shared<GraphicDisplay>();
   	CurGrid = make_shared<Grid>(1, startLevel, file1, td, gd, seed);
   	OtherGrid = make_shared<Grid>(2, startLevel, file2, td, gd, seed);
   	CurGrid->init(textOnly);
        OtherGrid->init(textOnly);
	if (!textOnly) {xw->fillRectangle(0,0,900,800,Xwindow::White); gd->buildBoard(xw);}
   	if (CurPlayer == 1) {
    	CurGrid->sethiscore(tmp1_hiscore);
    	OtherGrid->sethiscore(tmp2_hiscore);
   	} else {
    	CurGrid->sethiscore(tmp2_hiscore);
    	OtherGrid->sethiscore(tmp1_hiscore);
   	}
   	CurGrid->createCurBlock();
    OtherGrid->createCurBlock();
    CurGrid->createNextBlock();
    OtherGrid->createNextBlock();
}

void Biquadris::txtDis(ostream &out, int BlindPlayer, std::shared_ptr<Grid> Player1Grid, std::shared_ptr<Grid> Player2Grid) {
    out << "Player" << to_string(Player1Grid->getPlayer());
    printSpace(out, 11 + 5 - 7);
    out << "Player" << to_string(Player2Grid->getPlayer()) << endl;
    out << "hiScore: " << Player1Grid->gethiscore();
	printSpace(out, 11 + 5 - 9 - to_string(Player1Grid->gethiscore()).length());
	out << "hiScore: " << Player2Grid->gethiscore() << endl;
	out << "level: " << Player1Grid->getlevel();
	printSpace(out, 11 + 5 - 7 - to_string(Player1Grid->getlevel()).length());
	out << "level: " << Player2Grid->getlevel() << endl;
	out << "score: " << Player1Grid->getlvlscore();
	printSpace(out, 11 + 5 - 7 - to_string(Player1Grid->getlvlscore()).length());
	out << "score: " << Player2Grid->getlvlscore() << endl;
    printLine(out);

	if (BlindPlayer == 0) {
		td->display(out);
	} else {
		td->blindDis(out, BlindPlayer);
	}

    printLine(out);
	out << "Next:";
	for (int i = 0; i < 11; i++){
  		out << " ";
	}
	out << "Next:" << endl;

	char type1 = Player1Grid->getNextBlock();
	char type2 = Player2Grid->getNextBlock();

	switch (type1) {
	    case 'I': out << "IIII";
	              printSpace(out, 11 + 5 - 4);
	              break;
	    case 'J': out << "J";
	              printSpace(out, 11 + 5 - 1);
		          break;
	    case 'L': out << "  L";
	              printSpace(out, 11 + 5 - 3);
	              break;
	    case 'O': out << "OO";
	              printSpace(out, 11 + 5 - 2);
	              break;
	    case 'S': out << " SS";
	              printSpace(out, 11 + 5 - 3);
	              break;
	    case 'Z': out << "ZZ";
	              printSpace(out, 11 + 5 - 2);
	              break;
	    case 'T': out << "TTT";
	              printSpace(out, 11 + 5 - 3);
	              break;
	}

	switch (type2) {
	    case 'I': out << "IIII" << endl;
	              break;
	    case 'J': out << "J" << endl;
	              break;
	    case 'L': out << "  L" << endl;
	              break;
	    case 'O': out << "OO" << endl;
	              break;
	    case 'S': out << " SS" << endl;
	              break;
	    case 'Z': out << "ZZ" << endl;
	              break;
	    case 'T': out << "TTT" << endl;
	              break;
	}

	switch (type1) {
	    case 'I': printSpace(out, 11 + 5);
		          break;
	    case 'J': out << "JJJ";
	              printSpace(out, 11 + 5 - 3);
		          break;
	    case 'L': out << "LLL";
	              printSpace(out, 11 + 5 - 3);
	              break;
	    case 'O': out << "OO";
	              printSpace(out, 11 + 5 - 2);
	              break;
	    case 'S': out << "SS";
	              printSpace(out, 11 + 5 - 2);
	              break;
	    case 'Z': out << " ZZ";
	              printSpace(out, 11 + 5 - 3);
	              break;
	    case 'T': out << " T";
	              printSpace(out, 11 + 5 - 2);
	              break;
	}

	switch (type2) {
	    case 'I': out << endl;
	              break;
	    case 'J': out << "JJJ" << endl;
	              break;
	    case 'L': out << "LLL" << endl;
	              break;
	    case 'O': out << "OO" << endl;
	              break;
	    case 'S': out << "SS" << endl;
	              break;
	    case 'Z': out << " ZZ" << endl;
	              break;
	    case 'T': out << " T" << endl;
	              break;
	}
  out << endl << endl;
}

void Biquadris::printSpace(ostream &out, int space) {
	for (int i = 0; i < space; ++i) {
		cout << " ";
	}
}

void Biquadris::printLine(ostream &out) {
    for (int i = 0; i < 11; ++i) {
        out << "-";
    }
    for (int j = 0; j < 5; ++j){
        out << " ";
    }
    for (int k = 0; k < 11; ++k) {
        out << "-";
    }
    out << endl;
}
