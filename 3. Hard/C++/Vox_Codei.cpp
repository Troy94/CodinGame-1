/*~~~~~~~~~~~~~~~~~~*
*                  *
* $Dollar Akshay$  *
*                  *
*~~~~~~~~~~~~~~~~~~*/

//https://www.codingame.com/ide/1603843fc7a55b88ed33d1af6bd178f3977c778

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

struct point {
	int x, y;
};

struct state {
	int r, b, n, bc;
	char board[19][20];
};

bool win = 0;
int w, h;
state original;

vector<string> action;
point dir[4] = { { 0, -1 },{ 1, 0 },{ 0, 1 },{ -1, 0 } };

void debug() {

	REP(i, action.size())
		DB("%s, ", action[i].c_str());
	DB("\n");

}

void burst(state &s, int i, int j) {

	s.bc--;
	s.board[i][j] = '.';
	REP(d, 4) {
		int dx = dir[d].x, dy = dir[d].y;
		FOR(k, 1, 3) {
			int px = j+dx*k, py = i+dy*k;
			if (px>=0 && px<w && py>=0 && py<h) {
				if (s.board[py][px]=='#')
					break;
				else if (s.board[py][px]=='@') {
					s.board[py][px] = '.';
					s.n--;
				}
				else if (s.board[py][px]>='0' && s.board[py][px]<='2')
					burst(s, py, px);
			}
			else
				break;
		}
	}
}

void simulateRound(state &s) {

	s.r--;
	REP(i, h) {
		REP(j, w) {
			if (s.board[i][j]=='0')
				s.board[i][j] = '1';
			else if (s.board[i][j]=='1')
				s.board[i][j] = '2';
			else if (s.board[i][j]=='2') {
				burst(s, i, j);
			}
		}
	}
}

bool redundant(state &s, int i, int j) {

	REP(d, 4) {
		int dx = dir[d].x, dy = dir[d].y;
		FOR(k, 1, 3) {
			int px = j+dx*k, py = i+dy*k;
			if (px>=0 && px<w && py>=0 && py<h) {
				if (s.board[py][px]=='#')
					break;
				else if (s.board[py][px]>='0' && s.board[py][px]<='2')
					return true;
			}
		}
	}
	return false;

}

bool feasible(state &s, int i, int j) {

	REP(d, 4) {
		int dx = dir[d].x, dy = dir[d].y;
		FOR(k, 1, 3) {
			int px = j+dx*k, py = i+dy*k;
			if (px>=0 && px<w && py>=0 && py<h) {
				if (s.board[py][px]=='#')
					break;
				else if (s.board[py][px]=='@' && !redundant(s, py, px))
					return true;
			}
		}
	}
	return false;
}

int bombcoverCount(state &s) {

	bool v[19][20];
	MS(v,0);

	int c = 0;
	REP(i, h) {
		REP(j, w) {
			if (s.board[i][j]>='0' && s.board[i][j]<='2') {
				REP(d, 4) {
					int dx = dir[d].x, dy = dir[d].y;
					FOR(k, 1, 3) {
						int px = j+dx*k, py = i+dy*k;
						if (px>=0 && px<w && py>=0 && py<h) {
							if (s.board[py][px]=='#')
								break;
							else if (s.board[py][px]=='@' && v[py][px]==false) {
								c++;
								v[py][px] = true;
							}
						}
					}
				}
			}
		}
	}
	return c;
}

bool deadstate(state &s) {

	if(bombcoverCount(s)+s.b*12>=s.n)
		return false;
	else 
		return true;
	
}

void DFS(state &s) {

	if (s.r<=0 || deadstate(s))
		return;

	state copy = s;
	simulateRound(s);

	if (s.n==0) {
		win = 1;
		return;
	}

	//Place a bomb
	if (s.b>0) {
		REP(i, h) {
			REP(j, w) {
				if (s.board[i][j]=='.' && feasible(s, i, j)) {
					action.push_back(to_string(j)+" "+ to_string(i));
					
					s.board[i][j] = '0';
					s.bc++;
					s.b--;
					DFS(s);
					if (win)
						return;
					s.board[i][j] = '.';
					action.pop_back();
					s.b++;
					s.bc--;
				}
			}
		}
	}

	//Wait
	if (s.bc) {
		action.push_back("WAIT");
		DFS(s);
		if (win)
			return;
		action.pop_back();
	}

	//Backtrack
	s = copy;
}

int main() {

	int n;
	scanf("%d%d", &w, &h);
	DB("%d %d\n", w, h);

	REP(i, h) {
		scanf("%s", original.board[i]);
		DB("%s\n", original.board[i]);
		REP(j, w) {
			if (original.board[i][j]=='@')
				original.n++;
		}
	}
	scanf("%d %d", &original.r, &original.b);
	DB("%d %d\n", original.r, original.b);
	original.bc = 0;
	clock_t t = clock();
	DFS(original);
	t = clock()-t;
	DB("Time Taken = %.3lf ms\n", (double)1000*t/CLOCKS_PER_SEC);

	REP(i, action.size()) {
		printf("%s\n", action[i].c_str());
	}

	while (1) {
		printf("WAIT\n");
	}

	return 0;
	sp;
}

//Partially Solved ~ Dailing ` testcase (93%)