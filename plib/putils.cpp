#include "putils.h"

vector<u64> splitStringToVectorU64(const string& s) {
    vector<u64> result;

    bool innumber = false;
    u64 work = 0;

    for(char c : s) {
        if(c>= '0' && c<='9') {
            innumber = true;
            work *= 10;
            work += c-'0';
        } else {
            if(innumber) {
                result.push_back(work);
                work = 0;
                innumber = false;
            }
        }
    }

    if(innumber) {
        result.push_back(work);
    }

    return result;
}

u64 uint_at(const char* data, u64* idx) {
    u64 work = 0;
    char c;

    while(true) {
        c = data[*idx];
        if(c >= '0' && c <= '9') {
            (*idx)++;
            work *= 10;
            work += (c - '0');
        } else {
            return work;
        }
    }
}

i64 int_at(const char* data, u64* idx) {
    i64 work = 0;
    char c;

		i64 sign = 1;

		if(data[*idx] == '-') {
			sign = -1;
      (*idx)++;
		}

    while(true) {
        c = data[*idx];
        if(c >= '0' && c <= '9') {
            (*idx)++;
            work *= 10;
            work += (c - '0');
        } else {
            return work*sign;
        }
    }
}
