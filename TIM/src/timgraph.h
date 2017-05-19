class TimGraph: public InfGraph
{
    public:
        TimGraph(string folder, string graph_file):InfGraph(folder, graph_file ){
        }
        double MgT(int u){
            //static int i=0;
            //i++;
            //TRACE_LINE("mgt", i);
            ASSERT(u>=0);
            ASSERT(u<n);
            return (double)BuildHypergraphNode(u, 0, false);
        }
        double algo2(){
            double lb=1/2.0;
            double temp=0;
            double c=0;
            while(true){
                int loop= (6 * log(n)  +  6 * log(log(n)/ log(2)) )* 1/lb  ;
                c=0;
                IF_TRACE(int64 now=rdtsc());
                double sumMgTu=0;
                for(int i=0; i<loop; i++){
                    int u=rand()%n;
                    double MgTu=MgT(u);
                    temp+=MgTu;
                    double pu=MgTu/m;
                    sumMgTu+=MgTu;
                    c+=1-pow((1-pu), k);
                }
                c/=loop;
                if(c>lb) break;
                lb /= 2;
            }
            cout<<"temp="<<temp<<endl;
            return c * n;
        }
        double KptEstimation()
        {
            Timer t(1, "step1");
            double ept=algo2();
            ept/=2;
            return ept;
        }
        void RefindKPT(double epsilon, double ept){
            Timer t(2, "step2" );
            ASSERT(ept > 0);
            int64 R = (2 + epsilon) * ( n * log(n) ) / ( epsilon * epsilon * ept);
            BuildHypergraphR(R);
        }
        double logcnk(int n, int k){
            double ans=0;
            for(int i=n-k+1; i<=n; i++){
                ans+=log(i);
            }
            for(int i=1; i<=k; i++){
                ans-=log(i);
            }
            return ans;
        }
        void NodeSelection(double epsilon, double opt){
            Timer t(3, "step3");
            ASSERT(opt > 0);
            int64 R = (8+2 * epsilon) * ( log(n) + log(2) +  n * logcnk(n, k) ) / ( epsilon * epsilon * opt);
            cout<<"R="<<R<<endl;
            BuildHypergraphR(R);
            BuildSeedSet();
        }
        double EstimateOPT(double epsilon){
            Timer t(100,"EstimateOPT");

            //int64 R=1000000;
            //double tau=BuildHypergraphR(R);
            //return tau;
            //BuildSeedSet();
            //cout<<"tau="<<tau<<endl;
            // KPT estimation
            double kpt_star;
            kpt_star=KptEstimation();
            cout<<"kpt_star="<<kpt_star<<endl;
            //return kpt_star;
            // Refine KPT
            double eps_prime;
            eps_prime=5*pow(sqr(epsilon)/(k+1), 1.0/3.0);
            RefindKPT(eps_prime, kpt_star);
            BuildSeedSet();
            double kpt=InfluenceHyperGraph();
            kpt/=1+eps_prime;
            double kpt_plus = max(kpt, kpt_star);
            cout<<"kpt_plus="<<kpt_plus<<endl;
            disp_mem_usage("");
            return kpt_plus;
            //Node Selection
            //NodeSelection(epsilon, kpt_plus);
            //disp_mem_usage("");
        }

};

