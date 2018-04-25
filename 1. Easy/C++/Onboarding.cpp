/*~~~~~~~~~~~~~~~~~~*
 *                  *
 * $Dollar Akshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.codingame.com/ide/puzzle/onboarding

#include <algorithm>
#include <assert.h>
#include <ctype.h>
#include <iostream>
#include <math.h>
#include <queue>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <vector>

using namespace std;

#define sp system("pause")
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define FORD(i, a, b) for (int i = a; i >= b; --i)
#define REP(i, n) FOR(i, 0, (int)n - 1)
#define MS0(x) memset(x, 0, sizeof(x))
#define MS1(x) memset(x, 1, sizeof(x))
#define SORT(a, n) sort(begin(a), begin(a) + n)
#define REV(a, n) reverse(begin(a), begin(a) + n)
#define ll long long
#define MOD 1000000007
#define gc getchar_unlocked

struct enemy {
	char name[100];
	int dist;
};

int main() {
	enemy e[10];
	while (1) {
		scanf("%s %d", &e[0].name, &e[0].dist);
		scanf("%s %d", &e[1].name, &e[1].dist);
		puts(e[0].dist < e[1].dist ? e[0].name : e[1].name);
	}
	return 0;
}

//