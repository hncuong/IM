//
// Created by cuonghn on 26/5/17.
//
#include <chrono>
#include <ctime>
#include <ratio>

using namespace std::chrono;


class EasyIM
{
public:
    static void InfluenceMaximize(InfGraph &g, const Argument &arg)
    {
        Timer t(100, "InfluenceMaximize(Total Time)");

        for (int i=0;i<arg.time;i++)
        {
            g.init_visit_state();
            g.BuildSeedSetGreedy(arg.k, arg.l);
        }
        disp_mem_usage();
    }
};