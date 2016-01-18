/**
 Implementation of the Weighted A* Algorithm
 
 Author: Maxwell Renke (mcl83@wildcats.unh.edu) 
**/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <deque>
#include <vector>
#include <algorithm>
#include <map>
#include <assert.h>
#include <iostream>

#include "wAStar.h"
#include "State.h"
//#include "GenericHeap.h"
//#include "BucketPriorityQueue.h"

std::vector<bool> map;
int map_size = MAX_WIDTH*MAX_WIDTH; //2048*2048

#ifdef _BUCKET_LIST_H
	BucketPriorityQueue open_list;
#elif HEAP2_H
	PQueue open_list;
#else
	std::vector<State*> open_list;
#endif
std::vector<bool> closed_list;

std::vector<xyLoc> succ;
std::vector<State*> neighbors;

int width;
int height;

xyLoc start;
xyLoc goal;

//Returns name of entry
const char *GetName(){
	return "Speedy";
}

//Unused function
void PreprocessMap(std::vector<bool> &bits, int width, int height, const char *filename){
	printf("Not writing to file '%s'\n", filename);
}

//Unused function
void *PrepareForSearch(std::vector<bool> &bits, int w, int h, const char *filename){
	printf("Not reading from file '%s'\n", filename);
	map = bits;
	map_size = map.size();
	width = w;
	height = h;
	m_currentIteration = 1;
	#ifndef HEAP2_H
		#ifndef _BUCKET_LIST_H
			std::make_heap(open_list.begin(),open_list.end(), StateComparator() );
		#endif
	#endif
}

//Function to return index in vector given xyLoc
int GetIndex(xyLoc s)
{
	return s.y*width+s.x;
}

//Return distance heuristic
float distance(xyLoc a, xyLoc b){
	#ifdef _SPEEDY_H
		float delta_x = (a.x - b.x)*(a.x - b.x);
		float delta_y = (a.y - b.y)*(a.y - b.y);	
		return std::max(delta_x,delta_y);
	#endif
	
	#ifdef _WASTAR_H
		float delta_x = (a.x - b.x)*(a.x - b.x);
		float delta_y = (a.y - b.y)*(a.y - b.y);
		return std::max(delta_x, delta_y) + (sqrt(2)-1)*std::min(delta_x, delta_y);
	#endif
}

//Function to determine goal state
bool FindGoal(State* s){
	if( s->pos().x == goal.x &&
	    s->pos().y == goal.y){
			return true;
		}
	return false;
}

//Function to determine if x,y pair is valid in map
bool valid(int x, int y){
	if( x >= 0 && y >= 0 && x < map_size && y < map_size )
		return true;
	return false;
}

//Function to determine if index is valid in map
bool valid(int i){
	if( i >= 0 && i < map_size )
		return true;
	return false;
}

// generates 8-connected neighbors
void GetSuccessors(xyLoc s, std::vector<xyLoc> &neighbors)
{
	neighbors.resize(0);
	xyLoc next = s;
	xyLoc adj_x = s;
	xyLoc adj_y = s;
	int index;
	int x_index;
	int y_index;
	
	/* adjacent right */ 
	next = s;
	next.x++;	

	index = GetIndex(next);
	if ( valid(index) && next.x < width && map[index])
		neighbors.push_back(next);

	/* adjacent left */
	next = s;
	next.x--;
	index = GetIndex(next);
	if ( valid(index) && next.x >= 0 && map[GetIndex(next)])
		neighbors.push_back(next);

	/* adjacent down */
	next = s;
	next.y--;
	index = GetIndex(next);
	if ( valid(index) && next.y >= 0 && map[GetIndex(next)])
		neighbors.push_back(next);

	/* adjacent up */
	next = s;
	next.y++;
	index = GetIndex(next);
	if ( valid(index) && next.y < height && map[GetIndex(next)])
		neighbors.push_back(next);
	
	/* diagonal up and right */
	adj_x.x++;
	adj_y.y++;
	
	x_index = GetIndex(adj_x);
	y_index = GetIndex(adj_y);
	
	if( valid(x_index,y_index) && map[x_index] && map[y_index] ){
		next = s;
		next.x++;
		if (next.x < width && map[GetIndex(next)]){
			next.y++;
			if (next.y < height && map[GetIndex(next)] ){
				neighbors.push_back(next);
			}
		}
	}
	
	/* diagonal down and right */
	adj_x = s;
	adj_y = s;
	
	adj_x.x++;
	adj_y.y--;
	
	x_index = GetIndex(adj_x);
	y_index = GetIndex(adj_y);
	
	if( valid(x_index,y_index) && map[x_index] && map[y_index] ){
		next = s;
		next.x++;
		if (next.x < width && map[GetIndex(next)]){
			next.y--;
			if (next.y >=0 && map[GetIndex(next)] ){
				neighbors.push_back(next);
			}
		}
	}
	
	/* diagonal up and left */
	adj_x = s;
	adj_y = s;
	
	adj_x.x--;
	adj_y.y++;
	
	x_index = GetIndex(adj_x);
	y_index = GetIndex(adj_y);
	
	if( valid(x_index,y_index) && map[x_index] && map[y_index] ){
		next = s;
		next.x--;
		if (next.x >= 0 && map[GetIndex(next)]){
			next.y++;
			if (next.y < height && map[GetIndex(next)] ){
				neighbors.push_back(next);
			}
		}
	}
	
	/* diagonal down and left */
	adj_x = s;
	adj_y = s;
	
	adj_x.x--;
	adj_y.y--;
	
	x_index = GetIndex(adj_x);
	y_index = GetIndex(adj_y);
	
	if( valid(x_index,y_index) && map[x_index] && map[y_index] ){
		next = s;
		next.x--;
		if (next.x >= 0 && map[GetIndex(next)]){
			next.y--;
			if (next.y >= 0 && map[GetIndex(next)] ){
				neighbors.push_back(next);
			}
		}
	}
}

