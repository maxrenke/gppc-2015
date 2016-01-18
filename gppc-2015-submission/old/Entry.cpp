#include <stdio.h>
#include <deque>
#include <vector>
#include <algorithm>
#include <assert.h>
#include "Entry.h"

std::vector<bool> map;
std::vector<int> visited;
std::vector<xyLoc> succ;
int width, height;

void GetSuccessors(xyLoc s, std::vector<xyLoc> &neighbors);
int GetIndex(xyLoc s);
void ExtractPath(xyLoc end, std::vector<xyLoc> &finalPath);

const char *GetName()
{
	return "TestProgram";
}

void PreprocessMap(std::vector<bool> &bits, int width, int height, const char *filename)
{
	printf("Not writing to file '%s'\n", filename);
}

void *PrepareForSearch(std::vector<bool> &bits, int w, int h, const char *filename)
{
	printf("Not reading from file '%s'\n", filename);
	map = bits;
	width = w;
	height = h;
	return (void *)13182;
}

bool GetPath(void *data, xyLoc s, xyLoc g, std::vector<xyLoc> &path)
{
	assert((long)data == 13182);
	std::deque<xyLoc> q;

	if (path.size() > 0)
	{
		path.push_back(g);
		return true;
	}

	visited.assign(map.size(),0);
	visited[GetIndex(s)] = 1;
	q.push_back(s);
	
	while (q.size() > 0)
    {
		xyLoc next = q.front();
		
		q.pop_front();
		GetSuccessors(next, succ);
		for (unsigned int x = 0; x < succ.size(); x++)
		{
			if (visited[GetIndex(succ[x])])
				continue;
			visited[GetIndex(succ[x])] = visited[GetIndex(next)]+1;
			
			if (succ[x].x == g.x && succ[x].y == g.y) // goal found
			{
				ExtractPath(g, path);
				if (path.size() > 0)
				{
					path.pop_back();
					return false;
				}
				return true; // empty path
			}

			q.push_back(succ[x]);
		}
    }
	return true; // no path returned, but we're done
}

int GetIndex(xyLoc s)
{
	return s.y*width+s.x;
}

// generates 4-connected neighbors
// doesn't generate 8-connected neighbors (which ARE allowed)
// a diagonal move must have both cardinal neighbors free to be legal
void GetSuccessors(xyLoc s, std::vector<xyLoc> &neighbors)
{
	neighbors.resize(0);
  
	xyLoc next = s;
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

void ExtractPath(xyLoc end, std::vector<xyLoc> &finalPath)
{
	int currCost = visited[GetIndex(end)];

	finalPath.resize(0);
	finalPath.push_back(end);

	while (currCost != 1)
    {
		GetSuccessors(finalPath.back(), succ);
		for (unsigned int x = 0; x < succ.size(); x++)
		{
			if (visited[GetIndex(succ[x])] == currCost-1)
			{
				finalPath.push_back(succ[x]);
				currCost--;
				break;
			}
		}
    }
	std::reverse(finalPath.begin(), finalPath.end());
}
