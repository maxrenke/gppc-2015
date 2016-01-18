#include "State.h"

void State::set_values (float d, xyLoc pos) {
  _d = d;
  _pos = pos;
}

void State::set_parent(State* p){
	_p = p;
}

