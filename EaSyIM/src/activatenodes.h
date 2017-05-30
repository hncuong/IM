//
// Created by cuonghn on 28/5/17.
//

void UpdateActivatedNodes(int seed_node)
{
    q.clear();
    q.push_back(seed_node);
    visit_mark++;

    // update visited nodes start from seed node
    if (influModel == WC)
    {
        visit[seed_node] = true;
        while (!q.empty())
        {
            int expand = q.front();
            q.pop_front();
            int i = expand;
            for (int j = 0; j < (int) g[i].size(); j++)
            {
                int v = g[i][j];
                if (visit[v])
                    continue;

                double randDouble = sfmt_genrand_real1(&sfmtSeed);
                if (randDouble > prob[i][j])
                    continue;
                if (!visit[v])
                {
                    visit[v] = true;
                }
                q.push_back(v);
                visit_mark++;
            }
        }
    }
    else if (influModel == IC)
    {
        visit[seed_node] = true;
        while (!q.empty())
        {
            int expand = q.front();
            q.pop_front();
            int i = expand;
            for (int j = 0; j < (int) g[i].size(); j++)
            {
                int v = g[i][j];
                if (visit[v])
                    continue;
                double randDouble = sfmt_genrand_real1(&sfmtSeed);
                if (randDouble > 0.1)
                    continue;
                if (!visit[v])
                {
                    visit[v] = true;
                }
                q.push_back(v);
                visit_mark++;
            }
        }
    }
    else if (influModel == LT)
    {
        visit_thresh_hold[seed_node] = -1.0;
        while (!q.empty())
        {
            int expand = q.front();
            q.pop_front();
            int i = expand;
            // search on outgoing edges
            for (int j = 0; j < (int) g[i].size(); j++)
            {
                int v = g[i][j];
                // if activated : skip
                if (visit_thresh_hold[v] < 0.0)
                    continue;
                double randDouble;
                // generate threshold if not generated (node unvisited)
                if (visit_thresh_hold[v] > 1.0)
                {
                    randDouble = sfmt_genrand_real1(&sfmtSeed);
                    visit_thresh_hold[v] = randDouble;
                } else
                    randDouble = visit_thresh_hold[v];
                // search incoming edges
                for (int k = 0; k < (int) gT[v].size(); k++)
                {
                    int t = gT[v][k];
                    // for activated node
                    if (visit_thresh_hold[t] < 0.0)
                        randDouble -= probT[v][k];
                }
                // if thresh hold <= 0: activate it
                if (randDouble <= 0.0)
                {
                    q.push_back(v);
                    visit_thresh_hold[v] = -1.0;
                    visit_mark++;
                }
            }
        }
    }
}
