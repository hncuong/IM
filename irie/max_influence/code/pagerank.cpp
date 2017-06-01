#include "pagerank.h"
#include "graph.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <vector>

int pagerank::n = 0;
int pagerank::top = 0;
double pagerank::d[MAX_K];
int pagerank::list[MAX_K];
char pagerank::file[] = "pagerank.txt";

//int pagerank::k=1;
vector<int> pagerank::dd(MAX_NODE,0);
//double SPT_new::longest = log(100.0);
vector<double> pagerank::dp(MAX_NODE,1.0);
//vector<bool> SPT_new::used(MAX_NODE);
//vector<double *>SPT_new::self(MAX_NODE);
//vector<int> pagerank::lastupdate(MAX_NODE,-1);
//vector<double *>SPT_new::delta(MAX_NODE);
//vector<int *>SPT_new::children(MAX_NODE,NULL);
//vector<int *>SPT_new::path(MAX_NODE,NULL);

//int *SPT_new::S;
//double *SPT_new::distance, *SPT_new::b;
//int *SPT_new::heap;
//int *SPT_new::childlist, *SPT_new::oldchildlist, *SPT_new::parent;
//bool *SPT_new::validlist[MAX_K]={NULL};

//double ratio=0.01;

int pagerank::GetMax(int round)
{
		double max = -1000000.0;
		int mp = -1;
		for (int j=0; j<n; j++)
			//if (!used[j] && lastupdate[j]!=round)
			{
				double tmp = dp[j];
				//printf("%d %d %Lg %Lg %Lg\n",round,j, self[j],dp[j], tmp);
				if (tmp >max)
				{
					max = tmp;
					mp = j;
				}
			}
		return mp;
		//fprintf(out, "%ld %ld\n", mp, dd[mp]);


}

//int SPT_new::GetMax0(int round)
//{
//		double max = -1000000.0;
//		int mp = -1;
//		//for (int j=0; j<n; j++)
//		//	if (!used[j] && lastupdate[j]!=round)
//		//	{
//		//		double tmp = pow(1-1.0/dd[j],count[j])*(1+dp[j]);
//		//		if (tmp >max)
//		//		{
//		//			max = tmp;
//		//			mp = j;
//		//		}
//		//	}
//		return mp;
//		//fprintf(out, "%ld %ld\n", mp, dd[mp]);
//
//
//}

