/*~~~~~~~~~~~~~~~~~~*
*                  *
*  $DollarAkshay$  *
*                  *
*~~~~~~~~~~~~~~~~~~*/

//https://www.codingame.com/ide/puzzle/dwarfs-standing-on-the-shoulders-of-giants

#include <algorithm>
#include <assert.h>
#include <ctype.h>
#include <deque>
#include <iostream>
#include <map>
#include <math.h>
#include <queue>
#include <set>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <time.h>
#include <vector>

using namespace std;

#define sp system("pause")
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define FORD(i, a, b) for (int i = a; i >= b; --i)
#define REP(i, n) FOR(i, 0, (int)n - 1)
#define pb(x) push_back(x)
#define mp(a, b) make_pair(a, b)
#define MSX(a, x) memset(a, x, sizeof(a))
#define SORT(a, n) sort(begin(a), begin(a) + n)
#define ll long long
#define pii pair<int, int>
#define MOD 1000000007

int indeg[10000];
int outdeg[10000];
bool v[10000];
vector<int> graph[10000];

int DFS(int s) {
	v[s] = true;

	int res = 1;
	REP(i, graph[s].size()) {
		int childLen = DFS(graph[s][i]) + 1;
		res = max(res, childLen);
	}

	v[s] = false;
	return res;
}

int main() {

	int n;
	scanf("%d", &n);
	REP(i, n) {
		int u, v;
		scanf("%d %d", &u, &v);
		outdeg[u]++;
		indeg[v]++;
		graph[u].pb(v);
	}

	vector<int> roots;
	REP(i, 10000) {
		if (outdeg[i] > 0 && indeg[i] == 0) {
			roots.pb(i);
		}
	}

	int longestPath = 0;
	REP(i, roots.size()) {
		int len = DFS(roots[i]);
		longestPath = max(longestPath, len);
	}

	printf("%d\n", longestPath);

	return 0;
}

//Solved