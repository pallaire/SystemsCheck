#include <iostream>
#include "p2dmap.h"
#include "ptypes.h"

using namespace std;

P2DMap::P2DMap(char* rawdata, u64 size, char bufferchar) {
	map = rawdata;
    _freeMemory = false;
    w = -1;
    h = 0;

    // find width
    for(u64 i = 0; i < size; i++) {
        if(map[i] == '\n') {
            w = i;
            break;
        }
    }

    // find height
    for(u64 i = w; i < size; i += (w+1)) {
        if(map[i] == '\n') {
            h++;
        }
    }

    if(bufferchar != 0) {
        w += 2;
        h += 2;

        map = new char[h * w];
        _freeMemory = true;

        for(i64 x = 0; x < w; x++) {
            map[x] = bufferchar;
            map[((h-1)*w) + x] = bufferchar;
        }

        for(i64 y = 0; y < h; y++) {
            map[y*w] = bufferchar;
            map[((y+1)*w)-1] = bufferchar;
        }

        for(i64 y = 0; y < h-2; y++) {
            for(i64 x = 0; x < w-2; x++) {
                map[((y+1)*w) + (x+1)] = rawdata[(y*(w-1)) + x];
            }
        }
    }
}

P2DMap::~P2DMap() {
    if(_freeMemory) {
        delete[] map;
    }
}


i64 P2DMap::getWidth() {
    return w;
}

i64 P2DMap::getHeight() {
    return h;
}

char P2DMap::get(i64 x, i64 y) {
    return map[(y*(w+1)) + x];
}

void P2DMap::set(i64 x, i64 y, char c) {
    map[(y*(w+1)) + x] = c;
}

// char* P2DMap::operator[] (i64 y) {
//     return map + (y*(w+1));
// }

void P2DMap::print() {
    for(i64 y = 0; y < h; y++) {
        for(i64 x = 0; x < w; x++) {
            if(_freeMemory) {
                cout << map[y*w + x];
            } else {
                // w + 1 to skip the \n
                cout << map[(y*(w+1)) + x];
            }
        }        
        cout << std::endl;
    }
    cout << "Width: " << w << std::endl;
    cout << "Height: " << h << std::endl;
}

