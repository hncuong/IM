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
        // Timer t(100, "InfluenceMaximize(Total Time)");
        high_resolution_clock::time_point startTime = high_resolution_clock::now();
        for (int i=0;i<arg.time;i++)
        {
            g.init_visit_state();
            g.BuildSeedSetGreedy(arg.k, arg.l);
        }
        disp_mem_usage();

        high_resolution_clock::time_point endTime = high_resolution_clock::now();
        duration<double> interval = duration_cast<duration<double>>(endTime-startTime);
        double timeUsed = (double)interval.count();
        
        char str[100];
        //sprintf(str,"%.6lf",timeUsed[i]/TIMES_PER_SEC );
        sprintf(str,"%.6lf", timeUsed/arg.time);
        string s=str;
        if ((int)s.size()<15) s=" "+s;
        char t[100];
        memset(t, 0, sizeof t);
        sprintf(t,"Spend %s seconds on InfluenceMaximize(Total Time)",s.c_str());
        cout<< t << endl;  
        
    }
};