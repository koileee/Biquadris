#ifndef __SUBJECT_H__
#define __SUBJECT_H__
#include <vector>
#include <memory>
#include "sInfo.h"

class Observer;


class Subject{
        std::vector<std::shared_ptr<Observer>> observers;
public:          // gets type
        void attach(std::shared_ptr<Observer>); //attach observer
        virtual SInfo getInfo() = 0;
        void notifyObservers();                 //notifies all attached observers
        virtual ~Subject();
};


#endif
