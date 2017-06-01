#include "greedy.h"
#include "graph.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int Greedy::n = 0;
int Greedy::top = 0;
double Greedy::d[MAX_NODE] = {0};
int Greedy::list[MAX_NODE] = {0};
char Greedy::file[] = "greedy.txt";

void Greedy::Build(int num, int R, double (*Run)(int num_iter, int size, int set[]))
{
	//double timer;
    clock_t start_time, end_time;
	int simu_Num = 0;
	n = Graph::GetN();
	top = num;

	bool *used= new bool[n];
	memset(used, 0, sizeof(bool)*n);
	int set[SET_SIZE];

	double old = 0.0;

	double *improve=new double[n];
	int *lastupdate=new int[n];
	int *heap=new int[n];
	for (int i=0; i<n; i++)
	{
		heap[i] = i;
		lastupdate[i] = -1;
		improve[i] = (double)(n+1);
	}
	start_time = clock();
	for (int i=0; i<top; i++)
	{
		int ccc = 0;
		//printf("%d\n",i);
		while (lastupdate[heap[0]] != i)
		{
			ccc++;
			lastupdate[heap[0]] = i;
			set[i] = heap[0];

			improve[heap[0]] = Run(R, i+1, set) - old;
			simu_Num ++;
			int x = 0;
			while (x*2+2<=n-i)
			{
				int newx=x*2+1;
				if ((newx+1<n-i) && (improve[heap[newx]]<improve[heap[newx+1]]))
					newx++;
				if (improve[heap[x]]<improve[heap[newx]])
				{
					int t=heap[x];
					heap[x] = heap[newx];
					heap[newx] = t;
					x = newx;
				}
				else
					break;
			}
		}

		used[heap[0]] = true;
		set[i] = heap[0];
		list[i] = heap[0];
		d[i] = improve[heap[0]];
		old+=d[i];

		heap[0] = heap[n-i-1];
		int x = 0;
		while (x*2+2<=n-i)
		{
			int newx=x*2+1;
			if ((newx+1<n-i) && (improve[heap[newx]]<improve[heap[newx+1]]))
				newx++;
			if (improve[heap[x]]<improve[heap[newx]])
			{
				int t=heap[x];
				heap[x] = heap[newx];
				heap[newx] = t;
				x = newx;
			}
			else
				break;
		}
		end_time = clock();
		printf("%d\t%f\t%d\n", i+1, (double)(end_time-start_time)/CLOCKS_PER_SEC, simu_Num);
	}

	delete[] heap;
	delete[] lastupdate;
	delete[] improve;
	delete[] used;
}

void Greedy::Build(int num, double (*Run)(int num_iter, int size, int set[]))
{
	n = Graph::GetN();
	top = num;

	bool *used= new bool[n];
	memset(used, 0, sizeof(bool)*n);
	int set[SET_SIZE];

	double old = 0.0;

	double *improve=new double[n];
	int *lastupdate=new int[n];
	int *heap=new int[n];
	for (int i=0; i<n; i++)
	{
		heap[i] = i;
		lastupdate[i] = -1;
		improve[i] = (double)(n+1);
	}

	for (int i=0; i<top; i++)
	{
		int ccc = 0;
		//printf("%d\n",i);
		while (lastupdate[heap[0]] != i)
		{
			//printf("%d %d %d\n", i, heap[0], ccc);
			ccc++;
			lastupdate[heap[0]] = i;
			set[i] = heap[0];
			//printf("GreedyGC_SPM %d %d\n",heap[0],improve[heap[0]]);
			improve[heap[0]] = Run(NUM_ITER, i+1, set) - old;
			
			//char tmpfilename[200];
			//sprintf_s(tmpfilename, "tmp/%02d%05d.txt", i, heap[0]);
			//FILE *tmpfile;
			//fopen_s(&tmpfile, tmpfilename,"w");
			//fprintf(tmpfile, "%lg\n", improve[heap[0]]); 
			//fclose(tmpfile);

			int x = 0;
			while (x*2+2<=n-i)
			{
				int newx=x*2+1;
				if ((newx+1<n-i) && (improve[heap[newx]]<improve[heap[newx+1]]))
					newx++;
				if (improve[heap[x]]<improve[heap[newx]])
				{
					int t=heap[x];
					heap[x] = heap[newx];
					heap[newx] = t;
					x = newx;
				}
				else
					break;
			}
		}

		used[heap[0]] = true;
		set[i] = heap[0];
		list[i] = heap[0];
		d[i] = improve[heap[0]];
		old+=d[i];

		//char bakname[200];
		//sprintf(bakname, "greedychoice%02d.txt", i+1);
		//FILE *bak = fopen(bakname, "w");
		//fprintf(bak, "%6d\t%d\t%lg\n", i+1, heap[0], improve[heap[0]]);
		//fclose(bak);
		//printf("%d\t%lg\n", i+1, improve[131]);

		heap[0] = heap[n-i-1];
		int x = 0;
		while (x*2+2<=n-i)
		{
			int newx=x*2+1;
			if ((newx+1<n-i) && (improve[heap[newx]]<improve[heap[newx+1]]))
				newx++;
			if (improve[heap[x]]<improve[heap[newx]])
			{
				int t=heap[x];
				heap[x] = heap[newx];
				heap[newx] = t;
				x = newx;
			}
			else
				break;
		}
	}

	//FILE *out;
	//fopen_s(&out, file, "w");
	//fprintf(out, "%d\n", top);
	//for (int i=0; i<top; i++)
		//fprintf(out, "%d\t%Lg\n", list[i], d[i]);
	//fclose(out);
	delete[] heap;
	delete[] lastupdate;
	delete[] improve;
	delete[] used;
}

void Greedy::BuildFromFile(const char* name)
{
	n = Graph::GetN();
	FILE* in =	fopen(name, "r");
	fscanf(in, "%ld", &top);
	for (int i=0; i<top; i++)
		fscanf(in, "%ld %f", &list[i], &d[i]);
	fclose(in);
}

int  Greedy::GetNode(int i)
{
	if (i<0)
		return -1;
	if (i>=top) 
		return -1;
	return list[i];
}


