#include "biquadris.h"
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char *argv[]){
	bool textOnly = false;
	int seed = 1;
	string file1 = "sequence1.txt";
	string file2 = "sequence2.txt";
	int startLevel = 0;
	for (int i = 1; i < argc; i++){
		if (string(argv[i]) == "-text"){
			textOnly = true;
		} else if (string(argv[i])== "-seed"){
		    seed = strtol(argv[++i], NULL, 10); 
		} else if (string(argv[i]) == "-scriptfile1"){
			file1 = argv[++i];
		} else if (string(argv[i]) == "-scriptfile2"){
			file2 = argv[++i];
		} else if (string(argv[i]) == "-startlevel"){
			startLevel = strtol(argv[++i], NULL, 10); 
		}
	}
	Biquadris b{textOnly, seed, file1, file2, startLevel};
    b.play();
    return 0;
}
