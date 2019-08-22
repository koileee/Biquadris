#ifndef __OBSERVER_H__
#define __OBSERVER_H__

class Subject;

class Observer{
public:
	virtual void update (Subject &) = 0;  //gets notified by a subject
	virtual ~Observer() {}
};
#endif
