#include <iostream>
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
  cout << "[PChrono] : " << _name << " total run time : " << microseconds << "μs" << "   --->   " << microseconds/1000.0f << "ms" << "   --->   " << (microseconds / 1000000.0f) << "s" << std::endl;
}
