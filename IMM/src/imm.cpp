#define HEAD_INFO

#include "sfmt/SFMT.h"
#include "head.h"

class Argument{
public:
    int k;
    string dataset;
    double epsilon;
    string model;
    double T;
    string seedfile;
    int time;
};

#include "graph.h"
#include "infgraph.h"
#include "imm.h"

//static unsigned int rr_num=0;
void OutputSeedSetToFile(set<int> seed_set, string seedfile)
{
    ofstream of;
    of.open(seedfile);
    for (int seed: seed_set)
    {
        of << seed << " ";
    }
    of.close();
}

void run_with_parameter(InfGraph &g, const Argument & arg)
{
        //cout << "--------------------------------------------------------------------------------" << endl;
        //cout << arg.dataset << " k=" << arg.k << " epsilon=" << arg.epsilon <<   " " << arg.model << endl;


        
        // cout<<"Before IMM class"<<endl;
        // disp_mem_usage();
        // cout<<endl;
          
        Imm::InfluenceMaximize(g, arg);

        
        // cout<<"After IMM class" <<endl;
        // disp_mem_usage();
        // cout<<endl;
        

        // INFO(g.seedSet);
        OutputSeedSetToFile(g.seedSet, arg.seedfile);
        //INFO(g.InfluenceHyperGraph());
        Timer::show(arg.time);
}
void Run(int argn, char **argv)
{
    Argument arg;


    for (int i = 0; i < argn; i++)
    {
        if (argv[i] == string("-help") || argv[i] == string("--help") || argn == 1)
        {
            cout << "./imm -dataset *** -epsilon *** -k ***  -model IC|LT|WC|TR|CONT -seedfile *** -time *** " << endl;
            return ;
        }
        if (argv[i] == string("-dataset")) 
            arg.dataset = argv[i + 1];
        if (argv[i] == string("-epsilon")) 
            arg.epsilon = atof(argv[i + 1]);
        if (argv[i] == string("-T")) 
            arg.T = atof(argv[i + 1]);
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
    ASSERT(arg.model == "IC" || arg.model == "LT" || arg.model == "WC" || arg.model=="CONT");

    string graph_file;
    if (arg.model == "IC")
        graph_file = arg.dataset + "graph_ic.inf";
    else if (arg.model == "LT")
        graph_file = arg.dataset + "graph_lt.inf";
    else if (arg.model == "WC")
        graph_file = arg.dataset + "graph_ic.inf";
    else if (arg.model == "TR")
        graph_file = arg.dataset + "graph_tr.inf";
    else if (arg.model == "CONT")
        graph_file = arg.dataset + "graph_cont.inf";
    else
        ASSERT(false);
  
    
    // cout<<"Before load the graph"<<endl;
    // disp_mem_usage();
    // cout<<endl;
    
    InfGraph g(arg.dataset, graph_file);

    
    // cout<<"After load the graph"<<endl;
    // disp_mem_usage();
    // cout<<endl;    
    

    if (arg.model == "IC")
        g.setInfuModel(InfGraph::IC);
    else if (arg.model == "LT")
        g.setInfuModel(InfGraph::LT);
    else if (arg.model == "TR")
        g.setInfuModel(InfGraph::IC);
    else if (arg.model == "CONT")
        g.setInfuModel(InfGraph::CONT);
    else
        ASSERT(false);

    //INFO(arg.T);

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

