/*~~~~~~~~~~~~~~~~~~*
*                  *
*  $DollarAkshay$  *
*                  *
*~~~~~~~~~~~~~~~~~~*/

//https://www.codingame.com/ide/109098780ee8de14bdcef46f4f6342a1e683306c

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
#define DB(format, ...) fprintf(stderr, format, ##__VA_ARGS__)
#define mp(a, b) make_pair(a, b)
#define MSX(a, x) memset(a, x, sizeof(a))
#define SORT(a, n) sort(begin(a), begin(a) + n)
#define ll long long
#define MOD 1000000007

enum class UnitType : int {
	QUEEN = -1,
	KNIGHT = 0,
	ARCHER = 1,
	GIANT = 2
};

enum class SiteType : int {
	EMPTY = -1,
	TOWER = 1,
	BARRACKS = 2
};

enum class PlayerType : int {
	NEUTRAL = -1,
	FRIENDLY = 0,
	ENEMY = 1
};

class Point {
  public:
	int x, y;

	Point() {
	}

	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}

	void print() {
		printf("%d %d\n", x, y);
	}

	double distance(class Point p) {
		return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
	}

	bool operator!=(const class Point rhs) const {
		return x != rhs.x || y != rhs.y;
	}

	bool operator==(const class Point rhs) const {
		return x == rhs.x && y == rhs.y;
	}

	bool operator<(const class Point rhs) const {
		return (x < rhs.x) || (x == rhs.x && y < rhs.y);
	}

	Point operator+(class Point rhs) {
		return Point(x + rhs.x, y + rhs.y);
	}

	Point operator-(class Point rhs) {
		return Point(x - rhs.x, y - rhs.y);
	}

	Point operator*(double k) {
		return Point(round(x * k), round(y * k));
	}
};

class Site {
  public:
	// Common Variables
	int id, r;
	class Point pos;
	enum class SiteType type;
	enum class PlayerType owner;
	// Tower Variables
	int towerHP, towerAttackRange;
	// Barracks Variables
	int barracksDelay;
	enum class UnitType barracksUnit;

	Site() {
		id = -1;
		pos = Point();
		type = SiteType::EMPTY;

		towerHP = -1;
		towerAttackRange = -1;

		barracksDelay = -1;
		barracksUnit = UnitType::QUEEN;
	}

	Site(int id, class Point pos, int r) {
		this->id = id;
		this->pos = pos;
		this->r = r;
		type = SiteType::EMPTY;

		towerHP = -1;
		towerAttackRange = -1;

		barracksDelay = -1;
		barracksUnit = UnitType::QUEEN;
	}
};

class Unit {
  public:
	int hp;
	class Point pos;
	enum class PlayerType owner;
	enum class UnitType type;

	Unit() {
	}

	Unit(int hp, class Point pos, enum class PlayerType owner, enum class UnitType type) {
		this->hp = hp;
		this->pos = pos;
		this->owner = owner;
		this->type = type;
	}
};

/* ------------
	GLOBALS        	
------------ */

// Global Constants
const int QUEEN_SPEED = 60;
const int COST_ARCHER = 100;
const int COST_GIANT = 140;
const int COST_KNIGHT = 80;

// Global Variables
int siteCount;
int unitCount;
int gold, touchedSite;

// Site Variables
vector<class Site> allSites;
vector<class Site> neutralSites;

vector<class Site> friendlySites;
vector<class Site> friendlyBarracks;
vector<class Site> friendlyBarracksArcher;
vector<class Site> friendlyBarracksGiant;
vector<class Site> friendlyBarracksKnight;
vector<class Site> friendlyTowers;

vector<class Site> enemySites;
vector<class Site> enemyBarracks;
vector<class Site> enemyBarracksArcher;
vector<class Site> enemyBarracksGiant;
vector<class Site> enemyBarracksKnight;
vector<class Site> enemyTowers;

// Unit Variables
vector<class Unit> allUnits;

