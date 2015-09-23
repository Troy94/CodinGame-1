/*~~~~~~~~~~~~~~~~~~*
 *                  *
 * $Dollar Akshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.codingame.com/ide/20849806b7352d6930a569807c9236343ad70bd

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

deque<int> p1, p2;
deque<int> pile1, pile2;

int battle() {

	if (p1.front()>p2.front()) {
		while (!pile1.empty()) {
			p1.push_back(pile1.front());
			pile1.pop_front();
		}
		p1.push_back(p1.front());
		while (!pile2.empty()) {
			p1.push_back(pile2.front());
			pile2.pop_front();
		}
		p1.push_back(p2.front());
		p1.pop_front();
		p2.pop_front();
		return 1;
	}
	else if (p2.front()>p1.front()) {
		while (!pile1.empty()) {
			p2.push_back(pile1.front());
			pile1.pop_front();
		}
		p2.push_back(p1.front());
		while (!pile2.empty()) {
			p2.push_back(pile2.front());
			pile2.pop_front();
		}
		p2.push_back(p2.front());
		p1.pop_front();
		p2.pop_front();
		return 1;
	}
	else {
		REP(i, 4) {
			if (p1.empty() || p2.empty())
				return -1;
			pile1.push_back(p1.front());
			pile2.push_back(p2.front());
			p1.pop_front();
			p2.pop_front();
		}
		return battle();
	}


}

void debugCards() {

	DB("Player 1 : ");
	REP(i, p1.size())
		DB("%d ", p1[i]);
	DB("\n");

	DB("Player 2 : ");
	REP(i, p2.size())
		DB("%d ", p2[i]);
	DB("\n\n");
}

int main(){

	int n;

	//Player 1 Cards
	scanf("%d", &n);
	REP(i, n) {
		char c[10];
		scanf("%s", c);
		c[strlen(c)-1] = 0;
		if (c[0]=='A')
			p1.push_back(14);
		else if (c[0]=='K')
			p1.push_back(13);
		else if (c[0]=='Q')
			p1.push_back(12);
		else if (c[0]=='J')
			p1.push_back(11);
		else
			p1.push_back(stoi(c));
	}

	//Player 2 Cards
	scanf("%d", &n);
	REP(i, n) {
		char c[10];
		scanf("%s", c);
		c[strlen(c)-1] = 0;
		if (c[0]=='A')
			p2.push_back(14);
		else if (c[0]=='K')
			p2.push_back(13);
		else if (c[0]=='Q')
			p2.push_back(12);
		else if (c[0]=='J')
			p2.push_back(11);
		else
			p2.push_back(stoi(c));
	}

	int winner = -1, round = 0;
	while(1){
		if (p1.size()==0) {
			winner = 2;
			break;
		}
		else if (p2.size()==0) {
			winner = 1;
			break;
		}
		else {
			int winB = battle();
			if (winB==-1) {
				round++;
				break;
			}
		}
		round++;
		debugCards(); 
	}

	debugCards();

	if (winner==1) 
		printf("1 %d\n", round);
	else if (winner==2) 
		printf("2 %d\n", round);
	else
		printf("PAT");

	return 0;
}

//Solved