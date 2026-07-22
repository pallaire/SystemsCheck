#ifndef __P2DMAP__
#define __P2DMAP__

#include "ptypes.h"

class P2DMap {
public:
  P2DMap(char* data, u64 size, char bufferchar = 0);
  ~P2DMap();

  i64 getWidth();
  i64 getHeight();
  char get(i64 x, i64 y);
  void set(i64 x, i64 y, char c);
  void print();

  char* operator[] (i64 y) const {
    if(_freeMemory) {
      return map + (y*w);
    } else {
      return map + (y*(w+1));
    }
	}


  char* map;  
  i64 w;
  i64 h;

private: 
  bool _freeMemory;
};

#endif
