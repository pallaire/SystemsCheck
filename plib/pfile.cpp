
#include <cstdlib>
#include <format>
#include <fstream>
#include <iostream>
#include <vector>

#include "pfile.h"


PFile::PFile(string filepath) {
  _filepath = filepath;
  _size = 0;
  _data = nullptr;

  ifstream file(_filepath);

  if (!file.is_open()) {
    cerr << "Error opening file! : " << _filepath << std::endl;
    exit(EXIT_FAILURE);
  }

  file.seekg(0, std::ios::end);
  _size = file.tellg();
  file.seekg(0, std::ios::beg);

  _data = new char[_size];

  if (!file.read(_data, _size)) {
    cerr << "Error reading file! : " << _filepath << std::endl;
    exit(EXIT_FAILURE);
  }

  file.close();
}

PFile::~PFile() {
  if(_data != nullptr) {
    delete[] _data;
  }
}

u64 PFile::getSize() {
  return _size;
}

char* PFile::getRawData() {
  return _data;
}

vector<string> PFile::getDataOfStrings(bool keepEmptyLines) {
  vector<string> res;

  char* start = nullptr;

  for(u64 i = 0; i < _size; i++) {
    if(_data[i] == '\n' || _data[i] == 0) {
      if(start == nullptr) {
        if(keepEmptyLines) {
          res.push_back(string());  
        }
      } else {
        _data[i] = 0;
        res.push_back(string(start));
        _data[i] = '\n';
        start = nullptr;
      }
    } else if (start == nullptr){
      start = _data + i;
    }
  }

  if(start != nullptr) {
    res.push_back(string(start));
  }

  return res;
}

vector<u64> PFile::getDataOfNumbers() {
  vector<u64> res;

  char* start = nullptr;

  for(u64 i = 0; i < _size; i++) {
    if(_data[i] < '0' || _data[i] > '9') {
      _data[i] = 0;
      res.push_back(atol(start));
      _data[i] = '\n';
      start = nullptr;
    } else if (start == nullptr){
      start = _data + i;
    }
  }

  if(start != nullptr) {
    res.push_back(atol(start));
  }

  return res;
}

bool PFile::getIsTestFile() {
  return _filepath.find("_test") != std::string::npos;
}