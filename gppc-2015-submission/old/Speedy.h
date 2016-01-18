#include <stdint.h>

struct xyLoc {
  int16_t x;
  int16_t y;
};

void PreprocessMap(std::vector<bool> &bits, int width, int height, const char *filename);
void *PrepareForSearch(std::vector<bool> &bits, int width, int height, const char *filename);
bool GetPath(void *data, xyLoc s, xyLoc g, std::vector<xyLoc> &path);
const char *GetName();

class State{
	  float _d;
	  xyLoc _pos;
	  State* _p;
	public:
	  void set_values(float,xyLoc);
	  void set_parent(State* p);
	  float d() {return _d;}
	  xyLoc pos() {return _pos;}
	  State* parent() {return _p;}
};

void State::set_values (float d, xyLoc pos) {
  _d = d;
  _pos = pos;
}

void State::set_parent(State* p){
	_p = p;
}

struct StateComparator
{
    bool operator()( State* ls, State* rs ) {
    	return (ls->d()) > (rs->d());
    }
};