vector<class Unit> friendlyUnits;
class Unit friendlyQueen;
vector<class Unit> friendlyArchers;
vector<class Unit> friendlyGiants;
vector<class Unit> friendlyKnights;

vector<class Unit> enemyUnits;
class Unit enemyQueen;
vector<class Unit> enemyArchers;
vector<class Unit> enemyGiants;
vector<class Unit> enemyKnights;

/* --------------
	FUNCTIONS    	
-------------- */

// The comprator function for a site
bool siteCompare(class Site lhs, class Site rhs) {
	return lhs.pos.distance(friendlyQueen.pos) < rhs.pos.distance(friendlyQueen.pos);
}

// Categorize all sites into respective arrays
void categorizeSites() {

	neutralSites.clear();

	friendlySites.clear();
	friendlyBarracks.clear();
	friendlyBarracksArcher.clear();
	friendlyBarracksGiant.clear();
	friendlyBarracksKnight.clear();
	friendlyTowers.clear();

	enemySites.clear();
	enemyBarracks.clear();
	enemyBarracksArcher.clear();
	enemyBarracksGiant.clear();
	enemyBarracksKnight.clear();
	enemyTowers.clear();

	REP(i, allSites.size()) {
		class Site site = allSites[i];
		// Categorizing Player Type
		if (site.owner == PlayerType::FRIENDLY) {
			friendlySites.pb(site);
			// Categorizing Site Type
			if (site.type == SiteType::BARRACKS) {
				friendlyBarracks.pb(site);
				// Categorizing Barracks Type
				if (site.barracksUnit == UnitType::ARCHER) {
					friendlyBarracksArcher.pb(site);
				}
				else if (site.barracksUnit == UnitType::GIANT) {
					friendlyBarracksGiant.pb(site);
				}
				else if (site.barracksUnit == UnitType::KNIGHT) {
					friendlyBarracksKnight.pb(site);
				}
			}
			else if (site.type == SiteType::TOWER) {
				friendlyTowers.pb(site);
			}
		}
		else if (site.owner == PlayerType::ENEMY) {
			enemySites.pb(site);
			// Categorizing Site Type
			if (site.type == SiteType::BARRACKS) {
				enemyBarracks.pb(site);
				// Categorizing Barracks Type
				if (site.barracksUnit == UnitType::ARCHER) {
					enemyBarracksArcher.pb(site);
				}
				else if (site.barracksUnit == UnitType::GIANT) {
					enemyBarracksGiant.pb(site);
				}
				else if (site.barracksUnit == UnitType::KNIGHT) {
					enemyBarracksKnight.pb(site);
				}
			}
			else if (site.type == SiteType::TOWER) {
				enemyTowers.pb(site);
			}
		}
		else {
			neutralSites.pb(site);
		}
	}
}

// Sort all categories of sites based on distance from friendlyQueen
void sortSites() {

	sort(allSites.begin(), allSites.end(), siteCompare);
	sort(neutralSites.begin(), neutralSites.end(), siteCompare);

	sort(friendlySites.begin(), friendlySites.end(), siteCompare);
	sort(friendlyBarracks.begin(), friendlyBarracks.end(), siteCompare);
	sort(friendlyBarracksArcher.begin(), friendlyBarracksArcher.end(), siteCompare);
	sort(friendlyBarracksGiant.begin(), friendlyBarracksGiant.end(), siteCompare);
	sort(friendlyBarracksKnight.begin(), friendlyBarracksKnight.end(), siteCompare);
	sort(friendlyTowers.begin(), friendlyTowers.end(), siteCompare);

	sort(enemySites.begin(), enemySites.end(), siteCompare);
	sort(enemyBarracks.begin(), enemyBarracks.end(), siteCompare);
	sort(enemyBarracksArcher.begin(), enemyBarracksArcher.end(), siteCompare);
	sort(enemyBarracksGiant.begin(), enemyBarracksGiant.end(), siteCompare);
	sort(enemyBarracksKnight.begin(), enemyBarracksKnight.end(), siteCompare);
	sort(enemyTowers.begin(), enemyTowers.end(), siteCompare);
}

