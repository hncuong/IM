#define HEAD_INFO
//#define HEAD_TRACE
#include "sfmt/SFMT.h"
#include "head.h"

#include "MeasureM.h"
#include "memoryusage.h"

using namespace std;
typedef double (*pf)(int, int);
void handle_error(const char* msg);


class Graph
{
public:
    int n, m, k;
    vector<int> inDeg;
    vector<vector<int>> gT, g;

    vector<vector<double>> probT, prob;

    enum InfluModel {IC, LT, WC};
    InfluModel influModel;
    void setInfuModel(InfluModel p)
    {
        influModel = p;
        TRACE(influModel == IC);
        TRACE(influModel == LT);
        TRACE(influModel == WC);
    }

    string folder;
    string graph_file;
    void readNM()
    {
        ifstream cin((folder + "attribute.txt").c_str());
        ASSERT(!cin == false);
        string s;
        while (cin >> s)
        {
            if (s.substr(0, 2) == "n=")
            {
                n = atoi(s.substr(2).c_str());
                continue;
            }
            if (s.substr(0, 2) == "m=")
            {
                m = atoi(s.substr(2).c_str());
                continue;
            }
            ASSERT(false);
        }
        TRACE(n, m );
        cin.close();
    }
    void add_edge(int a, int b, double p)
    {
        probT[b].push_back(p);
        prob[a].push_back(p);

        gT[b].push_back(a);
        g[a].push_back(b);
        inDeg[b]++;
    }

    vector<bool> hasnode;
    void readGraph()
    {
        //FILE *fin = fopen((graph_file).c_str(), "rb");
		size_t length;
		int fd = open((graph_file).c_str(), O_RDWR);
		if (fd == -1)
			handle_error("open");
		struct stat sb;
		int rc = fstat(fd, &sb);
		if (rc == -1)
			handle_error("fstat");

		length = sb.st_size;
		auto ptr = static_cast<char*>(mmap(NULL, length, PROT_READ, MAP_PRIVATE, fd, 0u));  //byte by byte
		auto f = ptr;

		int gap = 2 * sizeof(int) + sizeof(double);
        //ASSERT(fin != false);
        int readCnt = 0;
        for (int i = 0; i < m; i++)
        {
            readCnt ++;
            int a, b;
            double p;
            //int c = fscanf(fin, "%d%d%lf", &a, &b, &p);
			memcpy(&a, f, sizeof(int));
			memcpy(&b, f + sizeof(int), sizeof(int));
			memcpy(&p, f + 2 * sizeof(int), sizeof(double));
			f += gap;
            //ASSERTT(c == 3, a, b, p, c);

            //TRACE_LINE(a, b);
            ASSERT( a < n );
            ASSERT( b < n );
            hasnode[a] = true;
            hasnode[b] = true;
            //cout<<"p="<<p<<endl;
            //p=0.1;
            //cout<<"p="<<p<<endl;
            add_edge(a, b, p);
        }
        TRACE_LINE_END();
        int s = 0;
        for (int i = 0; i < n; i++)
            if (hasnode[i])
                s++;
        // INFO(s);
        // cout<<"Read Graph Memory: "<<getProcMemory()<<" MB"<<endl;
        // disp_mem_usage();
        // cout<<endl;

        ASSERT(readCnt == m);
		rc = munmap(ptr, length);
		close(fd);
        //fclose(fin);
    }
#ifdef DISCRETE
    void readGraphBin()
    {
        string graph_file_bin = graph_file.substr(0, graph_file.size() - 3) + "bin";
        INFO(graph_file_bin);
        FILE *fin = fopen(graph_file_bin.c_str(), "rb");
        //fread(fin);
        struct stat filestatus;
        stat( graph_file_bin.c_str(), &filestatus );
        int64 sz = filestatus.st_size;
        char *buf = new char[sz];
        int64 sz2 = fread(buf, 1, sz, fin);
        INFO("fread finish", sz, sz2);
        ASSERT(sz == sz2);
        for (int64 i = 0; i < sz / 12; i++)
        {
            int a = ((int *)buf)[i * 3 + 0];
            int b = ((int *)buf)[i * 3 + 1];
            float p = ((float *)buf)[i * 3 + 2];
            //INFO(a,b,p);
            add_edge(a, b, p);
        }
        delete []buf;
        fclose(fin);
    }
#endif
    Graph(string folder, string graph_file): folder(folder), graph_file(graph_file)
    {
        readNM();

        //init vector
        FOR(i, n)
        {
            gT.push_back(vector<int>());
            g.push_back(vector<int>());
            hasnode.push_back(false);

            probT.push_back(vector<double>());
            prob.push_back(vector<double>());
            //hyperGT.push_back(vector<int>());
            inDeg.push_back(0);
        }
        readGraph();
        //system("sleep 10000");
    }

};
double sqr(double t)
{
    return t * t;
}

void handle_error(const char* msg) {
	perror(msg);
	exit(255);
}

