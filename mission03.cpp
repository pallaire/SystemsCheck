#include <print>
#include <cmath>
#include <map>
#include <set>
#include <vector>
#include "plib/plib.h"

struct Coord {
	i64 x;
	i64 y;
};
	
const u64 MAXNODES = 28;

i64 walk(i64 node, i64 nodescount, i64* pdistances, map<u8, vector<u8>>& closenodes, set<i64>& path) {
	i64 res = 0;

	if(node == nodescount-1) {
		return 1;
	}

	path.insert(node);

	for(u8 dest : closenodes[node]) {
		if(dest == node) {
			continue;
		}

		if(path.contains(dest)) {
			// no loops
			continue;
		}

		res += walk(dest, nodescount, pdistances, closenodes, path);
	}

	path.erase(node);

	return res;
}

int main (int /*argc*/, char** /*argv*/) {
	PChrono apptiming("");
	// PFile file("/home/pallaire/devs/SystemsCheck/data/mission03.test");
	PFile file("/home/pallaire/devs/SystemsCheck/data/mission03.data");
	char* bytes = file.getRawData();
	u64 len = file.getSize();

	u64 nodescount = 0;
	u64 parsestate = 0;
	i64 x = 0;
	i64 y = 0;

	vector<Coord> positions;
	map<u8, vector<u8>> closenodes;
	i64 distances[MAXNODES*MAXNODES] = {};

	// Parse input data
	for(u64 i = 0; i < len; i++) {
		u8 c = bytes[i];

		if(parsestate == 0) {
			//id ... not needed
			//wait for X

			if(c=='X') {
				i++;
				x = int_at(bytes, &i);
				parsestate = 1;
			}
			continue;
		} else {
			if(c=='Y') {
				i++;
				y = int_at(bytes, &i);

				nodescount++;
				positions.push_back({x, y});
				parsestate = 0;
			}
			continue;
		}
	}

	// Compute all the Manathan distances for every nodes
	for (u64 n = 0; n < nodescount - 1; n++) {
		for (u64 p = n + 1; p < nodescount; p++) {
			Coord p1 = positions[n];
			Coord p2 = positions[p];

			i64 d = std::abs(p1.x - p2.x) + std::abs(p1.y - p2.y);

			if(d <=5) {
				closenodes[n].push_back(p);
				closenodes[p].push_back(n);
			}

			distances[(n * MAXNODES) + p] = d;
			distances[(p * MAXNODES) + n] = d;
		}
	}

        set<i64> path;
	path.insert(0);

	i64 res = walk(0, nodescount, distances, closenodes, path);


	std::println("Running  >  {}", __FILE_NAME__);
	std::println("Result 1   how many paths: {}", res); 
	//std::println("Result 2    Cheapest path : {}", power[h-1][w-1]-1); // -1 because first step is free
	return 0;
}
