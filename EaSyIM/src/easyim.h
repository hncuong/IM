//
// Created by cuonghn on 26/5/17.
//

#ifndef IM_EASYIM_H
#define IM_EASYIM_H

#endif //IM_EASYIM_H


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
        cout<<"TotalSample "<<rr_num/arg.time<<endl;
    }
};