#include <vector>

using namespace std;

class PrunedEstimater {
private:
	int n, n1;
	vector<int> weight, comp, sigmas;
	vector<int> pmoc;
	vector<int> at_p;

	vector<int> up;
	vector<bool> memo, removed;

	vector<int> es, rs;
	vector<int> at_e, at_r;

	vector<bool> visited;

	int hub;
	vector<bool> descendant, ancestor;
	bool flag;

	void first();
	int sigma(const int v);
	inline int unique_child(const int v);
public:
	void init(int n, vector<pair<int, int> > &es, vector<int> &comp);
	int sigma1(const int v);
	void add(int v);
	void update(vector<long long> &sums);
};

class InfluenceMaximizer {
private:
	int n, m; // |V|, |E|

	vector<int> es1, at_e;
	vector<int> rs1, at_r;

	int scc(vector<int> &comp);
public:
	vector<int> run(vector<pair<pair<int, int>, double> > &es, const int k,
			const int R);
};

// Random Number Generator
class Xorshift {
public:
	Xorshift(int seed) {
		x = _(seed, 0);
		y = _(x, 1);
		z = _(y, 2);
		w = _(z, 3);
	}

	int _(int s, int i) {
		return 1812433253 * (s ^ (s >> 30)) + i + 1;
	}

	inline int gen_int() {
		unsigned int t = x ^ (x << 11);
		x = y;
		y = z;
		z = w;
		return w = w ^ (w >> 19) ^ t ^ (t >> 8);
	}

	inline int gen_int(int n) {
		return (int) (n * gen_double());
	}

	inline double gen_double() {
		unsigned int a = ((unsigned int) gen_int()) >> 5, b =
				((unsigned int) gen_int()) >> 6;
		return (a * 67108864.0 + b) * (1.0 / (1LL << 53));
	}

private:
	unsigned int x, y, z, w;
};
