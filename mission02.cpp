#include <print>
#include <vector>
#include "plib/plib.h"

int main (int /*argc*/, char** /*argv*/) {
  PChrono apptiming("");
  //PFile file("data/mission02.test");
  PFile file("data/mission02.data");
  char* bytes = file.getRawData();
  u64 len = file.getSize();

  P2DMap* map = new P2DMap(bytes, len, 0);

  i64 w = map->w;
  i64 h = map->h;

  std::println("Map size: {}x{}", w, h);

  i8 dx[8] = { 1, -1,  0,  0,  1,  1, -1, -1};
  i8 dy[8] = { 0,  0,  1, -1,  1, -1,  1, -1};
  i16 newx, newy;


  // Cost is the power cost to move to each grid position
  u8 cost[150][150];
  for(int y = 0; y < h; y++) {
    for(int x = 0; x < w; x++) {
      if(map->get(x, y) == '#') {
        cost[x][y] = 9;
        continue;
      }

      cost[x][y] = 1; // normal cost

      for(int r = 0; r < 8; r++){
        newx = x + dx[r];
        newy = y + dy[r];

        if(newx<0 || newx>=w || newy<0 || newy>=h) {
          continue;
        }

        if(map->get(newx, newy) == '#') {
          cost[x][y] = 2;
          break;
        }
      }
    }
  }

  // Distance is for Problem #1, shortest path
  // Power is for Problem #2, power cost 
  u16 distance[150][150];
  u16 power[150][150];
  for(int y = 0; y < h; y++) {
    for(int x = 0; x < w; x++) {
      distance[x][y] = 0xFFFF;
      power[x][y] = 0xFFFF;
    }
  }

  // this is a coordinate holder.
  // x,y
  // x == (v >> 8)
  // y == (v & 0xff)
  vector<u16> work;
  work.push_back(0);
  distance[0][0] = 1;
  power[0][0] = 1;

  i16 x, y;
  u16 pos;
  u16 workdistance, workpower;

  while(work.size() > 0) {
    pos = work.back();
    x = pos >> 8;
    y = pos & 0xFF;
    work.pop_back();

    bool addtowork = false;

    for(u8 i = 0; i < 4; i++) {
      newx = x + dx[i];
      newy = y + dy[i];

      if(newx<0 || newx>=w || newy<0 || newy>=h) {
        continue;
      }

      if(map->get(newx, newy) == '#') {
        continue;
      }

      // what is the cost of the new destination?
      // it's the current cost + 1
      workdistance = distance[x][y] + 1;
      if(workdistance < distance[newx][newy]) {
        distance[newx][newy] = workdistance;
        addtowork = true;
      }

      workpower = power[x][y] + cost[newx][newy];
      if(workpower < power[newx][newy]) {
        power[newx][newy] = workpower;
        addtowork = true;
      }

      if(addtowork) {
        work.push_back((newx<<8)+newy);
        addtowork = false;
      }
    }
  }

  delete map;

  std::println("Running  >  {}", __FILE_NAME__);
  std::println("Result 1    Shortest path length: {}", distance[h-1][w-1]-1); // -1 because first step is free
  std::println("Result 2    Cheapest path : {}", power[h-1][w-1]-1); // -1 because first step is free
  return 0;
}
