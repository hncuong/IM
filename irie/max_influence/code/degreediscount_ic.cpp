#include "degreediscount_ic.h"
#include "graph.h"
#include <stdio.h>
#include <string.h>

int DegreeDiscount_IC::n = 0;
vector<int> DegreeDiscount_IC::d(MAX_NODE,0);
int DegreeDiscount_IC::list[MAX_K] = {0};
char DegreeDiscount_IC::file[] = "degreediscount_ic.txt";

void DegreeDiscount_IC::Build(double ratio)
{
	n = Graph::GetN();
	d.resize(n);
	for (int i=0; i<n; i++)
		d[i] = Graph::GetDegree(i);
	bool *used=new bool[n];
	memset(used, 0, sizeof(bool)*n);
	int *count=new int[n];
	memset(count, 0, sizeof(int)*n);

	FILE *out;
	fopen_s(&out, file, "w");
	for (int i=0; i<SET_SIZE; i++)
	{
		double max = -1000000.0;
		int mp = -1;
		for (int j=0; j<n; j++)
			if (!used[j])
			{
				double tmp = d[j]-2*count[j]-ratio*count[j]*(d[j]-count[j]);
				if (tmp >max)
				{
					max = tmp;
					mp = j;
				}
			}

		list[i] = mp;
		used[mp] = true;
		fprintf(out, "%ld %ld\n", mp, d[mp]);

		for (int j=0; j<Graph::GetNeighbor(mp); j++)
		{
			Edge e = Graph::GetEdge(mp, j);
			count[e.v]+=e.c;
		}
	}
	fclose(out);
}

void DegreeDiscount_IC::BuildFromFile()
{
	n = Graph::GetN();
	FILE* in;
	fopen_s(&in, file, "r");
	for (int i=0; i<n; i++)
		fscanf_s(in, "%ld %Lg", &list[i], &d[list[i]]);
	fclose(in);
}

int  DegreeDiscount_IC::GetNode(int i)
{
	if (i<0)
		return -1;
	if (i>=n) 
		return -1;
	return list[i];
}


