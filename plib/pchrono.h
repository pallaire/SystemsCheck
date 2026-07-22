#ifndef __PCHRONO__
#define __PCHRONO__

#include <chrono>
#include <string>

using namespace std;

class PChrono {
  public:
    PChrono();
    PChrono(string name);
    ~PChrono();
    void stop();
    void start();
    void print();

  private:
    bool _running;
    string _name;
    chrono::time_point<chrono::high_resolution_clock> _start;
    chrono::time_point<chrono::high_resolution_clock> _stop;
};

#endif
