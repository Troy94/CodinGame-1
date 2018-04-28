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
	MINE = 0,
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
		x = -1;
		y = -1;
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
	int goldRemaining, maxGoldRate;
	class Point pos;
	enum class SiteType type;
	enum class PlayerType owner;
	// Barracks Variables
	int barracksDelay;
	enum class UnitType barracksUnit;
	// Mine Variables
	int mineGoldRate;
	// Tower Variables
	int towerHP, towerAttackRange;

	Site() {
		id = -1;
		pos = Point();
		type = SiteType::EMPTY;
		maxGoldRate = -1;

		barracksDelay = -1;
		barracksUnit = UnitType::QUEEN;

		mineGoldRate = -1;

		towerHP = -1;
		towerAttackRange = -1;
	}

	Site(int id, class Point pos, int r) {
		this->id = id;
		this->pos = pos;
		this->r = r;
		type = SiteType::EMPTY;
		maxGoldRate = -1;

		barracksDelay = -1;
		barracksUnit = UnitType::QUEEN;

		mineGoldRate = -1;

		towerHP = -1;
		towerAttackRange = -1;
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

// Game Constants
const int MAP_WIDTH = 1920;
const int MAP_HEIGHT = 1000;
const int BASE_X_PADDING = 120;

const int QUEEN_SPEED = 60;
const int COST_ARCHER = 100;
const int COST_GIANT = 140;
const int COST_KNIGHT = 80;

const int TOWER_HP = 800;

map<enum class UnitType, int> UNIT_COST = {
	pair<enum class UnitType, int>(UnitType::ARCHER, 100),
	pair<enum class UnitType, int>(UnitType::GIANT, 140),
	pair<enum class UnitType, int>(UnitType::KNIGHT, 80),
	pair<enum class UnitType, int>(UnitType::QUEEN, -1),
};

// Global Variables
int siteCount;
int unitCount;
int gold, touchedSite;
int goldIncomeRate;
queue<string> pendingActions;

class Point friendlyBaseCenter;
class Point enemyBaseCenter;

// Site Variables
vector<class Site> allSites;
vector<class Site> neutralSites;

vector<class Site> friendlySites;
vector<class Site> friendlyBarracks;
vector<class Site> friendlyBarracksArcher;
vector<class Site> friendlyBarracksGiant;
vector<class Site> friendlyBarracksKnight;
vector<class Site> friendlyMines;
vector<class Site> friendlyTowers;

vector<class Site> enemySites;
vector<class Site> enemyBarracks;
vector<class Site> enemyBarracksArcher;
vector<class Site> enemyBarracksGiant;
vector<class Site> enemyBarracksKnight;
vector<class Site> enemyMines;
vector<class Site> enemyTowers;

vector<class Site> minesToBuild;
vector<class Site> towersToBuild;

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

// Read Site Data from STDIN
void readSiteData() {

	REP(i, siteCount) {
		int id, goldRemaining, maxGoldRate, structure, owner, param1, param2;
		scanf("%d %d %d %d %d %d %d", &id, &goldRemaining, &maxGoldRate, &structure, &owner, &param1, &param2);
		int siteIndex = findIndexOfSiteByID(id);
		class Site &site = allSites[siteIndex];
		site.type = SiteType(structure);
		site.owner = PlayerType(owner);
		site.goldRemaining = goldRemaining;
		if (maxGoldRate != -1) {
			site.maxGoldRate = maxGoldRate;
		}

		if (site.type == SiteType::TOWER) {
			site.towerHP = param1;
			site.towerAttackRange = param2;
		}
		else if (site.type == SiteType::BARRACKS) {
			site.barracksDelay = param1;
			site.barracksUnit = UnitType(param2);
		}
		else if (site.type == SiteType::MINE) {
			site.mineGoldRate = param1;
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
	friendlyMines.clear();
	friendlyTowers.clear();

	enemySites.clear();
	enemyBarracks.clear();
	enemyBarracksArcher.clear();
	enemyBarracksGiant.clear();
	enemyBarracksKnight.clear();
	enemyMines.clear();
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
			else if (site.type == SiteType::MINE) {
				friendlyMines.pb(site);
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
			else if (site.type == SiteType::MINE) {
				enemyMines.pb(site);
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
	sort(friendlyMines.begin(), friendlyMines.end(), siteCompare);
	sort(friendlyTowers.begin(), friendlyTowers.end(), siteCompare);

	sort(enemySites.begin(), enemySites.end(), siteCompare);
	sort(enemyBarracks.begin(), enemyBarracks.end(), siteCompare);
	sort(enemyBarracksArcher.begin(), enemyBarracksArcher.end(), siteCompare);
	sort(enemyBarracksGiant.begin(), enemyBarracksGiant.end(), siteCompare);
	sort(enemyBarracksKnight.begin(), enemyBarracksKnight.end(), siteCompare);
	sort(enemyMines.begin(), enemyMines.end(), siteCompare);
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

// Find the nearest unit from a given point for a given array
class Unit findNearestUnit(vector<class Unit> array, class Point src) {

	class Unit res;
	double bestDist = -1;
	REP(i, array.size()) {
		class Unit unit = array[i];
		double curDist = unit.pos.distance(src);
		if (bestDist == -1 || curDist < bestDist) {
			res = unit;
			bestDist = curDist;
		}
	}

	return res;
}

// Find the nearest site from a given point for a given array
class Site findNearestSite(vector<class Site> array, class Point src) {

	class Site res;
	double bestDist = -1;
	REP(i, array.size()) {
		class Site site = array[i];
		double curDist = site.pos.distance(src);
		if (bestDist == -1 || curDist < bestDist) {
			res = site;
			bestDist = curDist;
		}
	}

	return res;
}

// Return a list of barack ids whos training turn delay is 0
vector<class Site> getTrainableBarracksID() {

	vector<class Site> res;

	REP(i, friendlyBarracks.size()) {
		class Site site = friendlyBarracks[i];
		if (site.barracksDelay == 0) {
			res.pb(site);
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

class Point evade(class Site nearestEnemy) {
	class Point delta = friendlyQueen.pos - nearestEnemy.pos;
	double distFromQueen = nearestEnemy.pos.distance(friendlyQueen.pos);
	delta = delta * (QUEEN_SPEED / distFromQueen);
	return friendlyQueen.pos + delta;
}

// Calculate some global variables
void calculateGlobals() {

	// Calculate the current ammount of gold being generated
	goldIncomeRate = 0;
	REP(i, friendlyMines.size()) {
		goldIncomeRate += friendlyMines[i].mineGoldRate;
	}

	// Find Our Base Center only once per game.
	if (friendlyBaseCenter.x == -1 && friendlyBaseCenter.y == -1) {
		if (friendlyQueen.pos.x < MAP_WIDTH / 2) {
			friendlyBaseCenter = Point(BASE_X_PADDING, MAP_HEIGHT / 2);
			enemyBaseCenter = enemyQueen.pos;
		}
		else {
			friendlyBaseCenter = Point(MAP_WIDTH - BASE_X_PADDING, MAP_HEIGHT / 2);
			enemyBaseCenter = enemyQueen.pos;
		}
	}
}

class Site findSuitableMine() {

	class Site res;
	REP(i, neutralSites.size()) {
		class Site mine = neutralSites[i];
		DB("MINE : %d %d\n", mine.id, mine.goldRemaining);
		if (mine.goldRemaining >= 10 || mine.goldRemaining == -1) {
			res = mine;
			break;
		}
	}

	return res;
}

class Site findRepairableTower() {

	class Site res;
	int minHP = TOWER_HP;
	REP(i, friendlyTowers.size()) {
		class Site tower = friendlyTowers[i];
		if (tower.towerHP <= minHP) {
			res = tower;
			minHP = tower.towerHP;
		}
	}

	return res;
}

int enemyTowersInRange(class Point p) {

	int res = 0;
	REP(i, enemyTowers.size()) {
		class Site tower = enemyTowers[i];
		if (p.distance(tower.pos) <= tower.towerAttackRange) {
			res++;
		}
	}

	return res;
}

bool isQueenInDanger() {

	int towersCloseBy = 0;
	int kightsCloseBy = 0;
	int senseDistance = 200;

	REP(i, enemyTowers.size()) {
		class Site tower = enemyTowers[i];
		if (tower.pos.distance(friendlyQueen.pos) <= tower.towerAttackRange + QUEEN_SPEED + 10) {
			towersCloseBy++;
		}
	}

	REP(i, enemyKnights.size()) {
		class Unit knight = enemyKnights[i];
		if (knight.pos.distance(friendlyQueen.pos) <= senseDistance) {
			kightsCloseBy++;
		}
	}

	return (kightsCloseBy + towersCloseBy) > 0 ? true : false;
}

void findMinesAndTowers() {

	vector<class Site> allSitesPositionSorted;

	allSitesPositionSorted = allSites;
	sort(allSitesPositionSorted.begin(), allSitesPositionSorted.end(),
		 [](class Site &lhs, class Site &rhs) {
			 return lhs.pos.x < rhs.pos.x || (lhs.pos.x == rhs.pos.x && lhs.pos.y < rhs.pos.y);
		 });
}

void debuggingInfo() {
	queue<string> pendingActionsCopy = pendingActions;
	DB("PENDING ACTIONS      :");
	while (pendingActionsCopy.empty() == false) {
		DB(" %s,", pendingActionsCopy.front().c_str());
		pendingActionsCopy.pop();
	}
	DB("\n");

	DB("TOUCHING SITE        : %d\n", touchedSite);
	DB("NEAREST NEUTRAL SITE : %d\n", neutralSites[0].id);
	DB("FRIENDLY MINES       : %d\n", friendlyMines.size());
	DB("FRIENDLY BARRACKS    : %d\n", friendlyBarracks.size());
	DB("FRIENDLY TOWERS      : %d\n", friendlyTowers.size());

	DB("MINE RATE            : ");
	REP(i, friendlyMines.size()) {
		DB("%d ", friendlyMines[i].mineGoldRate);
	}
	DB("\n");

	DB("MAX MINE RATE        : ");
	REP(i, friendlyMines.size()) {
		DB("%d ", friendlyMines[i].maxGoldRate);
	}
	DB("\n");
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

		string turnAction = "WAIT";
		string turnTrain = "TRAIN";

		scanf("%d %d", &gold, &touchedSite);

		readSiteData();
		readUnitData();

		categorizeSites();
		categorizeUnits();

		calculateGlobals();

		sortSites();
		sortUnits();

		findMinesAndTowers();

		debuggingInfo();

		if (isQueenInDanger()) {
			turnAction = "MOVE " + to_string(friendlyBaseCenter.x) + " " + to_string(friendlyBaseCenter.y);
		}
		else if (pendingActions.empty() == false) {
			turnAction = pendingActions.front();
			pendingActions.pop();
		}
		else if (friendlyBarracks.size() < 1) {
			if (neutralSites.size() > 0) {
				turnAction = "BUILD " + to_string(neutralSites[0].id) + " BARRACKS-KNIGHT";
			}
		}
		else if (friendlyTowers.size() < 9 && neutralSites.size() > 0 && enemyTowersInRange(neutralSites[0].pos) == 0) {
			turnAction = "BUILD " + to_string(neutralSites[0].id) + " TOWER";
			if (touchedSite == neutralSites[0].id) {
				REP(i, 6) {
					pendingActions.push("BUILD " + to_string(neutralSites[0].id) + " TOWER");
				}
			}
		}
		else {
			class Site tower = findRepairableTower();
			if (tower.id != -1) {
				turnAction = "BUILD " + to_string(tower.id) + " TOWER";
				int fullHealTurns = (TOWER_HP - (tower.towerHP + 100)) / 100;
				REP(i, fullHealTurns) {
					pendingActions.push("BUILD " + to_string(tower.id) + " TOWER");
				}
			}
			else {
				class Site mine = findSuitableMine();
				if (mine.id != -1) {
					turnAction = "BUILD " + to_string(mine.id) + " MINE";
				}
			}
		}

		// Train all barracks to pump knights
		vector<class Site> trainableBarracks = getTrainableBarracksID();
		REP(i, trainableBarracks.size()) {
			class Site barracks = trainableBarracks[i];
			int barracksTrainCost = UNIT_COST[barracks.barracksUnit];
			if (gold >= barracksTrainCost) {
				turnTrain += " " + to_string(barracks.id);
				gold -= barracksTrainCost;
			}
		}

		// Print Turn Actions
		printf("%s\n", turnAction.c_str());
		printf("%s\n", turnTrain.c_str());
	}

	return 0;
}

//