#ifdef DEBUG
	//Method to print representation of search space
	void display_search(){
		for( int y=0; y<height; y++){
			for( int x=0; x<width; x++){
				if( y == start.y && x == start.x ){
					printf("S");
				} else if( y == goal.y && x == goal.x ){
					printf("#");
				} else if( !map[y*width+x] ){
					printf("@");
				}
				else if( closed_list[y*width+x] ){
					printf("1");
				} else {
					printf("0");
				}
			}
			printf("\n");
		}
		printf("\n\n");
	}
#endif

//Return path
void return_path(State* s, std::vector<xyLoc> &path){
	std::vector<xyLoc> tempPath; //faster than inserting into path
	tempPath.resize(0);
	State* n = s;
	while( n != NULL ){
		tempPath.push_back(n->pos());
		n = n->parent();
	}
	
	int size = tempPath.size()-1;
	for( int i=size; i>=0; i--){
		path.push_back(tempPath[i]);
	}
}

bool GetPath(void *data, xyLoc s, xyLoc g, std::vector<xyLoc> &path){	
	/* clear open list */
	#ifdef _BUCKET_LIST_H
		open_list.Reset();
	#elif HEAP2_H
		open_list.reset();
		open_list.reserve(3000);
	#else
		open_list.clear();
	#endif
	
	/* initialize closed list */
	closed_list.resize(map.size());
	for( int i=0; i<map.size(); i++){
		closed_list[i] = false;
	}
	
	/* start location */
	start = s;
	
	/* goal location */
	goal = g;
	
	m_currentIteration++;
	
	/* start state */
	State* start = (State*)malloc(sizeof(State));//new State;
	#ifdef _SPEEDY_H
		start->set_values(distance(s,g),s);
	#endif
	
	#ifdef _WASTAR_H
		start->set_values(0,distance(s,g),s);
	#endif
	start->set_parent(NULL);
	start->m_iteration = m_currentIteration;
	
	/* push start state */
	#ifdef _BUCKET_LIST_H
		open_list.Push(start);
	#elif HEAP2_H
		open_list.add(start);
	#else
		open_list.push_back(start);
		std::push_heap(open_list.begin(),open_list.end(),StateComparator());
	#endif
	
	/* Speedy */
	#ifdef _BUCKET_LIST_H
	while( !open_list.Empty() ){
	#else
	while( !open_list.empty() ){
	#endif
		#ifdef _BUCKET_LIST_H
			State* curr = open_list.Pop();
		#elif HEAP2_H
			State* curr = open_list.remove();
		#else
			std::pop_heap (open_list.begin(),open_list.end(),StateComparator());
			State* curr = open_list.back();
			open_list.pop_back();
		#endif
		
		if( FindGoal(curr) ){
			return_path(curr, path);
			#ifdef DEBUG
				display_search();
			#endif
			break;
		}
		
		GetSuccessors(curr->pos(), succ);
		
		for( int i=0; i<succ.size(); i++){
			State* nb = (State*)malloc(sizeof(State));//new State;
			xyLoc pos = succ[i];
			
			#ifdef _SPEEDY_H
				/* estimate total number of moves to go */
				nb->set_values(distance(pos,g),pos);
			#endif
			
			#ifdef _WASTAR_H
				/* octile distance heuristic */
				if( succ[i].x == curr->pos().x || succ[i].y == curr->pos().y ){
				nb->set_values(curr->g()+1.0f,distance(pos,g),pos);
				}
				else{
					nb->set_values(curr->g()+sqrt(2),distance(pos,g),pos);
				}
			#endif
			
			nb->set_parent(curr);
			nb->m_iteration = m_currentIteration;
			int index = GetIndex(succ[i]);
			if( !closed_list[index] && map[index] ){
				closed_list[GetIndex(pos)] = true; //add state to closed list
				#ifdef _BUCKET_LIST_H
					open_list.Push(nb);
				#elif HEAP2_H
					open_list.add(nb);
				#else
					open_list.push_back(nb);
					std::push_heap(open_list.begin(),open_list.end(),StateComparator());
				#endif
			}
		}
	}
	
	return true;
}
