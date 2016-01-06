/*~~~~~~~~~~~~~~~~~~*
 *                  *
 * $Dollar Akshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//

#include <math.h>
#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

#define sp system("pause")
#define FOR(i,a,b) for(int i=a;i<=b;++i)
#define FORD(i,a,b) for(int i=a;i>=b;--i)
#define REP(i,n) FOR(i,0,(int)n-1)
#define pb(x) push_back(x)
#define mp(a,b) make_pair(a,b)
#define DB(format,...) fprintf(stderr,format, ##__VA_ARGS__)
#define MS(x,n) memset(x,n,sizeof(x))
#define SORT(a,n) sort(begin(a),begin(a)+n)
#define REV(a,n) reverse(begin(a),begin(a)+n)
#define ll long long
#define pii pair<int,int>
#define MOD 1000000007

char s[1000][1000];

int main(){

	int w, h;
	scanf("%d%d", &w, &h);
	DB("%d %d\n", w, h);
	REP(i, h) {
		scanf("%s", s[i]);
		DB("%s\n", s[i]);
	}
	int y = h-1, x = 0;
	while (true) {

		if (y<h-1 && s[y+1][x]=='.')
			y++;
		else if (s[y][x+1]=='.')
			x++;
		else if (y>0 && x<w-1 && s[y-1][x+1]=='.') {
			y--;
			x++;
		}
		else
			break;
	}
	if (x == w-1)
		printf("SUCCESS\n");
	else
		printf("%d %d\n", x, h-y-1);
	sp;
	return 0;
}

//Solved