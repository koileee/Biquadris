#include "subject.h"
#include "TextDisplay.h"
#include "sInfo.h"
#include <vector>
#include <memory>
#include "observer.h"

using namespace std;



Subject::~Subject(){}

void Subject::notifyObservers(){
        for (auto it : observers){
 	   it -> update(*this);
 	 }
}


void Subject::attach(std::shared_ptr<Observer> obs){
        observers.emplace_back(obs);
}
