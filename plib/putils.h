#include <sstream>
#include <string>
#include <vector>

#include "ptypes.h"

using namespace std;

// =========================================
// String utils
// =========================================

vector<u64> splitStringToVectorU64(const string& s);

u64 uint_at(const char* data, u64* idx);
i64 int_at(const char* data, u64* idx);
