#ifndef _WASTAR_H
#define _WASTAR_H

#include <stdint.h>

#include "State.h"

struct StateComparator
{
    bool operator()( State* ls, State* rs ) {
		if( ls->f() == rs->f() ){
			ls->g() > rs->g(); //tie on g value
		}
    	return (ls->f()) > (rs->f());
    }
};

#ifdef HEAP2_H

struct PathfindingNodeEqual {
	bool operator()(const State* i1, const State* i2)
	{
		return (i1->_d == i2->_d);
	}
};

struct PathfindingNodeCmp : std::binary_function<bool, State* const, State* const> {
	bool operator()(State* const lhs, State* const rhs) const {
		return lhs->d() > rhs->d();
	}
};

struct SearchNodeHash {
	size_t operator()(const State* x) const
	{
		return (size_t)(x->_pos.y + (x->_pos.x * MAX_WIDTH));
	}
};

typedef GenericHeap<State*, SearchNodeHash,
	PathfindingNodeEqual, PathfindingNodeCmp> PQueue;
	
#endif

#endif