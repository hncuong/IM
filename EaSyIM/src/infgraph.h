//
// Created by cuonghn on 26/5/17.
//

class InfGraph : public Graph{
private:
    vector<bool > visit;
public:
    vector<double > cur_score;
    vector<double > new_score;
    vector<vector<int>> hyperG;

    enum InfluModel {IC, LT, WC};
    InfluModel influModel;
    void setInfuModel(InfluModel p)
    {
        influModel = p;
        TRACE(influModel == IC);
        TRACE(influModel == LT);
        TRACE(influModel == WC);
    }

    InfGraph(string folder, string graph_file, InfluModel influModel): Graph(folder, graph_file){
//        srand(time(NULL));
//        sfmt_init_gen_rand(&sfmtSeed , rand());
        sfmt_init_gen_rand(&sfmtSeed , 95082);
        setInfuModel(influModel);
        init_visit_state();
        init_score();
    }
    void init_visit_state(){
        visit = vector<bool > (n);
    }

    void init_score(){
        cur_score = vector<double > (n);
        new_score = vector<double > (n);
    }

    deque<int> q;
    sfmt_t sfmtSeed;
    set<int> seedSet;
#include "assignscore.h"
#include "activatenodes.h"
    void BuildSeedSetGreedy(int k, int l)
    {
        seedSet.clear();
        ASSERT(k > 0);
        ASSERT(k < n);
        for (int i = 0; i < k; i++)
        {
            EasyIMAssignScore(l);
            auto t = max_element(cur_score.begin(), cur_score.end());
            int id = t - cur_score.begin();
            seedSet.insert(id);
            UpdateActivatedNodes(id);
        }
    }
};