#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include <cstdlib>
#include "level.h"


using namespace std;


Level::~Level() {}

shared_ptr<Level> Level::make_level(int choice) {
    if (choice == 0) {
        return make_shared<level_0> ();
    }
    if (choice == 1) {
        return make_shared<level_1> ();
    }
    if (choice == 2) {
        return make_shared<level_2> ();
    }
    if (choice == 3) {
        return make_shared<level_3> ();
    }
    if (choice == 4) {
        return make_shared<level_4> ();
    }
     return nullptr;
}


//implement level_0

level_0::~level_0(){}

level_0::level_0():pos{0}{}

char level_0::generateBlock(string input, bool isRandom) {
    	ifstream in{input};
        ifstream in2{input};
        char c;
	//find the length of file
        int l = 0;
        while (in>>c) {l++;}
        if (pos == l){pos=0;}
        char btype;
        for(int i=0; i<=pos; i++) {
            in2>>btype;
        }
        pos++;
        return btype;
}


// implement level_1

level_1::~level_1(){}

char level_1::generateBlock(string input, bool isRandom) {
        char alpha[12]= {'S','Z','I','J','L','O','T','I','J','L','O','T'};
        int i=rand()%12;
        return alpha[i];
}


level_2::~level_2(){}

char level_2::generateBlock(string input, bool isRandom) {
        char alpha[7]= {'S','Z','I','J','L','O','T'};
        int n=rand()%7;
        return alpha[n];
}


//implement level_3
level_3::level_3():pos{0}{}

level_3::~level_3(){}

char level_3::generateBlock(string input, bool isRandom) {
    if( isRandom ) {
        char alpha[9] = {'S','S','Z','Z','T','I','J','L','O'};
        int n = rand() % 9;
        return alpha[n];
    } else {
        ifstream in{input};
        ifstream in2{input};
        char c;
        int l = 0;
        while (in>>c) {l++;}
        if (pos == l){pos=0;}
        char btype;
        for(int i=0; i<=pos; i++) {
            in2>>btype;
        }
        pos++;
        return btype;
    }
}


//implement level_4
level_4::level_4():pos{0}{}

level_4::~level_4() {}

char level_4::generateBlock(string input, bool isRandom) {
    if(isRandom) {
        char alpha[9] = {'S','S','Z','Z','I','J','L','O','T'};
        int n = rand() % 9;
        return alpha[n];
    } else {
        ifstream in{input};
        ifstream in2{input};
        char c;
        int l = 0;
        while (in>>c) {l++;}
        if (pos == l){pos=0;}
        char btype;
        for(int i=0; i<=pos; i++) {
            in2>>btype;
        }
        pos++;
        return btype;
    }
}
