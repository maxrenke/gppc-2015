/**
 Implementation of the Speedy Algorithm
 
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
#include "Speedy.h"

std::vector<bool> map;

std::vector<State*> open_list;
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
	width = w;
	height = h;
	std::make_heap(open_list.begin(),open_list.end(), StateComparator() );
}

//Function to return index in vector given xyLoc
int GetIndex(xyLoc s)
{
	return s.y*width+s.x;
}

//Return euclidean distance between two xyLoc (cast to int) //TODO diagonal?
float distance(xyLoc a, xyLoc b){ //octile moves in search space
	float delta_x = (a.x - b.x)*(a.x - b.x);
	float delta_y = (a.y - b.y)*(a.y - b.y);	
	return std::max(delta_x,delta_y);
}

//Function to determine goal state
bool FindGoal(State* s){
	if( s->pos().x == goal.x &&
	    s->pos().y == goal.y){
			return true;
		}
	return false;
}

// generates 8-connected neighbors
void GetSuccessors(xyLoc s, std::vector<xyLoc> &neighbors)
{
	neighbors.resize(0);
  
	xyLoc next = s;
	xyLoc adj_x = s;
	xyLoc adj_y = s;
	
	
	//diagonal
	adj_x.x++;
	adj_y.y++;
	
	if( map[GetIndex(adj_x)] && map[GetIndex(adj_y)] ){
		next = s;
		next.x++;
		if (next.x < width && map[GetIndex(next)]){
			next.y++;
			if (next.y < height && map[GetIndex(next)] ){
				neighbors.push_back(next);
			}
		}
	}
	
	adj_x = s;
	adj_y = s;
	
	adj_x.x++;
	adj_y.y--;
	
	if( map[GetIndex(adj_x)] && map[GetIndex(adj_y)] ){
		next = s;
		next.x++;
		if (next.x < width && map[GetIndex(next)]){
			next.y--;
			if (next.y >=0 && map[GetIndex(next)] ){
				neighbors.push_back(next);
			}
		}
	}
	
	adj_x = s;
	adj_y = s;
	
	adj_x.x--;
	adj_y.y++;
	
	if( map[GetIndex(adj_x)] && map[GetIndex(adj_y)] ){
		next = s;
		next.x--;
		if (next.x >= 0 && map[GetIndex(next)]){
			next.y++;
			if (next.y < height && map[GetIndex(next)] ){
				neighbors.push_back(next);
			}
		}
	}
	
	adj_x = s;
	adj_y = s;
	
	adj_x.x--;
	adj_y.y--;
	
	if( map[GetIndex(adj_x)] && map[GetIndex(adj_y)] ){
		next = s;
		next.x--;
		if (next.x >= 0 && map[GetIndex(next)]){
			next.y--;
			if (next.y >= 0 && map[GetIndex(next)] ){
				neighbors.push_back(next);
			}
		}
	}
	
	//adjacent 
	next = s;
	next.x++;
	if (next.x < width && map[GetIndex(next)])
		neighbors.push_back(next);

	next = s;
	next.x--;
	if (next.x >= 0 && map[GetIndex(next)])
		neighbors.push_back(next);

	next = s;
	next.y--;
	if (next.y >= 0 && map[GetIndex(next)])
		neighbors.push_back(next);

	next = s;
	next.y++;
	if (next.y < height && map[GetIndex(next)])
		neighbors.push_back(next);
}

//Method to print representation of search space
/*void display_search(){
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
}*/

//Return path
void return_path(State* s, std::vector<xyLoc> &path){
	State* n = s;
	while( n != NULL ){
		path.insert ( path.begin() , n->pos() );
		n = n->parent();
	}
}

//Speedy
bool GetPath(void *data, xyLoc s, xyLoc g, std::vector<xyLoc> &path){
	//clear open list
	open_list.clear();
	
	//initialize closed list
	closed_list.resize(map.size());
	for( int i=0; i<map.size(); i++){
		closed_list[i] = false;
	}
	
	//start location
	start = s;
	
	//goal location
	goal = g;
	
	//start state
	State* start = (State*)malloc(sizeof(State));
	start->set_values(distance(s,g),s);
	start->set_parent(NULL);
	
	open_list.push_back(start);
	std::push_heap(open_list.begin(),open_list.end(),StateComparator());
	
	//Speedy
	while( !open_list.empty() ){
		std::pop_heap (open_list.begin(),open_list.end(),StateComparator()); //move max val to back of heap
		State* curr = open_list.back(); //get last element in vector (just popped)
		open_list.pop_back(); //delete last element
		
		if( FindGoal(curr) ){ //found goal
			return_path(curr, path); //get path
			break;
		}
		
		neighbors.resize(0); //reset vector
		GetSuccessors(curr->pos(), succ);//find neighbors
		for( int i=0; i<succ.size(); i++){
			State* nb = (State*)malloc(sizeof(State));
			nb->set_values(distance(succ[i],g),succ[i]);
			nb->set_parent(curr);
			int index = GetIndex(succ[i]);
			if( !closed_list[index] && map[index] ){
				open_list.push_back(nb);
				closed_list[GetIndex(nb->pos())] = true; //add state to closed list
				std::push_heap(open_list.begin(),open_list.end(),StateComparator());
			}
		}
	}
	
	return true;
}

