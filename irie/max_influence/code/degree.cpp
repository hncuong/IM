#include "degree.h"
#include "graph.h"
#include <stdio.h>

int Degree::n = 0;
vector<int> Degree::d(MAX_NODE,0);
int Degree::list[SET_SIZE];
char Degree::file[] = "degree.txt";

void Degree::qsort_degree(int h, int t)
{
	if (h<t) 
	{
		int i = h, j = t;
		int midd = d[(i+j)/2];
		int midn = list[(i+j)/2];
		d[(i+j)/2] = d[i];
		list[(i+j)/2] = list[i];

		while (i<j) 
		{
			while ((i<j) && (d[j]<midd))
				j--;
			if (i<j) {
				d[i] = d[j];
				list[i] = list[j];
				i++;
			}
			while ((i<j) && (d[i]>midd))
				i++;
			if (i<j) {
				d[j] = d[i];
				list[j] = list[i];
				j--;
			}
		}

		d[i] = midd;
		list[i] = midn;
		qsort_degree(h, i-1);
		qsort_degree(i+1, t);
	}
}

void Degree::Build(char data[])
{
	n = Graph::GetN();
	d.resize(n);
	for (int i=0; i<n; i++)
		d[i] = Graph::GetDegree(i);

	for (int i=0; i<SET_SIZE; i++)
	{	
		int max = 0;
		for (int j=0; j<n; j++)
			if (d[j]>d[max])
				max = j;
		d[max] = 0;
		list[i] = max;
	}

//	qsort_degree(0, n-1);

	sprintf_s(file,"DEGREE_%s", data);
	FILE *out;
	fopen_s(&out, file, "w");
	fprintf(out, "%d\n", SET_SIZE);
	for (int i=0; i<SET_SIZE; i++)
		fprintf(out, "%d\n", list[i]);
	fclose(out);
}

void Degree::BuildFromFile()
{
	n = Graph::GetN();
	d.resize(SET_SIZE);
	FILE* in;
	fopen_s(&in, file, "r");
	for (int i=0; i<SET_SIZE; i++)
		fscanf_s(in, "%ld %ld", &list[i], &d[i]);
	fclose(in);
}

int  Degree::GetNode(int i)
{
	if (i<0)
		return -1;
	if (i>=n) 
		return -1;
	return list[i];
}