//int SPT_new::generateSPT_newfrom(int round, int node){
//	for (int i=0;i<n;i++) S[i]=n;
//	for (int i=0;i<n;i++) distance[i]=longest;
//	int top=0, bottom=0;
//	distance[node]=0;
//	heap[0]=node;
//	//S[node]=-1;
//	top++;
//	//for (int i=0;i<Graph::GetNeighbor(node);i++){
//	//	Edge e=Graph::GetEdge(node,i);
//	//	if (used[e.v]) continue;
//	//	distance[e.v]=e.w1;
//	//	//if (e.w2>=longest) continue;
//	//	heap[top]=e.v;
//	//	int j=top++, x=(j-1)/2;
//	//	double temp=distance[heap[j]];
//	//	while (j>0) {
//	//		if (distance[heap[x]]>temp){
//	//			heap[j]=heap[x];
//	//			S[heap[j]]=j;
//	//			j=x;
//	//			x=(j-1)/2;
//	//		}
//	//		else break;
//	//	}
//	//	heap[j]=e.v;
//	//	S[e.v]=j;
//	//	//if (heap[j]==1541) printf("%d %d %d\n",e.u,e.v, i);
//	//}
//	//S[node]=-1;
//	while (true){
//		//pop out of heap
//		//for (int i=0;i<top;i++){
//			//if (heap[i]==1541) printf("%d %d\n",i,top);
//		//}
//		//printf("\n");
//		//printf("%d %d %Lg %Lg\n",node, bottom, distance[heap[0]], longest);
//		if (distance[heap[0]]<longest) S[heap[0]]=-1; 
//		else break;
//		childlist[bottom++]=heap[0];
//		for (int i=0;i<Graph::GetNeighbor(heap[0]);i++){
//			Edge e=Graph::GetEdge(heap[0],i);
//			if (used[e.v] || S[e.v]<0) continue;
//			//if (node==3311 && e.v==19205) {
//			//	//printf("lastupdate[e.v]=%d\n",lastupdate[e.v]);
//			//	//printf("valid=%d, S=%d\n",validlist[lastupdate[e.v]][node],S[e.v]);
//			//	printf("dist=%.10lg newdist=%.10lg w1=%.10lg\n",distance[e.v],distance[heap[0]]+e.w1,e.w1);
//			//}
//				if (distance[e.v]>distance[heap[0]]+e.w1+EPS) {
//				if (S[e.v]>=n){
//					distance[e.v]=distance[heap[0]]+e.w1;
//					heap[top]=e.v;
//					int j=top++, x=(j-1)/2;
//					double temp=distance[heap[j]];
//					while (j>0) {
//						if (distance[heap[x]]>temp){
//							heap[j]=heap[x];
//							S[heap[j]]=j;
//							j=x;
//							x=(j-1)/2;
//						}
//						else break;
//					}
//					heap[j]=e.v;
//					S[e.v]=j;
//					//if (e.v==1541) printf("%d, %d %d\n",bottom,top, j);
//				}
//				else{
//					distance[e.v]=distance[heap[0]]+e.w1;
//					int j=S[e.v], x=(j-1)/2;
//					double temp=distance[heap[j]];
//					while (j>0) {
//						if (distance[heap[x]]>temp){
//							heap[j]=heap[x];
//							S[heap[j]]=j;
//							j=x;
//							x=(j-1)/2;
//						}
//						else break;
//					}
//					heap[j]=e.v;
//					S[e.v]=j;
//					//if (e.v==1541) printf("%d, %d %d\n",bottom,top, j);
//				}
//			}//endif
//			
//		}// end for
//		heap[0]=heap[--top];
//		if (!top) break;
//		//siftdown
//		int j=0, x=j*2+1;
//		double temp=distance[heap[j]];
//		while (x<top){
//			if (x+1<top && distance[heap[x+1]]<distance[heap[x]]) x++;
//			if (distance[heap[x]]<temp){
//				heap[j]=heap[x];
//				S[heap[j]]=j;
//				j=x; x=j*2+1;
//			}
//			else break;
//		}
//		//if (heap[top]==1541) printf("%d, %d %d\n",bottom,top, j);
//		heap[j]=heap[top];
//		S[heap[j]]=j;
//	}
//	//update tree node set and heuristic
//	validlist[round]=new bool[n];
//	memset(validlist[round],false,n);
//	//printf("%d\n",bottom);
//	for (int i=0;i<bottom;i++){
//		int child=childlist[i];
//		oldchildlist[i]=child;
//		if (dd[child]>0) {
//			for (int j=0;j<dd[child];j++) dp[children[child][j]]-=delta[child][j]*(1-self[child][j]);
//			//self[child]*=1-exp(-distance[child]);
//			//delete[] children[child];
//			//delete[] dist[child];
//			//dd[child]=0;
//
//			//block some nodes in child's inverse tree
//			for (int j=0;j<round;j++) {
//				//printf("round=%d %d\n",j, list[j]);
//				if (validlist[j][child]) {
//					bool invalid=false;
//					int k;
//					for (k=0;k<dd[child] && children[child][k]!=list[j];k++) ;
//					if (k==dd[child]) {
//						//printf("%d %d %d \n", list[j], child, dd[child]);
//						continue;
//					}
//
//					for (;k && children[child][k]!=node;k=path[child][k]) {
//						//if (list[j]==4840) printf("%d %d %d\n",children[child][k],k, path[child][k]);
//					}
//					//printf("%d\n",k);
//					validlist[j][child]=!k; //k==0 means ok
//				}
//			}
//			validlist[round][child]=true;
//			//if (node==4840 && child==6034) printf("child=%d\n",child);
//		}
//		//printf("\n");
//	}
//	for (int i=1;i<bottom;i++) 			generateSPT_newto(oldchildlist[i]);
//	return bottom;
//}
//
//int SPT_new::generateSPT_newto(int node){
//	vector<int> numchild(n,0), queue(n);
//	for (int i=0;i<n;i++) S[i]=n;
//	for (int i=0;i<n;i++) distance[i]=longest;
//	for (int i=0;i<n;i++) parent[i]=-1;
//	int top=0, bottom=0;
//	if (used[node]) {
//		dd[node]=1;
//		path[node][0]=0;
//		self[node][0]=1;
//		delta[node][0]=0;
//		return 1;
//	}
//	distance[node]=0;
//	heap[0]=node;
//	top++;
//	//for (int i=0;i<Graph::GetNeighbor(node);i++){
//	//	Edge e=Graph::GetEdge(node,i);
//	//	if (used[e.v] && !validlist[lastupdate[e.v]][node]) continue;
//	//	distance[e.v]=e.w2;
//	//	//if (e.w2>=longest) continue;
//	//	heap[top]=e.v;
//	//	int j=top++, x=(j-1)/2;
//	//	double temp=distance[heap[j]];
//	//	while (j>0) {
//	//		if (distance[heap[x]]>temp){
//	//			heap[j]=heap[x];
//	//			S[heap[j]]=j;
//	//			j=x;
//	//			x=(j-1)/2;
//	//		}
//	//		else break;
//	//	}
//	//	heap[j]=e.v;
//	//	S[heap[j]]=j;
//	//	parent[e.v]=node;
//	//	numchild[node]++;
//	//	b[e.v]=e.w2;
//	//}
//	//S[node]=-1;
//	parent[node]=node;
//	b[node]=1;
//	while (true){
//		//stack out of heap
//		if (distance[heap[0]]<longest) S[heap[0]]=-bottom-1; 
//		else break;
//		childlist[bottom++]=heap[0];
//		if (parent[heap[0]]!=heap[0]) numchild[parent[heap[0]]]++;
//		if (!used[heap[0]])
//		for (int i=0;i<Graph::GetNeighbor(heap[0]);i++){
//			Edge e=Graph::GetEdge(heap[0],i);
//			//if (node==19205 && e.v==3311) {
//			//	//printf("lastupdate[e.v]=%d\n",lastupdate[e.v]);
//			//	//printf("valid=%d, S=%d\n",validlist[lastupdate[e.v]][node],S[e.v]);
//			//	printf("dist=%lg newdistance=%lg w2=%lg\n",distance[e.v],distance[heap[0]]+e.w2,e.w2);
//			//}
//			if (used[e.v] && !validlist[lastupdate[e.v]][node] || S[e.v]<0) continue;
//			if (distance[e.v]>distance[heap[0]]+e.w2+EPS) {
//				//if (parent[e.v]>=0) numchild[parent[e.v]]--;
//				parent[e.v]=heap[0];
//				b[e.v]=exp(-e.w2);
//				if (S[e.v]>=n){
//					distance[e.v]=distance[heap[0]]+e.w2;
//					heap[top]=e.v;
//					int j=top++, x=(j-1)/2;
//					double temp=distance[heap[j]];
//					while (j>0) {
//						if (distance[heap[x]]>temp){
//							heap[j]=heap[x];
//							S[heap[j]]=j;
//							j=x;
//							x=(j-1)/2;
//						}
//						else break;
//					}
//					heap[j]=e.v;
//					S[heap[j]]=j;
//				}
//				else{
//					distance[e.v]=distance[heap[0]]+e.w2;
//					int j=S[e.v], x=(j-1)/2;
//					double temp=distance[heap[j]];
//					while (j>0) {
//						if (distance[heap[x]]>temp){
//							heap[j]=heap[x];
//							S[heap[j]]=j;
//							j=x;
//							x=(j-1)/2;
//						}
//						else break;
//					}
//					heap[j]=e.v;
//					S[e.v]=j;
//				}
//			}//endif
//			
//		}// end for
//		heap[0]=heap[--top];
//		if (!top) break;
//		//siftdown
//		int j=0, x=j*2+1;
//		double temp=distance[heap[j]];
//		while (x<top){
//			if (x+1<top && distance[heap[x+1]]<distance[heap[x]]) x++;
//			if (distance[heap[x]]<temp){
//				heap[j]=heap[x];
//				S[heap[j]]=j;
//				j=x; x=j*2+1;
//			}
//			else break;
//		}
//		heap[j]=heap[top];
//		S[heap[j]]=j;
//	}
//	//update tree node set and heuristic
//	if (!dd[node]){
//		//printf("about to new %d %d\n",node, bottom);
//		children[node]=new int[bottom];
//		delta[node]=new double[bottom];
//		self[node]=new double[bottom];
//		path[node]=new int[bottom];
//		//printf("finish new %d %d\n",node, bottom);
//	}
//	//else if (dd[node]<bottom) printf("dd[%d]<%d\n", node, bottom);
//	dd[node]=bottom;
//	//if (node==4840) printf("childnum %d\n", numchild[childlist[0]]);
//	int head=0, tail=0;
//	for (int i=0;i<bottom;i++){
//		children[node][i]=childlist[i];
//		//printf("%d\t",numchild[childlist[i]]);
//		if (numchild[childlist[i]])	self[node][i]=1;
//		else {
//			self[node][i]=used[childlist[i]]?1:0;
//			queue[tail++]=i;
//		}
//		path[node][i]=-S[parent[childlist[i]]]-1;
//		//if (node==4840) printf("path %d %d\n",i,path[node][i]);
//		//delta[node][i]=distance[childlist[i]];
//
//		//printf("%d,%Lg\n",list[i],dp[list[i]]);
//	}
//	//if (bottom==1) printf("head %d tail %d path %d S %d\n", head, tail,path[node][0], S[parent[node]]);
//	int x,u;
//	while (head<tail) {
//		x=queue[head++];
//		u=path[node][x];
//		self[node][u]*=(1-self[node][x]*b[childlist[x]]);
//		if (!--numchild[childlist[u]]) {
//			self[node][u]=1-self[node][u];
//			queue[tail++]=u;
//			//printf("%d\t",u);
//		}		
//	}
//	//if (bottom==1) printf("head %d tail %d\n", head, tail);
//	if (x) printf("x!=0 %d\n",node);
//	delta[node][queue[--head]]=1;
//	dp[node]+=1-self[node][x];
//	for (head--;head>=0;head--) {
//		x=queue[head], u=path[node][x];
//		delta[node][x]=(1-self[node][u])/(1-self[node][x]*b[childlist[x]])*b[childlist[x]]*delta[node][u];
//		dp[childlist[x]]+=delta[node][x]*(1-self[node][x]);
//		//if (delta[node][x]*(1-self[node][x])>1) printf(">1 %d\n", node);
//	}
//	return bottom;
//}


