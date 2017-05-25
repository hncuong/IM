#include <sys/resource.h>
#include <string>

using namespace std;

unsigned int getProcMemory(){
	struct rusage r_usage;
	getrusage(RUSAGE_SELF, &r_usage);
	//string strMemUsage = to_string(r_usage.ru_maxrss);
	return r_usage.ru_maxrss / 1024.0 ;
	//return strMemUsage;
}
