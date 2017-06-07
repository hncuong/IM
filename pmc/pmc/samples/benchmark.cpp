#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include "../src/pmc.hpp"
#include "MeasureM.h"

#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>

using namespace std::chrono;
using namespace std;

void OutputSeedSetToFile(const vector<int>& seed_set, const string& seedfile)
{
    ofstream of;
    of.open(seedfile);
    for (int seed: seed_set)
    {
        of << seed << " ";
    }
    of.close();
}

int main(int argc, char **argv) {
	if (argc < 5) {
		cerr << "./pmc graph k R seedfile" << endl;
		exit(1);
	}

	string file = argv[1];
	int k = atoi(argv[2]);
	int R = atoi(argv[3]);
	string seedfile = argv[4];

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
	cout << "Spend " << time_span.count() << " seconds." << endl;

	OutputSeedSetToFile(seeds, seedfile);	
	cout<<"Memory: "<<getProcMemory()<<" MB"<<endl;
	return 0;
}
