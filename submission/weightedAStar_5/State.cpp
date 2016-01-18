#include "State.h"
#include "Weight.h"

void State::set_values (float g, float d, xyLoc pos) {
  _g = g;
  _h = d;
  _pos = pos;
}

void State::set_parent(State* p){
	_p = p;
}

float State::f(){
	return _g + weight * _h;
}

