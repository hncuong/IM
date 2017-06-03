//#define HEAD_TRACE
#define HEAD_INFO

#define HEAD_INFO
//#define HEAD_TRACE
#include "sfmt/SFMT.h"
#include "head.h"
#include "memoryusage.h"
#include "graph.h"
#include "MeasureM.h"

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

void run(TimGraph & m, string dataset, int k, double epsilon, string model , string seedfile){
    m.k=k;
    if(model=="IC")
        m.setInfuModel(InfGraph::IC);
    else if(model=="LT")
        m.setInfuModel(InfGraph::LT);
    else
        ASSERT(false);

    m.EstimateOPT(epsilon);

    OutputSeedSetToFile(m.seedSet, seedfile);

}
void parseArg(int argn, char ** argv)
{
    string dataset="";
    string seedfile="";

    double epsilon=0;
    string model="";
    int k=0;

    for(int i=0; i<argn; i++)
    {
        if(argv[i]==string("-dataset")) dataset=string(argv[i+1])+"/";
        if(argv[i]==string("-epsilon")) epsilon=atof(argv[i+1]);
        if(argv[i]==string("-k")) k=atoi(argv[i+1]);
        if(argv[i]==string("-model")) {
            if(argv[i+1]==string("LT"))
            {
                model=argv[i+1];
            }
            else if(argv[i+1]==string("IC"))
            {
                model=argv[i+1];
            }
            else
                ExitMessage("model should be IC or LT");
        }
        if(argv[i]==string("-seedfile")) seedfile=string(argv[i+1]);
    }
    if (dataset=="")
        ExitMessage("argument dataset missing");
    if (k==0)
        ExitMessage("argument k missing");
    if (epsilon==0)
        ExitMessage("argument epsilon missing");
    if (model=="")
        ExitMessage("argument model missing");


    string graph_file;
    if(model=="IC")
        graph_file=dataset + "graph_ic.inf";
    else if(model=="LT")
        graph_file=dataset + "graph_lt.inf";

    TimGraph m(dataset, graph_file);
    run(m, dataset, k ,  epsilon, model, seedfile );
}





int main(int argn, char ** argv)
{
    // OutputInfo info(argn, argv);
    parseArg( argn, argv );
    cout<<"Memory: "<<getProcMemory()<<" MB"<<endl;
}






