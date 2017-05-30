//
// Created by cuonghn on 26/5/17.
//
#include "graph.h"
class InfGraph : public Graph{
private:
    vector<bool > visit;
    vector<double > visit_thresh_hold;
public:
    vector<double > cur_score;
    vector<double > new_score;
    vector<vector<int>> hyperG;

    enum InfluModel {IC, LT, WC};
    InfluModel influModel;
    void setInfuModel(const InfluModel& p)
    {
        influModel = p;
        TRACE(influModel == IC);
        TRACE(influModel == LT);
        TRACE(influModel == WC);
    }

    InfGraph(const string& folder, const string& graph_file,
             const InfluModel& influModel): Graph(folder, graph_file){
        srand(time(NULL));
        sfmt_init_gen_rand(&sfmtSeed , rand());
        setInfuModel(influModel);
        if (influModel == IC || influModel == WC)
            init_visit_state();
        else if (influModel == LT)
            init_visit_thresh_hold();
        init_score();
    }

    void init_visit_state()
    {
        visit = vector<bool > (n, false);
    }

    void init_visit_thresh_hold()
    {
        // assign all thresh hold to > 1 denote unvisited
        visit_thresh_hold = vector<double> (n, 2.0);
    }

    void init_score()
    {
        cur_score = vector<double > (n, 0.0);
        new_score = vector<double > (n, 0.0);
    }

    deque<int> q;
    sfmt_t sfmtSeed;
    set<int> seedSet;
    int visit_mark;


#include "assignscore.h"
#include "activatenodes.h"

    void BuildSeedSetGreedy(int k, int l)
    {
        visit_mark = 0;
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