double pagerank::Build(int num, char data[], double dampen)
{
	//LARGE_INTEGER start, end, freq;
	//	QueryPerformanceFrequency(&freq);
	//QueryPerformanceCounter(&start);
	n = Graph::GetN();
	//longest=log(double(bound));
	top = num;
	//double treesize=0;
	//S = new int[n];
	//distance = new double[n];
	//b = new double[n];
	//heap = new int[n];
	//childlist = new int[n];
	//oldchildlist = new int[n];
	//parent = new int[n];

	//used.resize(n);
	//lastupdate.resize(n);
	//children.resize(n);
	dp.resize(n);
	//self.resize(n);
	dd.resize(n);
	//delta.resize(n);
	//path.resize(n);
	//memset(count, 0, sizeof(int)*MAX_NODE);
	vector<double> newdp(n,0);
	vector<double> self(n,0.0);
	int set[SET_SIZE];

	//double old = 0.0;

	//double improve[MAX_NODE];
	//int heap[MAX_NODE];
	int i=0;
	for (i=0; i<n; i++)
	{
	//	heap[i] = i;
		//lastupdate[i] = -1;
		//children[i]=NULL;
		dp[i]=1.0;
		dd[i]=Graph::GetNeighbor(i);
		for (int j=0;j<dd[i];j++)
			self[i]+=exp(-Graph::GetEdge(i,j).w2);
		
	//	improve[i] = (double)(n+1);
	}
	//for (i=0; i<n; i++)
	//	dd[i] = 0;

	//generateSPT_newto(256042);

	//for (i=0;i<n;i++)
	//{
	//	treesize+=generateSPT_newto(i);
	//	//printf("i=%d\n",i);
	//	//dp[i]/=dd[i];
	//}


	//for (int i=0; i<top; i++)
	//{
	//	int ccc = 0;
	//	while (lastupdate[heap[0]] != i)
	//	{ 
	//		//printf("%d %d %d\n", i, heap[0], ccc);
	//		ccc++;
	//		lastupdate[heap[0]] = i;
	//		set[i] = heap[0];
	//		//printf("SPT_newIC_SPM %d %d\n",heap[0],improve[heap[0]]);
	//		improve[heap[0]] = Run(NUM_ITER, i+1, set) - old;
	//		
			//char tmpfilename[200];
			//sprintf(tmpfilename, "tmp/top%d.txt", k);
			//FILE *tmpfile = fopen(tmpfilename,"w");

	//		int x = 0;
	//		while (x*2+2<=n-i)
	//		{
	//			int newx=x*2+1;
	//			if ((newx+1<n-i) && (improve[heap[newx]]<improve[heap[newx+1]]))
	//				newx++;
	//			if (improve[heap[x]]<improve[heap[newx]])
	//			{
	//				int t=heap[x];
	//				heap[x] = heap[newx];
	//				heap[newx] = t;
	//				x = newx;
	//			}
	//			else
	//				break;
	//		}
	//	}
	double theta=1e-3;				
	double delta;
	long count=0;
	do
	{
		for (i=0;i<n;i++)
			newdp[i]=0;
		for (i=0;i<n;i++)
			for (int j=0;j<dd[i];j++)
			{
				Edge e=Graph::GetEdge(i,j);
				newdp[e.v]+=dp[i]*exp(-e.w2)/self[i];
			}
		delta=0;
		for (i=0;i<n;i++)
		{
			delta+=fabs(dampen+(1-dampen)*newdp[i]-dp[i]);
			dp[i]=dampen+(1-dampen)*newdp[i];
		}
		//printf("%lg\n",delta);
		
	} while (delta>theta &&++count<10000);

	i=0;
	double max = -1000000.0;
	int mp;
	//for (int j=0;j<k;j++)
	//{
	//	int x=GetMax(i);
	//	set[i] = x;
	//	lastupdate[x] = i;			
	//	//double improve = RunFast(NUM_ITER, i+1, set);
	//	double improve=dp[x];
	//	//fprintf(tmpfile, "%d %d %Lg\n",i,x,improve); 
	//	if (improve > max) {
	//		max=improve;
	//		mp=x;
	//	}
	//}
	//used[mp] = true;
	//set[i] = mp;
	//list[i] = mp;
	//d[i] = max;
	//old+=d[i];
	////printf("%d %d %Lg\n",i,mp,max);
	//generateSPT_newfrom(i, mp);
	////printf("step 1 ok\n");
	////for (int j=0; j<Graph::GetNeighbor(mp); j++)
	////{
	////	Edge e = Graph::GetEdge(mp, j);
	////	count[e.v]+=e.c;
	////	dp[e.v]-=1-pow(1-1.0/dd[mp],e.c);
	////}
	//	QueryPerformanceCounter(&end);
	//double	timer = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
	//	printf("%lg ", timer);

	for (i=0; i<top; i++)
	{
		max = -1000000.0;
		//for (int j=0;j<k;j++){
			int x=GetMax(i);
			set[i] = x;
			//lastupdate[x] = i;			
			//double improve = i>top? Run(NUM_ITER/100, i+1, set) - old : RunFast(NUM_ITER/100, i+1, set) - old;
			double improve=dp[x];
			//fprintf(tmpfile, "%d %d %Lg\n",i,x,improve); 
			if (improve > max) {
				max=improve;
				mp=x;
			}
		//}
		dp[mp] = 0;
		set[i] = mp;
		list[i] = mp;
		d[i] = max;
		//old+=d[i];
		//printf("before %d step 2 ok %d\n",i,mp);
		//generateSPT_newfrom(i, mp);
		//printf("after %d step 2 ok %d\n",i,mp);
		//for (int j=0; j<Graph::GetNeighbor(mp); j++)
		//{
		//	Edge e = Graph::GetEdge(mp, j);
		//	count[e.v]+=e.c;
		//	dp[e.v]-=1-pow(1-1.0/dd[mp],e.c);
		//}
		// update trees.
	}
			//fclose(tmpfile);

		//char bakname[200];
		//sprintf(bakname, "SPT_newchoice%02d.txt", i+1);
		//FILE *bak = fopen(bakname, "w");
		//fprintf(bak, "%6d\t%d\t%lg\n", i+1, heap[0], improve[heap[0]]);
		//fclose(bak);
		//printf("%d\t%lg\n", i+1, improve[131]);

	//	heap[0] = heap[n-i-1];
	//	int x = 0;
	//	while (x*2+2<=n-i)
	//	{
	//		int newx=x*2+1;
	//		if ((newx+1<n-i) && (improve[heap[newx]]<improve[heap[newx+1]]))
	//			newx++;
	//		if (improve[heap[x]]<improve[heap[newx]])
	//		{
	//			int t=heap[x];
	//			heap[x] = heap[newx];
	//			heap[newx] = t;
	//			x = newx;
	//		}
	//		else
	//			break;
	//	}
	//}
	//delete[] childlist;
	//delete[] oldchildlist;
	//delete[] distance;
	//delete[] S;
	//delete[] heap;
	//delete[] b;
	//delete[] parent;

	//for (i=0;i<n;i++)
	//	if (dd[i]) {
	//		delete[] children[i];
	//		delete[] delta[i];
	//		delete[] self[i];
	//		delete[] path[i];
	//		dd[i]=0;
	//	}
	//for (i=0;i<top;i++)
	//	delete[] validlist[i];

	sprintf_s(file,"PAGERANK_%s", data);
	FILE *out;
	fopen_s(&out, file, "w");
	fprintf(out, "%d\n", top);
	for (i=0; i<top; i++)
		fprintf(out, "%d\t%Lg\n", list[i], d[i]);
	fclose(out);
	return 1;
}

