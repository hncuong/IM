#include "limit.h"
#include "graph.h"

#include "random.h"
#include "degree.h"
#include "greedy.h"
#include "degreediscount_ic.h"
#include "weighteddegree.h"

#include "SPM_gc.h"
#include "SP1M_gc.h"
#include "pmia.h"
#include "pagerank.h"
#include "general_cascade.h"
#include "mia.h"
#include "ir.h"
#include "irie.h"
#include "heap.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <io.h>
#include <string>
#include <windows.h>
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

FILE* timetmpfile;
double timer;
LARGE_INTEGER Start, End, Freq;

void toSimulate(char *file, int (*GetNode)(int i), double (*Run)(int num_iter, int size, int set[]))
{
	ofstream out;
	out.open(file);
	
	int set[MAX_NODE];
	for (int t=0; t<SET_SIZE; t++)
	{
		set[t] = GetNode(t);
		out << t + 1 << '\t' <<  Run(NUM_ITER, t+1, set) << endl;
	}
	out.close();
}

double toSimulateOnce(int setsize, int (*GetNode)(int i), double (*Run)(int num_iter, int size, int set[]))
{
	int set[MAX_NODE];
	int t;
	for (t=0; t<setsize; t++)
	{
		set[t] = GetNode(t);

		printf("%d\n", set[t]);
	}
	return Run(NUM_ITER, t, set);
}

