#ifndef __PFILE__
#define __PFILE__

#include <cstring>
#include <string>
#include <vector>

#include "ptypes.h"

using namespace std;

class PFile {
public:
  PFile(string filepath);
  ~PFile();

  u64 getSize();
  char* getRawData();
  vector<string> getDataOfStrings(bool keepEmptyLines=false);
  vector<u64> getDataOfNumbers();
  bool getIsTestFile();

private:
  string _filepath;
  u64 _size;
  char* _data;  
};

#endif
