#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdint>
#include <sstream>
#include <stdio.h>
// for mmap:
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

//for customer
#include "sfmt/SFMT.h"
#include <vector>
#include <cstdlib>
#include <time.h>
#include <stdlib.h>
#include <set>
#include <queue>
#include <unistd.h>  //close open
#include <fstream>

#define ASSERT(v) {if (!(v)) {cerr<<"ASSERT FAIL @ "<<__FILE__<<":"<<__LINE__<<endl; exit(1);}}

using namespace std;

//typedef double (*pf)(int, int);

void handle_error(const char* msg);

class Graph
{
public:
    int n, m;
    vector<int> inDeg;
   // vector<vector<int>> InNode;
	vector<vector<int>> OutNode;

    vector<vector<double>> probT;

	sfmt_t sfmtSeed;

    enum InfluModel {IC, WC, LT};
    InfluModel influModel;
    void setInfuModel(InfluModel p)
    {
        influModel = p;
    }

    string folder;
    string graph_file;
    void readNM()
    {
		ifstream cin((folder + "attribute.txt").c_str());
        ASSERT(!cin == false);
        string s;
        while (cin >> s)
        {
            if (s.substr(0, 2) == "n=")
            {
                n = atoi(s.substr(2).c_str());
                continue;
            }
            if (s.substr(0, 2) == "m=")
            {
                m = atoi(s.substr(2).c_str());
                continue;
            }
            ASSERT(false);
        }
        cin.close();
    }

    void add_edge(int a, int b, double p)
    {
        probT[a].push_back(p);
        //InNode[b].push_back(a);
		OutNode[a].push_back(b);
        inDeg[b]++;
    }

    vector<bool> hasnode;
    void readGraph()
    {      
		size_t length;
		int fd = open((graph_file).c_str(), O_RDWR);
		if (fd == -1)
			handle_error("open");
		struct stat sb;
		int rc = fstat(fd, &sb);
		if (rc == -1)
			handle_error("fstat");

		length = sb.st_size;
		auto ptr = static_cast<char*>(mmap(NULL, length, PROT_READ, MAP_PRIVATE, fd, 0u));  //byte by byte
		auto f = ptr;

		int gap = 2 * sizeof(int) + sizeof(double);
        //ASSERT(fin != false);
        int readCnt = 0;
        for (int i = 0; i < m; i++)
        {
            readCnt ++;
            int a, b;
            double p;
            //int c = fscanf(fin, "%d%d%lf", &a, &b, &p);
			memcpy(&a, f, sizeof(int));
			memcpy(&b, f + sizeof(int), sizeof(int));
			memcpy(&p, f + 2 * sizeof(int), sizeof(double));
			f += gap;
            
            ASSERT( a < n );
            ASSERT( b < n );
            hasnode[a] = true;
            hasnode[b] = true;
            add_edge(a, b, p);           
        }
        ASSERT(readCnt == m);
		rc = munmap(ptr, length);
		close(fd);
    }

    Graph(string folder, string graph_file): folder(folder), graph_file(graph_file)
    {
		srand(time(NULL));
		sfmt_init_gen_rand(&sfmtSeed, rand());

        readNM();

		for (int i = 0; i < n; i++)
        {

			OutNode.push_back(vector<int>());
            
			hasnode.push_back(false);

            probT.push_back(vector<double>());

            inDeg.push_back(0);
        }
        readGraph();
    }
};

double sqr(double t)
{
    return t * t;
}

void handle_error(const char* msg) {
	perror(msg);
	exit(255);
}

