//
// Created by cuonghn on 26/5/17.
//

//#ifndef IM_INFGRAPH_H
//#define IM_INFGRAPH_H
//
//#endif //IM_INFGRAPH_H

class InfGraph : public Graph{
private:
    vector<bool > visit;
public:
    vector<double > cur_score;
    vector<double > new_score;
    vector<vector<int>> hyperG;

    InfGraph(string folder, string graph_file): Graph(folder, graph_file){
        srand(time(NULL));
        sfmt_init_gen_rand(&sfmtSeed , rand());
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

    void EasyIMAssignScore(int max_length)
    {
        init_score();
        for (int step=0; step < max_length; step++){
            // for each node
            for (int i = 0; i < n; i++)
            {
                // for each outgoing edge from node i
                if (visit[i]) continue;
                for (int j = 0; j < (int)g[i].size(); j++)
                {
                    int v = g[i][j];
                    if (!visit[v])
                    {
                        new_score[i] += prob[i][j] * (1 + cur_score[v]);
                    }
                }
            }
            // update current score
            cur_score = new_score;
        }
    }

    void UpdateActivatedNodes(int seed_node)
    {
        q.clear();
        q.push_back(seed_node);
        visit[seed_node] = true;
        // update visited nodes start from seed node
        if (influModel == IC) {
            while (!q.empty()) {
                int expand = q.front();
                q.pop_front();
                int i = expand;
                for (int j = 0; j < (int) g[i].size(); j++)
                {
                    int v = g[i][j];
                    double randDouble = sfmt_genrand_real1(&sfmtSeed);
                    if (randDouble > prob[i][j])
                        continue;
                    if (visit[v])
                        continue;
                    if (!visit[v]) {
                        visit[v] = true;
                    }
                    q.push_back(v);
                }

            }
        }
    }
};