int main(int argc, char * argv[])
{
	srand(time_t(NULL));
	//srand(100);
	QueryPerformanceFrequency(&Freq);
	system("mkdir tmp");
	system("cd tmp");

	ofstream timeFile;
	ofstream simulationFile;
	ofstream controlFile;

	char timeFileName[100];
	char simulationFileName[100];
	char controlFileName[100];
	
	if (argc<=1)
	{ 
		printf("-st : statistics of the weighted cascade graph\n");
		printf("-stg : statistics of the general indepEndent cascade graph\n");
		printf("-b : baseline(random, degree, degreediscount, weighteddegree, pagerank) for general ic\n");
		printf("-g : greedy, SPM and SP1M for general ic\n");
		printf("-p bound1 bound2 : PMIA with 1/theta from bound1 to bound 2\n");
		printf("-m bound1 bound2 : MIA with 1/theta from bound1 to bound 2\n");
		printf("example: max_influence -p 20 2000 < hep.inf \n");
		return 0;
	}
	string s;
	/*
	s="-st";
	if (!s.compare(argv[1]))
	{
		Graph::Build();
		Graph::Stats();
	}
	s="-stg";
	if (!s.compare(argv[1]))
	{
		Graph::Build2GC();
		Graph::Stats();
	}
	*/

	s="-d";
	if (!s.compare(argv[1]))
	{
		Graph::Build2WC(argv[argc - 1]);
		GeneralCascade::Build();

		// Highest Degree
		QueryPerformanceCounter(&Start);
		Degree::Build(argv[argc - 1]);
		QueryPerformanceCounter(&End);
		timer = (double)(End.QuadPart - Start.QuadPart) / Freq.QuadPart;
		sprintf(timeFileName, "time_DEGREE_%s", argv[argc - 1]);
		timeFile.open(timeFileName);
		timeFile << timer << endl;
		timeFile.close();
		//sprintf(simulationFileName, "sim_DEGREE_%s", argv[argc - 1]);
		//toSimulate(simulationFileName, Degree::GetNode, GeneralCascade::Run);
	}

	s="-pr";
	if (!s.compare(argv[1]))
	{
		Graph::Build2WC(argv[argc - 1]);
		GeneralCascade::Build();
	
		/*
		// Random
		QueryPerformanceCounter(&Start);
		Random::Build();
		QueryPerformanceCounter(&End);
		timer = (double)(End.QuadPart - Start.QuadPart) / Freq.QuadPart;
		fopen_s(&timetmpfile, "time_random.txt", "w");
		fprintf(timetmpfile,"%lg\n", timer);
		fclose(timetmpfile);
		toSimulate("GC_Random.txt", Random::GetNode, GeneralCascade::Run);
		// Weighted Degree
		QueryPerformanceCounter(&Start);
		WeightedDegree::Build();
		QueryPerformanceCounter(&End);
		timer = (double)(End.QuadPart - Start.QuadPart) / Freq.QuadPart;
		fopen_s(&timetmpfile, "time_weighteddegree.txt", "w");
		fprintf(timetmpfile,"%lg\n", timer);
		fclose(timetmpfile);
		toSimulate("GC_WeightedDegree.txt", WeightedDegree::GetNode, GeneralCascade::Run);

		// Highest Degree
		QueryPerformanceCounter(&Start);
		Degree::Build();
		QueryPerformanceCounter(&End);
		timer = (double)(End.QuadPart - Start.QuadPart) / Freq.QuadPart;
		fopen_s(&timetmpfile, "time_degree.txt", "w");
		fprintf(timetmpfile,"%lg\n", timer);
		fclose(timetmpfile);
		toSimulate("GC_Degree.txt", Degree::GetNode, GeneralCascade::Run);

		// DegreeDiscountIC
		QueryPerformanceCounter(&Start);
		DegreeDiscount_IC::Build(0.01);
		QueryPerformanceCounter(&End);
		timer = (double)(End.QuadPart - Start.QuadPart) / Freq.QuadPart;
		fopen_s(&timetmpfile, "time_degreediscount_ic.txt", "w");
		fprintf(timetmpfile,"%lg\n", timer);
		fclose(timetmpfile);
		toSimulate("GC_DiscountIC.txt", DegreeDiscount_IC::GetNode, GeneralCascade::Run);
		*/

		// Pagerank
		GeneralCascade::Build();
		QueryPerformanceCounter(&Start);
		pagerank::Build(SET_SIZE, argv[argc - 1]);
		QueryPerformanceCounter(&End);
		timer = (double)(End.QuadPart - Start.QuadPart) / Freq.QuadPart;
		sprintf(timeFileName, "time_PAGERANK_%s", argv[argc - 1]);
		timeFile.open(timeFileName);
		timeFile << timer << endl;
		timeFile.close();
		//sprintf(simulationFileName, "sim_PAGERANK_%s", argv[argc - 1]);
		//toSimulate(simulationFileName, pagerank::GetNode, GeneralCascade::Run);
	}

	s = "-ir";
	if (!s.compare(argv[1]))
	{
		//Influence Rank
		Graph::Build2WC(argv[argc - 1]);
		GeneralCascade::Build();
		double bound1 = 0.1, bound2 = 0.9;

		if (argc == 5)
		{
			sscanf_s(argv[2],"%lf",&bound1);
			sscanf_s(argv[3],"%lf",&bound2);
		}

		sprintf(timeFileName, "time_IR_%s", argv[argc - 1]);
		timeFile.open(timeFileName);

		for (double bound = bound1; bound <= bound2; bound += 0.1)
		{
			QueryPerformanceCounter(&Start);
			IR::Build(SET_SIZE, bound, argv[argc - 1]);
			QueryPerformanceCounter(&End);
			timer = (double)(End.QuadPart - Start.QuadPart) / Freq.QuadPart;
			timeFile << timer << endl;
			//sprintf(simulationFileName, "sim_IR_%.1f_%s", bound, argv[argc - 1]);
			//toSimulate(simulationFileName, IR::GetNode, GeneralCascade::Run);
		}
		timeFile.close();
	}

	s = "-irie";
	if(!s.compare(argv[1]))
	{
		//Influence Rank Influence Estimation
		Graph::Build2WC(argv[argc - 1]);
		GeneralCascade::Build();
		double bound1 = 0.1, bound2 = 0.9;
		if (argc == 5)
		{
			sscanf_s(argv[2],"%lf",&bound1);
			sscanf_s(argv[3],"%lf",&bound2);
		}

		sprintf(timeFileName, "time_IRIE_i3_%s", argv[argc - 1]);
		timeFile.open(timeFileName);

		QueryPerformanceCounter(&Start);
		double alpha = IRIE::Build(SET_SIZE, bound1, bound2, argv[argc - 1]);
		QueryPerformanceCounter(&End);
		timer = (double)(End.QuadPart - Start.QuadPart) / Freq.QuadPart;
		timeFile << timer << endl;
		sprintf(simulationFileName, "sim_IRIE_%.1f_i3_%s", alpha, argv[argc - 1]);
		toSimulate(simulationFileName, IRIE::GetNode, GeneralCascade::Run);

		//cout << "optimal alpha = " << alpha << endl;

		timeFile.close();
	}

	// GreedyGC (improved by CELF)
	s ="-g";
	if (!s.compare(argv[1]))
	{
		Graph::Build2WC(argv[argc - 1]);
		GeneralCascade::Build();
		QueryPerformanceCounter(&Start);
		Greedy::Build(SET_SIZE,GeneralCascade::Run, argv[argc - 1]);
		QueryPerformanceCounter(&End);
		timer = (double)(End.QuadPart - Start.QuadPart) / Freq.QuadPart;
		sprintf(timeFileName, "time_GREEDY_%s", argv[argc - 1]);
		timeFile.open(timeFileName);
		timeFile << timer << endl;
		timeFile.close();
		//system("copy greedy.txt greedy_gc.txt");
		//system("del /Q tmp\\*");
		//sprintf(simulationFileName, "sim_GREEDY_%s", argv[argc - 1]);
		//toSimulate(simulationFileName, Greedy::GetNode, GeneralCascade::Run);
/*
		// GreedyGC_SPM (improved by CELF)
		QueryPerformanceCounter(&Start);
		Greedy::Build(SET_SIZE,SPM_gc::Run);
		QueryPerformanceCounter(&End);
		timer = (double)(End.QuadPart - Start.QuadPart) / Freq.QuadPart;
		fopen_s(&timetmpfile, "time_greedy_gc_spm.txt", "w");
		fprintf(timetmpfile,"%lg\n", timer);
		fclose(timetmpfile);
		system("copy greedy.txt greedy_gc_spm.txt");
		system("del /Q tmp\\*");
		toSimulate("GC_SPM.txt", Greedy::GetNode, GeneralCascade::Run);

		// GreedyGC_SP1M (improved by CELF)
		QueryPerformanceCounter(&Start);
		Greedy::Build(SET_SIZE,SP1M_gc::Run);
		QueryPerformanceCounter(&End);
		timer = (double)(End.QuadPart - Start.QuadPart) / Freq.QuadPart;
		fopen_s(&timetmpfile,"time_greedy_gc_sp1m.txt", "w");
		fprintf(timetmpfile,"%lg\n", timer);
		fclose(timetmpfile);
		system("copy greedy.txt greedy_gc_sp1m.txt");
		system("del /Q tmp\\*");
		toSimulate("GC_SP1M.txt", Greedy::GetNode, GeneralCascade::Run);
*/
	}
		//control bound to test PMIA_GC
	s="-p";
	if (!s.compare(argv[1]))
	{
		Graph::Build2WC(argv[argc - 1]);
		GeneralCascade::Build();
		int bound1=10, bound2=2000;
		if (argc>=3) sscanf_s(argv[2],"%d",&bound1);
		if (argc>=4) sscanf_s(argv[3],"%d",&bound2);
		
		for (int bound=bound1;bound<bound2; bound+=bound)
		{
			printf("%d ",bound);
			double spread, treesize=0;

			QueryPerformanceCounter(&Start);
			treesize=SPT_new::Build(SET_SIZE, bound, argv[argc - 1]);
			QueryPerformanceCounter(&End);
			printf("\n");
			timer = (double)(End.QuadPart - Start.QuadPart) / Freq.QuadPart;
			sprintf(timeFileName, "time_PMIA_%d_%s", bound, argv[argc - 1]);
			timeFile.open(timeFileName);
			timeFile << timer << endl;
			timeFile.close();
			//sprintf(simulationFileName, "sim_PMIA_%d_%s", bound, argv[argc - 1]);
			//toSimulate(simulationFileName, SPT_new::GetNode, GeneralCascade::Run);
		}
	}
/*
	//control bound to test MIA_GC
	s="-m";
	if (!s.compare(argv[1]))
	{
		Graph::Build2WC(argv[argc - 1]);
		GeneralCascade::Build();
		int bound1=10, bound2=2000;
		if (argc>=3) sscanf_s(argv[2],"%d",&bound1);
		if (argc>=4) sscanf_s(argv[3],"%d",&bound2);
		char SPTfilename[]="MIA_control.txt";
		FILE *out;
		fopen_s(&out, SPTfilename, "w");
		char timefilename[]="time_MIA_0000.txt";
		char SPT_new_WC[]="GC_MIA_0000.txt";
		for (int bound=bound1;bound<bound2; bound+=bound)
		{
			printf("%d ",bound);
			double spread, treesize=0;
			sprintf_s(timefilename,"time_MIA_%04d.txt", bound);
			sprintf_s(SPT_new_WC,"GC_MIA_%04d.txt",bound);
			{
				QueryPerformanceCounter(&Start);
				treesize=MIA::Build(SET_SIZE, bound);
				QueryPerformanceCounter(&End);
				printf("\n");
				timer = (double)(End.QuadPart - Start.QuadPart) / Freq.QuadPart;
				fopen_s(&timetmpfile, timefilename, "w");
				fprintf(timetmpfile,"%lg\n", timer);
				fclose(timetmpfile);
				spread=toSimulateOnce(SET_SIZE, MIA::GetNode, GeneralCascade::Run);
				toSimulate(SPT_new_WC, MIA::GetNode, GeneralCascade::Run);
			}
			fprintf(out,"%lg %lg %d %lg\n", timer, spread, bound, treesize);
		}
	fclose(out);
	}
	*/
}