// The comprator function for a unit
bool unitCompare(class Unit lhs, class Unit rhs) {
	return lhs.pos.distance(friendlyQueen.pos) < rhs.pos.distance(friendlyQueen.pos);
}

// Categorize all units into respective arrays
void categorizeUnits() {

	friendlyUnits.clear();
	friendlyArchers.clear();
	friendlyGiants.clear();
	friendlyKnights.clear();
	enemyUnits.clear();
	enemyArchers.clear();
	enemyGiants.clear();
	enemyKnights.clear();

	REP(i, allUnits.size()) {
		class Unit unit = allUnits[i];
		// Categorizing Player Type
		if (unit.owner == PlayerType::FRIENDLY) {
			friendlyUnits.pb(unit);
			// Categorizing Unit Type
			if (unit.type == UnitType::ARCHER) {
				friendlyArchers.pb(unit);
			}
			else if (unit.type == UnitType::GIANT) {
				friendlyGiants.pb(unit);
			}
			else if (unit.type == UnitType::KNIGHT) {
				friendlyKnights.pb(unit);
			}
			else if (unit.type == UnitType::QUEEN) {
				friendlyQueen = unit;
			}
		}
		else if (unit.owner == PlayerType::ENEMY) {
			enemyUnits.pb(unit);
			// Categorizing Unit Type
			if (unit.type == UnitType::ARCHER) {
				enemyArchers.pb(unit);
			}
			else if (unit.type == UnitType::GIANT) {
				enemyGiants.pb(unit);
			}
			else if (unit.type == UnitType::KNIGHT) {
				enemyKnights.pb(unit);
			}
			else if (unit.type == UnitType::QUEEN) {
				enemyQueen = unit;
			}
		}
	}
}

// Sort all categories of units based on distance from friendlyQueen
void sortUnits() {

	sort(allUnits.begin(), allUnits.end(), unitCompare);

	sort(friendlyUnits.begin(), friendlyUnits.end(), unitCompare);
	sort(friendlyArchers.begin(), friendlyArchers.end(), unitCompare);
	sort(friendlyGiants.begin(), friendlyGiants.end(), unitCompare);
	sort(friendlyKnights.begin(), friendlyKnights.end(), unitCompare);

	sort(enemyUnits.begin(), enemyUnits.end(), unitCompare);
	sort(enemyArchers.begin(), enemyArchers.end(), unitCompare);
	sort(enemyGiants.begin(), enemyGiants.end(), unitCompare);
	sort(enemyKnights.begin(), enemyKnights.end(), unitCompare);
}

// Get the index position of a given siteId in the allSites vector
int findIndexOfSiteByID(int siteId) {
	REP(i, allSites.size()) {
		class Site site = allSites[i];
		if (site.id == siteId) {
			return i;
		}
	}
	return -1;
}

// Find the nearest unit from a given point
class Unit findNearestUnit(class Point src) {

	class Unit res;
	double bestDist = -1;
	REP(i, allUnits.size()) {
		class Unit unit = allUnits[i];
		double curDist = unit.pos.distance(src);
		if (bestDist == -1 || curDist < bestDist) {
			res = unit;
			bestDist = curDist;
		}
	}

	return res;
}

// Find the nearest site from a given point
class Site findNearestSite(class Point src) {

	class Site res;
	double bestDist = -1;
	REP(i, allSites.size()) {
		class Site site = allSites[i];
		double curDist = site.pos.distance(src);
		if (bestDist == -1 || curDist < bestDist) {
			res = site;
			bestDist = curDist;
		}
	}

	return res;
}

