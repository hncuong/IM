#include "degreediscount.h"
#include "graph.h"
#include <stdio.h>
#include <string.h>

int DegreeDiscount::n = 0;
int DegreeDiscount::d[MAX_NODE] = {0};
int DegreeDiscount::list[MAX_NODE] = {0};
char DegreeDiscount::file[] = "degreediscount.txt";

void DegreeDiscount::Build()
{
	n = Graph::GetN();
	for (int i=0; i<n; i++)
		d[i] = Graph::GetDegree(i);
	bool used[MAX_NODE];
	memset(used, 0, sizeof(bool)*MAX_NODE);
	FILE *out;
	fopen_s(&out, file, "w");
	for (int i=0; i<SET_SIZE; i++)
	{
		int max = -1, mp = -1;
		for (int j=0; j<n; j++)
			if (!used[j])
				if (d[j]>max)
				{
					max = d[j];
					mp = j;
				}

		list[i] = mp;
		used[mp] = true;
		fprintf(out, "%d %d\n", list[i], d[i]);

		for (int j=0; j<Graph::GetNeighbor(mp); j++)
		{
			Edge e = Graph::GetEdge(mp, j);
			d[e.v]-=e.c;
		}
	}
	fclose(out);
}

void DegreeDiscount::BuildFromFile()
{
	n = Graph::GetN();
	FILE* in;
	fopen_s(&in, file, "r");
	for (int i=0; i<n; i++)
		fscanf_s(in, "%ld %ld", &list[i], &d[i]);
	fclose(in);
}

int  DegreeDiscount::GetNode(int i)
{
	if (i<0)
		return -1;
	if (i>=n) 
		return -1;
	return list[i];
}


