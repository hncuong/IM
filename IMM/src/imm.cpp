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
    int time;
};

#include "graph.h"
#include "infgraph.h"
#include "imm.h"

//static unsigned int rr_num=0;


void run_with_parameter(InfGraph &g, const Argument & arg)
{
        //cout << "--------------------------------------------------------------------------------" << endl;
        //cout << arg.dataset << " k=" << arg.k << " epsilon=" << arg.epsilon <<   " " << arg.model << endl;


        
        cout<<"Before IMM class"<<endl;
        disp_mem_usage();
        cout<<endl;
          
        Imm::InfluenceMaximize(g, arg);

        
        cout<<"After IMM class" <<endl;
        disp_mem_usage();
        cout<<endl;
        

        INFO(g.seedSet);
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
            cout << "./tim -dataset *** -epsilon *** -k ***  -model IC|LT|TR|CONT " << endl;
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
        if (argv[i] == string("-time"))
            arg.time = atoi(argv[i+1]);
    }
    ASSERT(arg.dataset != "");
    ASSERT(arg.model == "IC" || arg.model == "LT" || arg.model == "TR" || arg.model=="CONT");

    string graph_file;
    if (arg.model == "IC")
        graph_file = arg.dataset + "graph_ic.inf";
    else if (arg.model == "LT")
        graph_file = arg.dataset + "graph_lt.inf";
    else if (arg.model == "TR")
        graph_file = arg.dataset + "graph_tr.inf";
    else if (arg.model == "CONT")
        graph_file = arg.dataset + "graph_cont.inf";
    else
        ASSERT(false);
  
    
    cout<<"Before load the graph"<<endl;
    disp_mem_usage();
    cout<<endl;
    
    InfGraph g(arg.dataset, graph_file);

    
    cout<<"After load the graph"<<endl;
    disp_mem_usage();
    cout<<endl;    
    

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

/*
 * * convert from an integer to a string
 * */
/*
string intToStr(int i) {
  stringstream ss;
  ss << i;
  return ss.str();
}

*
 * * convert from a strong to an integer
 * */
/*
unsigned int strToInt(string s) {
    unsigned int i;
    istringstream myStream(s);

    if (myStream>>i) {
      return i;
     } else {
       cout << "String " << s << " is not a number." << endl;
      return atoi(s.c_str());
    }
   return i;
}


float getCurrentMemoryUsage() {

   string pid = intToStr(unsigned(getpid()));
   string outfile = "tmp_" + pid + ".txt";
   string command = "pmap " + pid + " | grep -i Total | awk '{print $2}' > " + outfile;
   system(command.c_str());

   string mem_str;
   ifstream ifs(outfile.c_str());
   std::getline(ifs, mem_str);
   ifs.close();

   mem_str = mem_str.substr(0, mem_str.size()-1);
   
   float mem = (float)strToInt(mem_str);
   command = "rm " + outfile;
   system(command.c_str());
   return mem/1024;
   return 0;
}
*/

int main(int argn, char **argv)
{
    __head_version = "v1";
    OutputInfo info(argn, argv);
    
    Run( argn, argv );
    disp_mem_usage();
    cout<<"Memory: "<<getProcMemory()<<" MB"<<endl;
}

