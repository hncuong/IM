#include <chrono>
#include <ctime>
#include <ratio>

using namespace std::chrono;

class Math{
    public:
        static double log2(int n){
            return log(n) / log(2);
        }
        static double logcnk(int n, int k) {
            double ans = 0;
            for (int i = n - k + 1; i <= n; i++)
            {
                ans += log(i);
            }
            for (int i = 1; i <= k; i++)
            {
                ans -= log(i);
            }
            return ans;
        }
};
class Imm
{
    private:
        //static InfGraph g;
        //static int k;
        //static map<string, string> arg;
        static unsigned int rr_num;

        static double step1(InfGraph &g, const Argument & arg)
        {
            double epsilon_prime = arg.epsilon * sqrt(2);            
            Timer t(1, "step1");
            for (int x = 1; ; x++)
            {
                
                int64 ci = (2+2/3 * epsilon_prime)* ( log(g.n) + Math::logcnk(g.n, arg.k) + log(Math::log2(g.n))) * pow(2.0, x) / (epsilon_prime* epsilon_prime);                
                

                g.build_hyper_graph_r(ci, arg);              

                g.build_seedset(arg.k);
                double ept = g.InfluenceHyperGraph()/g.n;
                
                if (ept > 1 / pow(2.0, x))
                {
                    double OPT_prime = ept * g.n / (1+epsilon_prime);                
                    return OPT_prime;
                }
            }
            ASSERT(false);
            return -1;
        }

        static double step2(InfGraph &g, const Argument & arg, double OPT_prime)
        {
            Timer t(2, "step2");
            ASSERT(OPT_prime > 0);
            double e = exp(1);
            double alpha = sqrt(log(g.n) + log(2));
            double beta = sqrt((1-1/e) * (Math::logcnk(g.n, arg.k) + log(g.n) + log(2)));

            int64 R = 2.0 * g.n *  sqr((1-1/e) * alpha + beta) /  OPT_prime / arg.epsilon / arg.epsilon ;

          
            g.build_hyper_graph_r(R, arg);
            
            rr_num+=R;
           

            g.build_seedset(arg.k);
            double opt = g.InfluenceHyperGraph();
            return opt;
        }
    public:
        
       

        static void InfluenceMaximize(InfGraph &g, const Argument &arg)
        {
            Timer t(100, "InfluenceMaximize(Total Time)");            

   
            for (int i=0;i<arg.time;i++)
            {
                g.init_hyper_graph();
                double OPT_prime;
                OPT_prime = step1(g, arg ); //estimate OPT

                step2(g, arg, OPT_prime);
            }
            disp_mem_usage();
            cout<<"TotalSample "<<rr_num/arg.time<<endl;

        }

};
unsigned int  Imm::rr_num=0;

