#include "graph.h"
#include "IMRank.h"
#include "MeasureM.h"
#include "memoryusage.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

class Argument{
public:
    int k;
    int l;
    string dataset;
    int directed;
    string seedfile;
};

void OutputSeedSetToFile(int k, int (*GetNode)(int i), string seedfile)
{
    ofstream of;
    of.open(seedfile);
    for (int i=0; i < k; i++)
    {
        of << GetNode(i) << " ";
    }
    of.close();
}

void Run(int argn, char **argv)
{
    time_t t;
	srand((unsigned) time(&t));
    cout << "Start\n" ;

    Argument arg;
    arg.l = 1;
    cout << "Start2\n" ;
    for (int i = 0; i < argn; i++)
    {
        if (argv[i] == string("-help") || argv[i] == string("--help") || argn == 1)
        {
            cout << "./imrank -dataset *** -k *** -l *** -directed *** -seedfile ***" << endl;
            return ;
        }
        if (argv[i] == string("-dataset")) 
            arg.dataset = argv[i + 1];
        if (argv[i] == string("-k")) 
            arg.k = atoi(argv[i + 1]);
        if (argv[i] == string("-directed"))            
            arg.directed = atoi(argv[i + 1]);
        if (argv[i] == string("-l"))            
            arg.l = atoi(argv[i + 1]);
        if (argv[i] == string("-seedfile"))
            arg.seedfile = argv[i + 1];
    }
	char initialranking[] = "Degree";
    cout << arg.dataset << endl;
    string graph_file;
    graph_file = arg.dataset + "graph_ir.txt";
    cout << graph_file << endl;
    char filename[graph_file.length() + 1];

    strcpy(filename, graph_file.c_str());
    cout << filename << endl;
    if (arg.directed)
    {
        cout << "Build directed\n";
        Graph::BuildFromFile2DWC(filename);
    }
    else
    {
        cout << "Build undirected\n";
        Graph::BuildFromFile2WC(filename);
    } 

    cout << "Build graph OK! \n";

    imrank::Build(initialranking, arg.l, arg.k);
    double timer = (double)imrank::timer / CLOCKS_PER_SEC;
    cout << "Spend " << timer << endl;
    OutputSeedSetToFile(arg.k, imrank::GetNode, arg.seedfile);

}

int main(int argn, char **argv)
{    
    Run( argn, argv );
    // disp_mem_usage();
    cout<<"Memory: "<<getProcMemory()<<" MB"<<endl;
}