#include <stdint.h>

struct xyLoc {
  int16_t x;
  int16_t y;
};

void PreprocessMap(std::vector<bool> &bits, int width, int height, const char *filename);
void *PrepareForSearch(std::vector<bool> &bits, int width, int height, const char *filename);
bool GetPath(void *data, xyLoc s, xyLoc g, std::vector<xyLoc> &path);
const char *GetName();

/* Weighted A* value */
//float weight = 0.0f;
//float weight = 1.0f;
//float weight = 1.1f;
//float weight = 4.0f;
float weight = 5.0f;

class State{
	  float _g;
	  float _h;
	  xyLoc _pos;
	  State* _p;
	public:
	  void set_values(float,float,xyLoc);
	  void set_parent(State* p);
	  float g() {return _g;}
	  float h() {return _h;}
	  float f() {return _g + weight * _h;}
	  xyLoc pos() {return _pos;}
	  State* parent() {return _p;}
};

void State::set_values (float g, float h, xyLoc pos) {
  _g = g;
  _h = h;
  _pos = pos;
}

void State::set_parent(State* p){
	_p = p;
}

struct StateComparator
{
    bool operator()( State* ls, State* rs ) {
		if( ls->f() == rs->f() ){
			ls->g() > rs->g(); //tie on g value
		}
    	return (ls->f()) > (rs->f());
    }
};
