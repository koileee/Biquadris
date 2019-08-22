#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <vector>
#include "sInfo.h"
#include "subject.h"
#include "observer.h"



class TextDisplay: public Observer {
	std::vector<std::vector<char>> board;
public:
	void update(Subject &) override;  //notifies the TextDisplay
	void display(std::ostream &);     //output the TextDisplay to an output stream
	TextDisplay();
	~TextDisplay();
	void blindDis(std::ostream &out, int p);
};

#endif