//double SPT_new::Build(int num, int k0, int bound, double (*Run)(int num_iter, int size, int set[]), double (*RunFast)(int num_iter, int size, int set[]))
//{
//	n = Graph::GetN();
//	longest=log(double(bound));
//	k=k0;
//	top = num;
//	double treesize=0;
//	S = new int[n];
//	distance = new double[n];
//	b = new double[n];
//	heap = new int[n];
//	childlist = new int[n];
//	oldchildlist = new int[n];
//	parent = new int[n];
//
//	used.resize(n);
//	lastupdate.resize(n);
//	children.resize(n);
//	dp.resize(n);
//	self.resize(n);
//	dd.resize(n);
//	//memset(used, 0, sizeof(bool)*MAX_NODE);
//	//memset(count, 0, sizeof(int)*MAX_NODE);
//	int set[SET_SIZE];
//
//	double old = 0.0;
//
//	//double improve[MAX_NODE];
//	//int heap[MAX_NODE];
//	int i=0;
//	for (i=0; i<n; i++)
//	{
//	//	heap[i] = i;
//		lastupdate[i] = -1;
//		children[i]=NULL;
//		dp[i]=0.0;
//		self[i]=NULL;
//	//	improve[i] = (double)(n+1);
//	}
//	for (i=0; i<n; i++)
//		dd[i] = 0;
//	for (i=0;i<n;i++)
//	{
//		//printf("step 0 %d ok\n",i);
//		treesize+=generateSPT_newto(i);
//		//dp[i]/=dd[i];
//	}
//
//
//	//for (int i=0; i<top; i++)
//	//{
//	//	int ccc = 0;
//	//	while (lastupdate[heap[0]] != i)
//	//	{ 
//	//		//printf("%d %d %d\n", i, heap[0], ccc);
//	//		ccc++;
//	//		lastupdate[heap[0]] = i;
//	//		set[i] = heap[0];
//	//		//printf("SPT_newIC_SPM %d %d\n",heap[0],improve[heap[0]]);
//	//		improve[heap[0]] = Run(NUM_ITER, i+1, set) - old;
//	//		
//			//char tmpfilename[200];
//			//sprintf(tmpfilename, "tmp/top%d.txt", k);
//			//FILE *tmpfile = fopen(tmpfilename,"w");
//
//	//		int x = 0;
//	//		while (x*2+2<=n-i)
//	//		{
//	//			int newx=x*2+1;
//	//			if ((newx+1<n-i) && (improve[heap[newx]]<improve[heap[newx+1]]))
//	//				newx++;
//	//			if (improve[heap[x]]<improve[heap[newx]])
//	//			{
//	//				int t=heap[x];
//	//				heap[x] = heap[newx];
//	//				heap[newx] = t;
//	//				x = newx;
//	//			}
//	//			else
//	//				break;
//	//		}
//	//	}
//	double max = -1000000.0;
//	int mp;
//	for (int j=0;j<k;j++){
//		int x=GetMax(i);
//		set[i] = x;
//		lastupdate[x] = i;			
//		double improve = RunFast(NUM_ITER, i+1, set);
//		//double improve=dp[x];
//		//fprintf(tmpfile, "%d %d %Lg\n",i,x,improve); 
//		if (improve > max) {
//			max=improve;
//			mp=x;
//		}
//	}
//	used[mp] = true;
//	set[i] = mp;
//	list[i] = mp;
//	d[i] = max;
//	old+=d[i];
//	//printf("%d %d %Lg\n",i,mp,max);
//	generateSPT_newfrom(i, mp);
//	//printf("step 1 ok\n");
//	//for (int j=0; j<Graph::GetNeighbor(mp); j++)
//	//{
//	//	Edge e = Graph::GetEdge(mp, j);
//	//	count[e.v]+=e.c;
//	//	dp[e.v]-=1-pow(1-1.0/dd[mp],e.c);
//	//}
//
//	for (i=1; i<top; i++)
//	{
//		max = -1000000.0;
//		for (int j=0;j<k;j++){
//			int x=GetMax(i);
//			set[i] = x;
//			lastupdate[x] = i;			
//			double improve = i>top? Run(NUM_ITER/100, i+1, set) - old : RunFast(NUM_ITER/100, i+1, set) - old;
//			//double improve=dp[x];
//			//fprintf(tmpfile, "%d %d %Lg\n",i,x,improve); 
//			if (improve > max) {
//				max=improve;
//				mp=x;
//			}
//		}
//		used[mp] = true;
//		set[i] = mp;
//		list[i] = mp;
//		d[i] = max;
//		old+=d[i];
//		//printf("before %d step 2 ok\n",i);
//		generateSPT_newfrom(i, mp);
//		//for (int j=0; j<Graph::GetNeighbor(mp); j++)
//		//{
//		//	Edge e = Graph::GetEdge(mp, j);
//		//	count[e.v]+=e.c;
//		//	dp[e.v]-=1-pow(1-1.0/dd[mp],e.c);
//		//}
//		// update trees.
//	}
//			//fclose(tmpfile);
//
//		//char bakname[200];
//		//sprintf(bakname, "SPT_newchoice%02d.txt", i+1);
//		//FILE *bak = fopen(bakname, "w");
//		//fprintf(bak, "%6d\t%d\t%lg\n", i+1, heap[0], improve[heap[0]]);
//		//fclose(bak);
//		//printf("%d\t%lg\n", i+1, improve[131]);
//
//	//	heap[0] = heap[n-i-1];
//	//	int x = 0;
//	//	while (x*2+2<=n-i)
//	//	{
//	//		int newx=x*2+1;
//	//		if ((newx+1<n-i) && (improve[heap[newx]]<improve[heap[newx+1]]))
//	//			newx++;
//	//		if (improve[heap[x]]<improve[heap[newx]])
//	//		{
//	//			int t=heap[x];
//	//			heap[x] = heap[newx];
//	//			heap[newx] = t;
//	//			x = newx;
//	//		}
//	//		else
//	//			break;
//	//	}
//	//}
//	//printf("about to delete\n");
//	delete[] childlist;
//	delete[] oldchildlist;
//	delete[] distance;
//	delete[] S;
//	delete[] heap;
//	delete[] b;
//	delete[] parent;
//	//printf("about to delete dd\n");
//
//	for (i=0;i<n;i++)
//		if (dd[i]) {
//			//printf("about to delete dd[%d]\n",i);
//			delete[] children[i];
//			delete[] delta[i];
//			delete[] self[i];
//			delete[] path[i];
//		}
//	for (i=0;i<top;i++)
//		delete[] validlist[i];
//
//	sprintf_s(file,"SPT_new_%04d.txt", bound);
//	FILE *out;
//	fopen_s(&out, file, "w");
//	fprintf(out, "%d\n", top);
//	for (i=0; i<top; i++)
//		fprintf(out, "%d\t%Lg\n", list[i], d[i]);
//	fclose(out);
//	return treesize/n;
//}

void pagerank::BuildFromFile()
{
	n = Graph::GetN();
	//sprintf_s(file,"SPT_new_%04d.txt", bound);
	FILE* in;
	fopen_s(&in, file, "r");
	fscanf_s(in, "%ld", &top);
	for (int i=0; i<top; i++)
		fscanf_s(in, "%ld %Lg", &list[i], &d[i]);
	fclose(in);
}

int  pagerank::GetNode(int i)
{
	if (i<0)
		return -1;
	if (i>=top) 
		return -1;
	return list[i];
}


//char* pagerank::filename()
//{
//	sprintf_s(file,"SPT_new_%04d.txt", bound);
//	return file;
