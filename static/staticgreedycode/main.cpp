#include "limit.h"
#include "graph.h"
#include "random.h"
#include "degree.h"
#include "greedy.h"
#include "degreediscount_ic.h"
#include "weighteddegree.h"
#include "staticgreedy.h"
#include "SPM_gc.h"
#include "SP1M_gc.h"
#include "pmia.h"
#include "pagerank.h"
#include "general_cascade.h"
#include "mia.h"
#include "staticgreedy_directed_new.h"
#include "staticgreedy_basic.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <io.h>
#include <string>
#include <iostream>
#include <fstream>
//#include <windows.h>

using namespace std;

FILE* timetmpfile;
double timer;
clock_t start_time, end_time;

void toSimulate(char *file, int (*GetNode)(int i), double (*Run)(int num_iter, int size, int set[]), double time, int R)
{
	FILE *out = fopen(file, "w");

	int set[MAX_NODE];
	fprintf(out,"R=\t%d\t%f\t\n",R, (double)(time)/CLOCKS_PER_SEC);
	int t;

	for (int t=0; t<SET_SIZE; t++)
	{
		set[t] = GetNode(t);
	    double temp = Run(20000, t+1, set);
	    fprintf(out, "k\t%02d\t%f\t\n", t+1, GeneralCascade::mean);
	}
	fprintf(out, "ids:\t\n");
	for(t=0; t<SET_SIZE; t++){
		fprintf(out, "%d\t\n", set[t]);
	}

	fprintf(out,"\n");
	fclose(out);
}

void toSimulateForStaticGreedy(char *file, int R, long time, int *seeds, double (*Run)(int num_iter, int size, int set[]))
{
	int set[MAX_NODE];
	double value[MAX_NODE];
	int t;

	for (t=0; t<SET_SIZE; t++)
	{
		set[t] = seeds[t];
		value[t] = Run(20000, t+1, set);
	}

	FILE *out = fopen(file, "w");
	fprintf(out,"R=\t%d\t%f\t\n",R, (double)(time)/CLOCKS_PER_SEC);

	for(t=0; t<SET_SIZE; t++){
			fprintf(out,"k\t%02d\t%f\t\n", t+1, value[t]);
	}
	
	fprintf(out, "ids:\t\n");
	for(t=0; t<SET_SIZE; t++){
		fprintf(out, "%d\t\n", seeds[t]);
	}
	fprintf(out,"\n");
	fclose(out);
}

double toSimulateOnce(int setsize, int (*GetNode)(int i), double (*Run)(int num_iter, int size, int set[]))
{
	int set[MAX_NODE];
	int t;
	for (t=0; t<setsize; t++)
	{
		set[t] = GetNode(t);
	}
	return Run(NUM_ITER, t, set);
}

