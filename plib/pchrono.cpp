#include <print>
#include "pchrono.h"

using namespace std;

PChrono::PChrono() {
  _name = "NONAME";
  start();
}

PChrono::PChrono(string name) {
  _name = name;
  start();
}

PChrono::~PChrono() {
  if(_running) {
    stop();
    print();
  }
}

void PChrono::stop() {
  _stop = chrono::high_resolution_clock::now();
  _running = false;
}

void PChrono::start() {
  _start = chrono::high_resolution_clock::now();
  _running = true;
}

void PChrono::print() {
  auto delta = chrono::high_resolution_clock::now() - _start;

  if(!_running) {
    delta = _stop - _start;
  }

	long long microseconds = chrono::duration_cast<chrono::microseconds>(delta).count();
  std::println("[PChrono] : {}  total run time : {}μs   --->   {}ms   --->   {:9f}s", _name, microseconds, microseconds/1000.0f, microseconds / 1000000.0f);
}
