#ifndef __GDISPLAY_H__
#define __GDISPLAY_H__
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "subject.h"
#include "observer.h"


class Xwindow;
//class Subject;

class GraphicDisplay: public Observer {
	std::vector<std::vector<std::string>> board;
	void mustDraw(std::shared_ptr<Xwindow> &win, int, int);
public:
	void draw(std::shared_ptr<Xwindow> &win, int);
	void update(Subject &) override;  //notifies the GraphicDisplay
	void buildBoard(std::shared_ptr<Xwindow> &);    //output the GraphicDisplay to an output stream

	GraphicDisplay();
	~GraphicDisplay();

};


#endif
