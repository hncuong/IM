#include "graph.h"

class MC : public Graph
{
public:
	MC(string folder, string graph_file) :Graph(folder, graph_file){
	}

	set<int> seedSet;

	double Influence(int nMonteCarlo){// if not node then edge
		double inf;
		if (influModel == IC)
			inf = InfluenceIC(nMonteCarlo, seedSet);
		else if (influModel == WC)
			inf = InfluenceWC(nMonteCarlo, seedSet);
		else if (influModel == LT)
			inf = InfluenceLT(nMonteCarlo, seedSet);
		else
			ASSERT(false);
		//TRACE(inf, inf / n);
		return inf;
	}

	double InfluenceIC(int nMonteCarlo, set<int> startSet){

		ASSERT(nMonteCarlo > 0);
		double influence = 0;
		for (int x = 0; x<nMonteCarlo; x++){
			vector< int> visit_local(n);
			//TRACE("montecarlo", i);
			queue<int> q;
			for (int i : startSet){
				q.push(i);
				visit_local[i] = true;
				influence++;
			}
			while (!q.empty()) {
				//TRACE(q.size());
				int expand = q.front();
				q.pop();
				int i = expand;
				for (int j = 0; j<(int)OutNode[i].size(); j++){
					int v = OutNode[i][j];
					double randDouble = sfmt_genrand_real1(&sfmtSeed);

					if (randDouble > 0.1) //This is the only difference with IC
						continue;
					if (visit_local[v])
						continue;
					visit_local[v] = true;
					q.push(v);
					influence++;
				}
			}
		}
		return influence / nMonteCarlo;
	}

	double InfluenceWC(int nMonteCarlo, set<int> startSet){

		ASSERT(nMonteCarlo > 0);
		double influence = 0;
		for (int x = 0; x<nMonteCarlo; x++){
			vector< int> visit_local(n);
	
			queue<int> q;
			for (int i : startSet){
				q.push(i);
				visit_local[i] = true;
				influence++;
			}
			while (!q.empty()) {
	
				int expand = q.front();
				q.pop();
				int i = expand;
				for (int j = 0; j<(int)OutNode[i].size(); j++){
					int v = OutNode[i][j];
					double randDouble = sfmt_genrand_real1(&sfmtSeed);

					if (randDouble > probT[i][j])
						continue;
					if (visit_local[v])
						continue;
					visit_local[v] = true;
					q.push(v);
					influence++;
				}
			}
		}
		return influence / nMonteCarlo;
	}	


	double InfluenceLT(int nMonteCarlo, set<int> startSet){

		ASSERT(nMonteCarlo > 0);
		double influence = 0;
		for (int i = 0; i<nMonteCarlo; i++){
			queue<int> q_local;
			vector<int> visit_local(n);
			vector<double> active(n);
			for (int i = 0; i<n; i++){
				double randDouble = sfmt_genrand_real1(&sfmtSeed);
				active[i] = randDouble;
			}  //the threshold is initialized every time for each Monte-Simulation.
			for (int i : startSet){
				q_local.push(i);
				visit_local[i] = true;
			}
			while (!q_local.empty()) {
				influence++;      //different from IC and WC to count the influenced number
				//TRACE(q_local.size());
				int expand = q_local.front();
				q_local.pop();
				set<int> t = ExpandLT(expand, active);  //there is always at most one node in set t, right? Wrong! Can be multiple nodes, actually.  
				for (auto v : t)
				{
					if (visit_local[v] == false){
						visit_local[v] = true;
						q_local.push(v);
						//TRACE(expand, v);
					}
				}
			}
		}
		return influence / nMonteCarlo;
	}

	set<int> ExpandLT(int u, vector<double>& active){
		set<int> rtn;
		for (int v : OutNode[u]){
			double p = 1.0 / inDeg[v];
			//double p = probT[u][v];
			//TRACE(u, v, p, 1.0/inDeg[v]);
			if (active[v]>0 && active[v] - p<0)
			{
				//TRACE("-----------------------", u, v);
				rtn.insert(v);
			}
			//TRACE(u, v, inDeg[v]);
			active[v] -= p;
		}
		return rtn;
	}

};