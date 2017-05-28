//
// Created by cuonghn on 28/5/17.
//

void UpdateActivatedNodes(int seed_node)
{
    q.clear();
    q.push_back(seed_node);
    visit[seed_node] = true;
    // update visited nodes start from seed node
    if (influModel == WC)
    {
        while (!q.empty())
        {
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
                if (!visit[v])
                {
                    visit[v] = true;
                }
                q.push_back(v);
            }

        }
    } else if (influModel == IC)
    {
        int expand = q.front();
        q.pop_front();
        int i = expand;
        for (int j = 0; j < (int) g[i].size(); j++)
        {
            int v = g[i][j];
            double randDouble = sfmt_genrand_real1(&sfmtSeed);
            if (randDouble > 0.1)
                continue;
            if (visit[v])
                continue;
            if (!visit[v])
            {
                visit[v] = true;
            }
            q.push_back(v);
        }
    }
}