int main(int argc, char * argv[])
{
	//srand(time_t(NULL));
	time_t t;
	srand((unsigned) time(&t));

    /***** note ******/
	// -sgu is only used for undirected graph under uic model
	// -sgd is used for two kinds of test cases: undirected graph under other models expect uic model, and directed graph under any model
	/****************/

	if (argc<=1) { 
		printf("-st : statistics of the weighted cascade graph\n");
		printf("-stg : statistics of the general independent cascade graph\n");
		printf("-b : baseline(random, degree, degreediscount, weighteddegree, pagerank) for general ic\n");
		printf("-g : greedy, SPM and SP1M for general ic\n");
		/**** staticgreedy start ****/
		printf("-bsg : basic static greedy for undirected graph under R snapshots\n");
		printf("-sgu :  improved static greedy for undirected cases(undirected graph + UIC model) under R snapshots \n");
		printf("-sgd : improved static greedy for directed cases(undirected graph + UIC model / directed graph + any model)  under R snapshots \n");
		/**** staticgreedy end ****/
		printf("-p bound1 bound2 : PMIA with 1/theta from bound1 to bound 2\n");
		printf("-m bound1 bound2 : MIA with 1/theta from bound1 to bound 2\n");
		return 0;
	}
	string s;


	s="-stg";
	if (!s.compare(argv[1])) {
		Graph::Build2GC();
		Graph::Stats();
	}

	//file
	char filename[100] = "E:/newcode2/networks/hep.txt";
	bool directed = false;


	

	int R = 100;

	//build graph, need to be built according to different networks and models
	Graph::BuildFromFile2WC(filename); 

	GeneralCascade::Build();



	s="-st";
	if (!s.compare(argv[1])) {
		Graph::Build();
		Graph::Stats();
	}

	// GreedyGC (improved by CELF)
	s="-g";
	if (!s.compare(argv[1])) {
		char outfile[50] = "Greedy_RS.txt";

		start_time = clock();
		Greedy::Build(SET_SIZE, R, GeneralCascade::Run);
		end_time = clock();
		timer = (double)(end_time-start_time);

		toSimulate(outfile, Greedy::GetNode, GeneralCascade::Run, timer, NUM_ITER);
	}


	s="-sp1m";// GreedyGC_SP1M (improved by CELF)
	if(!s.compare(argv[1])){
		//set ourfilename
		char outfile[50] = "SP1M_RS.txt";
		start_time = clock();
    	Greedy::Build(SET_SIZE,SP1M_gc::Run);
		end_time = clock();
    	toSimulate(outfile, Greedy::GetNode, GeneralCascade::Run, (double)(end_time-start_time), NUM_ITER);
	}

	s="-bsg";
	if(!s.compare(argv[1])){
		char outfile[100] = "BasicStaticGreedy_RS.txt";
		start_time = clock();
		int *seeds = BasicStaticGreedy::GetSeeds(R, SET_SIZE);
		end_time = clock();
		long time = end_time-start_time;
		toSimulateForStaticGreedy(outfile, R, time, seeds, GeneralCascade::Run);
	}

	s="-sgu";
	if(!s.compare(argv[1])){
		char outfile[50] = "StaticGreedyUD_SGU_RS.txt";
		start_time = clock();
		int *seeds = StaticGreedy::GetSeedsFromUGraphForUIC(R, SET_SIZE);
		end_time = clock();
		long time = end_time-start_time;
		toSimulateForStaticGreedy(outfile, R, time, seeds, GeneralCascade::Run);
	}

	s="-sgd";
	if(!s.compare(argv[1])){
		char outfile[50] = "StaticGreedyUD_SGD_RS.txt";
		int *seeds;
		
		if(!directed){
				start_time = clock();
				seeds = StaticGreedyDirectedNew::GetSeedsForWICUNDirectedG(R, SET_SIZE);
				end_time = clock();
		}else{
				start_time = clock();
				seeds = StaticGreedyDirectedNew::GetSeedsForDirectedG(R, SET_SIZE);
				end_time = clock();
		}

		long time = end_time-start_time;
		toSimulateForStaticGreedy(outfile, R, time, seeds, GeneralCascade::Run);
	}

	//control bound to test PMIA_GC
	s="-p";
	if (!s.compare(argv[1])) {
		int bound1=10, bound2=2000;
		//sscanf(argv[5],"%d",&bound1);
		//sscanf(argv[6],"%d",&bound2);
	
		char SPTfilename[]="PMIA_control.txt";
		FILE *out = fopen(SPTfilename, "w");
		char timefilename[]="time_PMIA_0000.txt";
		char SPT_new_WC[]="GC_PMIA_0000.txt";
		for (int bound=bound1;bound<bound2; bound+=bound){
			printf("%d ",bound);
			double spread, treesize=0;
#ifdef COUNT
			{
				spread=SPT_new::Build(SET_SIZE, bound);
				printf("%f\n",spread);
				continue;
			}
#endif
			sprintf(timefilename,"time_PMIA_%04d.txt", bound);
			sprintf(SPT_new_WC,"GC_PMIA_%04d.txt",bound);
			{
				//QueryPerformanceCounter(&start);
				start_time = clock();
				treesize=SPT_new::Build(SET_SIZE, bound);
				end_time = clock();
				timer = (double)(end_time-start_time)/CLOCKS_PER_SEC;
				//QueryPerformanceCounter(&end);
				printf("\n");
				//timer = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
				timetmpfile = fopen(timefilename, "w");
				fprintf(timetmpfile,"%f\n", timer);
				fclose(timetmpfile);
				spread=toSimulateOnce(SET_SIZE, SPT_new::GetNode, GeneralCascade::Run);
				toSimulate(SPT_new_WC, SPT_new::GetNode, GeneralCascade::Run, timer, -1);
			}
			fprintf(out,"%f %f %d %f\n", timer, spread, bound, treesize);
		}
		fclose(out);
	}

	//control bound to test MIA_GC
	s="-m";
	if (!s.compare(argv[1])) {
		Graph::Build2WC();
		GeneralCascade::Build();
		int bound1=10, bound2=2000;
		//sscanf(argv[5],"%d",&bound1);
		//sscanf(argv[6],"%d",&bound2);

		char SPTfilename[]="MIA_control.txt";
		FILE *out = fopen(SPTfilename, "w");
		char timefilename[]="time_MIA_0000.txt";
		char SPT_new_WC[]="GC_MIA_0000.txt";
		for (int bound=bound1;bound<bound2; bound+=bound){
			printf("%d ",bound);
			double spread, treesize=0;
#ifdef COUNT
			{
				spread=SPT_new::Build(SET_SIZE, bound);
				printf("%f\n",spread);
				continue;
			}
#endif
			sprintf(timefilename,"time_MIA_%04d.txt", bound);
			sprintf(SPT_new_WC,"GC_MIA_%04d.txt",bound);
			{
				//QueryPerformanceCounter(&start);
				treesize=MIA::Build(SET_SIZE, bound);
				//QueryPerformanceCounter(&end);
				printf("\n");
				//timer = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
				timetmpfile = fopen(timefilename, "w");
				fprintf(timetmpfile,"%f\n", timer);
				fclose(timetmpfile);
				spread=toSimulateOnce(SET_SIZE, MIA::GetNode, GeneralCascade::Run);
				toSimulate(SPT_new_WC, MIA::GetNode, GeneralCascade::Run, timer, -1);
			}
			fprintf(out,"%f %f %d %f\n", timer, spread, bound, treesize);
		}
		fclose(out);
	}

}

