#ifndef _STATE_H
#define _STATE_H

#include <stdint.h>

struct xyLoc {
  int16_t x;
  int16_t y;
};

struct State{
	  int m_iteration;
	  float _g;
	  float _h;
	  xyLoc _pos;
	  State* _p;
	public:
	  void set_values(float,float,xyLoc);
	  void set_parent(State* p);
	  float g() {return _g;}
	  float h() {return _h;}
	  float f();
	  xyLoc pos() {return _pos;}
	  State* parent() {return _p;}
};

struct StateComparator
{
    bool operator()( State* ls, State* rs ) {
    	return (ls->_g) > (rs->_g);
    }
};

#endif