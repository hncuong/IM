#include "MC-Spread.h"

set<int> readseedset(string seedfile);
void split(string line, set<int>& s, const char * filter);

int main(int argn, char*argv[])
{
	if (argn == 1){
		cout << "Usage: ./montecarlo --count 1000 --dataset ../../data/arxiv/ --model IC  --seed ./seedfile" << endl;
		exit(0);
	}

	string model;
	string dataset;
	string seedfile;
	int count = 10000;

	for (int i = 1; i<argn; i++){
		if (string(argv[i]) == "--count")
			count = atoi(argv[i + 1]);
		if (string(argv[i]) == "--seed")			
			seedfile = argv[i + 1];
		if (string(argv[i]) == "--dataset")
			dataset = argv[i + 1];
		if (string(argv[i]) == "--model")
			model = argv[i + 1];
	}

	ASSERT((model == "IC") || (model == "LT") || (model == "WC"));

	string diffusionPath;
	if (model == "IC" || model == "WC")
		diffusionPath = dataset + "graph_ic.inf";
	if (model == "LT")
		diffusionPath = dataset + "graph_lt.inf";

	MC mi(dataset, diffusionPath);

	if (model == "IC")
		mi.setInfuModel(Graph::IC);
	else if (model == "WC")
		mi.setInfuModel(Graph::WC);
	else if (model == "LT")
		mi.setInfuModel(Graph::LT);

	mi.seedSet = readseedset(seedfile);


	double influence = mi.Influence(count);
	cout << "count " << count << endl;
	cout << "influence " << influence << endl;
	
}

set<int> readseedset(string seedfile)
{
	set<int> s;
	ifstream file(seedfile.c_str());
	string seed;
	getline(file, seed);
	file.close();
	split(seed, s, " ");
	ASSERT(s.size() > 0);
	return s;
}

void split(string line, set<int>& s, const char * filter)
{
	char *str = (char *)line.c_str();
	char *pch;
	pch = strtok(str, filter);
	while (pch != NULL)
	{
		s.insert(atoi(pch));
		pch = strtok(NULL, filter);
	}
}