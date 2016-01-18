#ifndef _STATE_H
#define _STATE_H

#include <stdint.h>

struct xyLoc {
  int16_t x;
  int16_t y;
};

struct State{
	public:
	  int m_iteration;
	  float _d;
	  State* _p;
	  xyLoc _pos;
	  void set_values(float,xyLoc);
	  void set_parent(State* p);
	  float d() {return _d;}
	  xyLoc pos() {return _pos;}
	  State* parent() {return _p;}
	  float f() {return _d;}
};

struct StateComparator
{
    bool operator()( State* ls, State* rs ) {
    	return (ls->d()) > (rs->d());
    }
};

#endif