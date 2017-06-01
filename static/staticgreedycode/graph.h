#ifndef GRAPH_H
#define GRAPH_H

#include "limit.h"
#include <vector>

using namespace std;

struct Edge 
{
	int u,v,c;	
	double w1,w2;
};

class Graph
{
private:
	static int n;
	static int m;
	static vector<int> degree;
	static vector<int> indegree;
	static vector<int> outdegree;
	static void qsort_edges(int h, int t);

public:
	static void QuickSort(int p,int r);
    static int partion(int p,int r);
	static void insertsort_edges(int right);
	static void merge_edges(int start, int middle, int left);
	static void mergesort_edges(int start, int end);
	static void merge(int start, int middle, int end);
	static bool built;
	static vector<int> index;
	static vector<int> correspond;
	static void	Build();
	static int	GetN();
	static int	GetM();
	static vector<Edge> edges;
	static int	GetDegree(int node);
	static int	GetOutDegree(int node);
	static int	GetInDegree(int node);
	static int	GetNeighbor(int node);
	static Edge	GetEdge(int node, int idx);
	static void BuildIC();
	static void BuildWC();
	static void Build2GC();
	static void Build2WC();
	static void Build2DWC();
	static void BuildFromFile2DWC(char *file); //directed graph + wic
	static void BuildFromFile2OIC(char *file);
	static void BuildFromFile2DUC(char *file, double p);//directed graph + uic
	static void BuildFromFile2WC(char *file);// undirected graph + wic
	static void BuildFromFile2UC(char *file, double p);//undirected graph + uic
	static void Build2IC();
	static void sortEdges();

	/*
	static void Build2DIC(double, double);
	static void Build2RIC(double, double);
	static void Build2TIC(double, double, double);
	static void Build2DT(double, double, double);
	static void Build2T(double, double, double);
	*/
	static void Stats();
};

#endif

