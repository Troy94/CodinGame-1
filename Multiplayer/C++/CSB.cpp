/*~~~~~~~~~~~~~~~~~~*
 *                  *
 * $Dollar Akshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.codingame.com/ide/3366125ed9eaaabc1868622a9b212a120bc34ba

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
public:
	inline point() {
		x = 1;
		y = 1;
	}
	inline point(int px, int py) {
		x = px;
		y = py;
	}
	inline void print() {
		printf("%d %d\n", x, y);
	}
	inline int manhatanDistance(point p) {
		return abs(x-p.x) + abs(y-p.y);
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
	inline point operator * (double k) {
		return point((int)(x*k), (int)(y*k));
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
	inline point operator *= (double k) {
		x = x*k;
		y = y*k;
		return *this;
	}


};

struct pod {
	int next_cp;
	double angle;
	point loc, speed;
	
};

int laps, cp_count;

pod player[2], enemy[2];

vector<point> checkpoints;

inline double degtorad(double deg) {
	return deg*3.14159265358979/180;
}

inline double radtodeg(double rad) {
	return rad*180/3.14159265358979;
}

point predict(pod p, int thrust, point target, int turns) {

	REP(i, turns) {

		double theta = radtodeg(atan2(target.y-p.loc.y, target.x-p.loc.x));

		if (theta<0)
			theta += 360;

		//DB("\nTheta = %f\n", theta);

		theta = (theta-p.angle);

		if (theta>180)
			theta = 180-theta;
		if (theta<-180)
			theta = 180 + theta;

		//DB("Diff = %f\n", theta);

		if (theta > +18)
			theta = +18;
		if (theta < -18)
			theta = -18;

		//DB("Pre Update Angle = %f\n", p.angle);
		p.angle -= theta;
		if (p.angle<0)
			p.angle += 360;
		p.angle = fmod(p.angle, 360);

		DB("Update Angle = %f\n", p.angle);

		point vt = point( round(cos(degtorad(p.angle))*thrust), round(sin(degtorad(p.angle))*thrust));
		//p.angle = round(p.angle);
		//DB("Thrust %d %d\n", vt.x, vt.y);
		//DB("Actual Thrust %.4f %.4f\n\n", (double)cos(degtorad(p.angle))*thrust, (double)sin(degtorad(p.angle))*thrust);
		
		//DB("Pre Speed = %d %d\n", p.speed.x, p.speed.y);
		p.speed += vt;
		//DB("Post Speed = %d %d\n", p.speed.x, p.speed.y);
		p.loc += p.speed;
		p.speed*=0.85;
		//DB("Post Speed MUL = %d %d\n\n", p.speed.x, p.speed.y);
		DB("Turn +%d = %5d, %5d\n", i+1, p.loc.x, p.loc.y);
	}
	return p.loc;
}


int main(){

	int round = 0;

	scanf("%d %d", &laps, &cp_count);
	REP(i, cp_count) {
		int px, py;
		scanf("%d %d", &px, &py);
		point p = { px, py };
		checkpoints.push_back(p);
	}
	
	while(1){
		REP(i, 2) {
			scanf("%d %d %d %d %lf %d",
				  &player[i].loc.x, &player[i].loc.y,
				  &player[i].speed.x, &player[i].speed.y,
				  &player[i].angle, &player[i].next_cp);
			DB("Pod %d is facing angle %lf\n", i+1, player[i].angle);
		}

		REP(i, 2)
			scanf("%d %d %d %d %lf %d",
				  &enemy[i].loc.x  , &enemy[i].loc.y,
				  &enemy[i].speed.x, &enemy[i].speed.y,
				  &enemy[i].angle  , &enemy[i].next_cp);

		int cp1 = player[0].next_cp, cp2 = player[1].next_cp;

		printf("%d %d 100\n", checkpoints[cp1].x, checkpoints[cp1].y);
		printf("%d %d 200\n", checkpoints[cp2].x, checkpoints[cp2].y);

		DB("\nPredications for POD 1:\n");
		predict(player[0], 100, checkpoints[cp1], 5);

		DB("\nEnd of Round %d\n", round);
		round++;
	}
	
	return 0;
}

//