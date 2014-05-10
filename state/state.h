#ifndef STATE_H
#define STATE_H

#include "transition.h"

struct State {
	virtual ~State() {}
	virtual Transition Tick(double dt) = 0;
	virtual void Draw(double weight) = 0;
	virtual void KeyDown(int key) {};
	virtual void KeyUp(int key) {};
	virtual void KeyTyped(int key) {};
};

#endif
