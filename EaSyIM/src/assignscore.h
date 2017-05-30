//
// Created by cuonghn on 28/5/17.
//

void EasyIMAssignScore(int max_length)
{
    init_score();
    if (influModel == IC)
    {
        for (int step=0; step < max_length; step++)
        {
            fill(new_score.begin(), new_score.end(), 0.0);
            // for each node
            for (int i = 0; i < n; i++) {
                // for each outgoing edge from node i
                if (visit[i]) continue;
                for (int j = 0; j < (int) g[i].size(); j++) {
                    int v = g[i][j];
                    if (!visit[v]) {
                        new_score[i] += 0.1 * (1 + cur_score[v]);
                    }
                }
            }
        }
        // update current score after each step
        cur_score = new_score;
    }
    else if (influModel == WC)
        for (int step=0; step < max_length; step++)
        {
            fill(new_score.begin(), new_score.end(), 0.0);
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
    else if (influModel == LT)
        for (int step=0; step < max_length; step++)
        {
            fill(new_score.begin(), new_score.end(), 0.0);
            // for each node
            for (int i = 0; i < n; i++)
            {
                // for each outgoing edge from node i
                if (visit_thresh_hold[i] < 0) continue;
                for (int j = 0; j < (int)g[i].size(); j++)
                {
                    int v = g[i][j];
                    if (visit_thresh_hold[v] > 0)
                    {
                        new_score[i] += prob[i][j] * (1 + cur_score[v]);
                    }
                }
            }
            // update current score
            cur_score = new_score;
        }
}
