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
#define PI 3.1415926535898

struct point {
	double x, y;
public:
	inline point() {
		x = 1;
		y = 1;
	}
	inline point(double px, double py) {
		x = px;
		y = py;
	}
	inline void print() {
		printf("%d %d\n", (int)x, (int)y);
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

inline point round_point(point p) {
	return point(round(p.x), round(p.y));
}

inline point truncate_point(point p) {
	return point((int)p.x, (int)p.y);
}

inline double degtorad(double deg) {
	return deg*PI/180;
}

inline double radtodeg(double rad) {
	return rad*180/PI;
}

inline double smalldiffAngle(double a, double b) {

	double maxang = max(a, b), minang = min(a, b);
	double alpha = maxang-minang, beta = minang+(360-maxang);
	return alpha<beta?-alpha:beta;
}

inline double distance(point a, point b) {
	double x = (a.x-b.x), y = (a.y-b.y);
	return sqrt(x*x + y*y);
}

bool pointinCheckpoint(point p, int cp) {

	if (distance(p, checkpoints[cp])<600)
		return true;
	else
		return false;

}

double angle_3points(point a, point b, point c) {

	point ab = a-b, bc = b-c;
	double prod = ab.x*bc.x + ab.y*bc.y;
	double mag = distance(a, b), distance(b, c);

	return radtodeg(acos(prod/mag));

}

vector<point> predict(pod p, int thrust, point target, int turns) {

	vector<point> res;

	REP(i, turns) {

		double theta = radtodeg(atan2(target.y-p.loc.y, target.x-p.loc.x));
		theta = fmod(theta + 360, 360);
		double diff = smalldiffAngle(theta, p.angle);

		if (diff > +18)
			diff = +18;
		if (diff < -18)
			diff = -18;

		p.angle = fmod(p.angle + diff + 360, 360);

		point vt = point( cos(degtorad(p.angle))*thrust, sin(degtorad(p.angle))*thrust);

		p.speed += vt;
		p.loc = round_point(p.loc+p.speed);
		p.speed = truncate_point(p.speed*0.85);
		res.push_back(p.loc);
		DB("Turn +%d = %5.2lf %5.2lf\n", i+1, p.loc.x, p.loc.y);
	}
	return res;
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
			scanf("%lf %lf %lf %lf %lf %d",
				  &player[i].loc.x, &player[i].loc.y,
				  &player[i].speed.x, &player[i].speed.y,
				  &player[i].angle, &player[i].next_cp);
			DB("Pod %d is facing angle %lf\n", i+1, player[i].angle);
		}

		REP(i, 2)
			scanf("%lf %lf %lf %lf %lf %d",
				  &enemy[i].loc.x  , &enemy[i].loc.y,
				  &enemy[i].speed.x, &enemy[i].speed.y,
				  &enemy[i].angle  , &enemy[i].next_cp);

		int cp1 = player[0].next_cp, cp2 = player[1].next_cp;
		int ncp1 = (player[0].next_cp+1)%cp_count, ncp2 = (player[1].next_cp+1)%cp_count;

		vector<point> predictions1 = predict(player[0], 0, checkpoints[cp1], 10);
		vector<point> predictions2 = predict(player[1], 0, checkpoints[cp2], 10);
		
		double ang1 = angle_3points(player[0].loc, checkpoints[cp1], checkpoints[ncp1]);
		
		int turntonextcp = -1;
		REP(i, 10) {
			if(n)
		}

		DB("\nEnd of Round %d\n", round);
		round++;
	}
	
	return 0;
}

//