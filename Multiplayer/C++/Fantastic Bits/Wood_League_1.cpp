/*~~~~~~~~~~~~~~~~~~*
 *                  *
 * $Dollar Akshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.codingame.com/ide/6300886932c2a2159ec88e46239f1d880df8337

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
	float x, y;
    public:
	inline point() {
		x = 1;
		y = 1;
	}
	inline point(float px, float py) {
		x = px;
		y = py;
	}
	inline void print() {
		printf("%d %d\n", (int)x, (int)y);
	}
	inline int manhatanDistance(point p) {
		return fabs(x-p.x) + fabs(y-p.y);
	}
    inline float distance(point p) {
        float dx = x-p.x, dy=y-p.y;
		return sqrt(dx*dx + dy*dy);
	}
	inline bool operator != (const point rhs) const {
		return x!=rhs.x || y!=rhs.y;
	}
	inline bool operator == (const point rhs) const {
		return x==rhs.x && y==rhs.y;
	}
	inline bool operator < (const point rhs) const {
		return (x<rhs.x) || (x==rhs.x && y<rhs.y);
	}
	inline point operator + (point rhs) {
		return point(x+rhs.x, y+rhs.y);
	}
	inline point operator - (point rhs) {
		return point(x-rhs.x, y-rhs.y);
	}
	inline point operator * (float k) {
		return point(x*k, y*k);
	}
	inline point operator += (point rhs) {
		x += rhs.x;
		y += rhs.y;
		return *this;
	}
	inline point operator -= (point rhs) {
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}
	inline point operator *= (float k) {
		x = x*k;
		y = y*k;
		return *this;
	}

};

struct Entity{
    int id, state;
    float vx, vy;
    char type[100];
    point loc;

	float getSpeed(){
		return sqrt(vx*vx + vy*vy);
	}
};

int myID, n;
Entity obj[100];

int findNearestSnaffle(point p){

    int res = -1;
    float minDist = 100000;
    
     REP(i, n){
         if(obj[i].type[0] == 'S' ){
             float dist = p.distance(obj[i].loc);
             if(dist < minDist){
                 res = i;
                 minDist = dist;
             }
         }
     }

     return res;

}

int findNearestEnemy(point p){

    int res = -1;
    float minDist = 100000;
    
     REP(i, n){
         if(obj[i].type[0] == 'O' ){
             float dist = p.distance(obj[i].loc);
             if(dist < minDist){
                 res = i;
                 minDist = dist;
             }
         }
     }

     return res;

}


int main(){

    scanf("%d", &myID);
    
    while(1){

		int wiz1=-1, wiz2=-1;
        scanf("%d", &n);
        REP(i, n){
            scanf("%d %s %f %f %f %f %f", &obj[i].id, obj[i].type, &obj[i].loc.x, &obj[i].loc.y, &obj[i].vx, &obj[i].vy, &obj[i].state);   
            //DB("%d %s %.0f %.0f %.0f %.0f %d\n", obj[i].id, obj[i].type, obj[i].loc.x, obj[i].loc.y, obj[i].vx, obj[i].vy, obj[i].state);  
			if(obj[i].type[0] == 'W' ){
				if(wiz1==-1)
					wiz1=i;
				else
					wiz2 = i;
			}
        }

		point goal = point(  (!myID)*16000, 3750);
		point defend = point(  myID*16000 + (myID==0?500:(-500)), 3750);

		// Wizard 1 Scores Goal
		if(obj[wiz1].state==0){
			int snaffle = findNearestSnaffle(goal);

			float distfromsnaff = obj[snaffle].loc.distance(obj[wiz1].loc);
			float thrust = min(150.0f, 150*distfromsnaff/10 );

			DB("Wizard 1 going for snaffle %d\n", snaffle);
			printf("MOVE %.0f %.0f %.0f\n", obj[snaffle].loc.x, obj[snaffle].loc.y, thrust );
		}
		else{
			DB("Wizard 1 Throwing\n");
			float distfromgoal = goal.distance(obj[wiz1].loc);
			float thrust = 500.0f;
			printf("THROW %.0f %.0f %0.f\n", goal.x, goal.y, thrust );
		}
		
		//Wizard 2 defend goal
		if(obj[wiz2].state==0){
			int snaffle = findNearestSnaffle(defend);

			float distfromsnaff = obj[snaffle].loc.distance(obj[wiz2].loc);
			float thrust = min(150.0f, 150*distfromsnaff/10 );

			DB("Wizard 2 going for snaffle %d\n", snaffle);
			printf("MOVE %.0f %.0f %.0f\n", obj[snaffle].loc.x, obj[snaffle].loc.y, thrust );
		}
		else{
			DB("Wizard 2 Throwing\n");
			float distfromgoal = goal.distance(obj[wiz2].loc);
			float thrust = 500.0f;
			printf("THROW %.0f %.0f %0.f\n", goal.x, goal.y, thrust );
		}
        
    }
    
    return 0;
}

//