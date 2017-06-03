//
// Created by cuonghn on 26/5/17.
//
#define HEAD_INFO

#include "sfmt/SFMT.h"
#include "head.h"

class Argument{
public:
    int k;
    string dataset;
    int l;
    string model;
    string seedfile;
    int time;
};

#include "infgraph.h"
#include "easyim.h"

//static unsigned int rr_num=0;


void run_with_parameter(InfGraph &g, const Argument & arg)
{

    // cout<<"Before EasyIM class"<<endl;
    // disp_mem_usage();
    // cout<<endl;

    EasyIM::InfluenceMaximize(g, arg);


    // cout<<"After EasyIM class" <<endl;
    // disp_mem_usage();
    // cout<<endl;


    // INFO(g.seedSet);
    OutputSeedSetToFile(g.seedSet, arg.seedfile);
    
    // INFO(g.visit_mark);
    // Timer::show(arg.time);
}
void Run(int argn, char **argv)
{
    Argument arg;


    for (int i = 0; i < argn; i++)
    {
        if (argv[i] == string("-help") || argv[i] == string("--help") || argn == 1)
        {
            cout << "./easyim -dataset *** -l *** -k ***  -model IC|LT|WC -seedfile *** -time ***" << endl;
            return ;
        }
        if (argv[i] == string("-dataset"))
            arg.dataset = argv[i + 1];
        if (argv[i] == string("-l"))
            arg.l = atoi(argv[i + 1]);
        if (argv[i] == string("-k"))
            arg.k = atoi(argv[i + 1]);
        if (argv[i] == string("-model"))
            arg.model = argv[i + 1];
        if (argv[i] == string("-seedfile"))
            arg.seedfile = argv[i + 1];
        if (argv[i] == string("-time"))
            arg.time = atoi(argv[i+1]);
    }
    ASSERT(arg.dataset != "");
    ASSERT(arg.model == "IC" || arg.model == "LT" || arg.model == "WC");

    string graph_file;
    if (arg.model == "IC")
        graph_file = arg.dataset + "graph_ic.inf";
    else if (arg.model == "LT")
        graph_file = arg.dataset + "graph_lt.inf";
    else if (arg.model == "WC")
        graph_file = arg.dataset + "graph_ic.inf";
    else
    ASSERT(false);

    InfGraph::InfluModel influModel;

    if (arg.model == "IC")
        influModel = InfGraph::IC;
    else if (arg.model == "LT")
        influModel = InfGraph::LT;
    else if (arg.model == "WC")
        influModel = InfGraph::WC;
    else
    ASSERT(false);

    // cout<<"Before load the graph"<<endl;
    // disp_mem_usage();
    // cout<<endl;

    InfGraph g(arg.dataset, graph_file, influModel);


    // cout<<"After load the graph"<<endl;
    // disp_mem_usage();
    // cout<<endl;

    run_with_parameter(g, arg);
}


int main(int argn, char **argv)
{
    __head_version = "v1";
    OutputInfo info(argn, argv);

    Run( argn, argv );
    // disp_mem_usage();
    cout<<"Memory: "<<getProcMemory()<<" MB"<<endl;
}