// Return a list of barack ids whos training turn delay is 0
vector<int> getTrainableBarracksID() {

	vector<int> res;

	REP(i, friendlyBarracks.size()) {
		class Site site = friendlyBarracks[i];
		if (site.barracksDelay == 0) {
			res.pb(site.id);
		}
	}

	return res;
}

class Point evade(class Unit nearestEnemy) {
	class Point delta = friendlyQueen.pos - nearestEnemy.pos;
	double distFromQueen = nearestEnemy.pos.distance(friendlyQueen.pos);
	delta = delta * (QUEEN_SPEED / distFromQueen);
	return friendlyQueen.pos + delta;
}

// Read Site Data from STDIN
void readSiteData() {

	REP(i, siteCount) {
		int id, _1, _2, structure, owner, param1, param2;
		scanf("%d %d %d %d %d %d %d", &id, &_1, &_2, &structure, &owner, &param1, &param2);
		int siteIndex = findIndexOfSiteByID(id);
		class Site &site = allSites[siteIndex];
		site.type = SiteType(structure);
		site.owner = PlayerType(owner);

		if (site.type == SiteType::TOWER) {
			site.towerHP = param1;
			site.towerAttackRange = param2;
		}
		else if (site.type == SiteType::BARRACKS) {
			site.barracksDelay = param1;
			site.barracksUnit = UnitType(param2);
		}
	}
}

// Read unit data from STDIN
void readUnitData() {

	allUnits.clear();

	scanf("%d", &unitCount);
	REP(i, unitCount) {
		int x, y, owner, type, hp;
		scanf("%d %d %d %d %d", &x, &y, &owner, &type, &hp);
		class Point pos = Point(x, y);
		allUnits.pb(Unit(hp, pos, PlayerType(owner), UnitType(type)));

		//DB("UNIT = %d %d %d %d %d\n", x, y, owner, type, hp);
	}
}

/* ---------
	MAIN                	
--------- */

int main() {

	scanf("%d", &siteCount);
	REP(i, siteCount) {
		int id, x, y, r;
		scanf("%d %d %d %d", &id, &x, &y, &r);
		class Point pos = Point(x, y);
		allSites.pb(Site(id, pos, r));
	}

	while (true) {

		scanf("%d %d", &gold, &touchedSite);

		readSiteData();
		readUnitData();

		categorizeSites();
		categorizeUnits();

		sortSites();
		sortUnits();

		DB("NEAREST NEUTRAL SITE : %d\n", neutralSites[0].id);
		DB("FRIENDLY BARRACKS    : %d\n", friendlyBarracks.size());
		DB("FRIENDLY TOWERS      : %d\n", friendlyTowers.size());

		if (friendlyBarracks.size() < 1) {
			if (neutralSites.size() > 0) {
				printf("BUILD %d BARRACKS-KNIGHT\n", neutralSites[0].id);
			}
			else {
				printf("WAIT\n");
			}
		}
		else if (friendlyTowers.size() < 2) {
			if (neutralSites.size() > 0) {
				printf("BUILD %d TOWER\n", neutralSites[0].id);
			}
			else {
				printf("WAIT\n");
			}
		}
		else {
			DB("TOWER HP      : %d %d\n", friendlyTowers[0].towerHP, friendlyTowers[1].towerHP);
			if (friendlyTowers[0].towerHP < 750) {
				printf("BUILD %d TOWER\n", friendlyTowers[0].id);
			}
			else if (friendlyTowers[1].towerHP < 750) {
				printf("BUILD %d TOWER\n", friendlyTowers[1].id);
			}
			else {
				printf("BUILD %d TOWER\n", friendlyTowers[0].id);
			}
		}

		// Train all barracks to pump knights
		vector<int> trainableBarracks = getTrainableBarracksID();
		printf("TRAIN");
		REP(i, trainableBarracks.size()) {
			if (gold >= COST_KNIGHT) {
				printf(" %d", trainableBarracks[i]);
				gold -= COST_KNIGHT;
			}
		}
		printf("\n");
	}

	return 0;
}

//