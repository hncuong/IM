#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include "../src/pmc.hpp"

#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>

using namespace std::chrono;
using namespace std;

int main(int argc, char **argv) {
	if (argc < 4) {
		cerr << "./pmc graph k R" << endl;
		exit(1);
	}

	string file = argv[1];
	int k = atoi(argv[2]);
	int R = atoi(argv[3]);

	ifstream is(file.c_str());
	vector<pair<pair<int, int>, double> > es;
	int u, v;
	double p;
	for (; is >> u >> v >> p;) {
		if (u == v) {
			continue;
		}
		es.push_back(make_pair(make_pair(u, v), p));
	}
	is.close();

	InfluenceMaximizer im;

	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	vector<int> seeds = im.run(es, k, R);
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
	cout << "Time: " << time_span.count() << endl;
	cout << "Seed=";
	for (int i = 0; i < k; i++) {
		cout << seeds[i] << " ";
	}
	cout << endl;

	return 0;
}
