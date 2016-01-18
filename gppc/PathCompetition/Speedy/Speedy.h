#ifndef _SPEEDY_H
#define _SPEEDY_H

#include <stdint.h>

#define MAX_WIDTH 2048

int m_currentIteration;

#ifdef HEAP2_H

struct PathfindingNodeEqual {
	bool operator()(const State* i1, const State* i2)
	{
		return (i1 == i2);
	}
};

struct PathfindingNodeCmp : std::binary_function<bool, State* const, State* const> {
	bool operator()(State* const lhs, State* const rhs) const {
		return lhs->_d > rhs->_d;
	}
};

struct SearchNodeHash {
	size_t operator()(const State* x) const
	{
		return (size_t)(x->_pos.x + (x->_pos.y * MAX_WIDTH));
	}
};

typedef GenericHeap<State*, SearchNodeHash,
	PathfindingNodeEqual, PathfindingNodeCmp> PQueue;
	
#endif

#endif