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
	Point(double x, double y) {
		this->x = (int)round(x);
		this->y = (int)round(y);
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
const int BASE_X_PADDING = 200;

const int BARRACK_COUNT = 2;
const int MINE_COUNT = 3;
const int TOWER_COUNT = 5;
const int INITIAL_TOWER_HEAL = 6;

const int QUEEN_SPEED = 60;
const int COST_ARCHER = 100;
const int COST_GIANT = 140;
const int COST_KNIGHT = 80;

const int TOWER_MAX_HP = 800;
const int TOWER_REPAIR_THRESHOLD = 700;
const int TOWER_CRITICAL_THRESHOLD = 200;

const int EVADE_TOWER_BUILD_DISTANCE = 90;

map<enum class UnitType, int> UNIT_COST = {
	pair<enum class UnitType, int>(UnitType::ARCHER, 100),
	pair<enum class UnitType, int>(UnitType::GIANT, 140),
	pair<enum class UnitType, int>(UnitType::KNIGHT, 80),
	pair<enum class UnitType, int>(UnitType::QUEEN, -1),
};

// Global Variables
int gameTurn = 0;
int siteCount;
int unitCount;
int gold, touchedSite;
int goldIncomeRate;
queue<string> pendingActions;

class Point friendlyBaseCenter;
class Point friendlyBarrackPoint, friendlyMinePoint, friendlyTowerPoint;
class Point enemyBaseCenter;

// Site Variables
vector<class Site> allSites;
vector<class Site> allBuildableSites;
vector<class Site> buildableSites;
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

vector<class Site> baseBuild;
vector<class Site> buildBarracks;
vector<class Site> buildMines;
vector<class Site> buildTowers;

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

string buildSite(class Site site, string structure) {
	return "BUILD " + to_string(site.id) + " " + structure;
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

// Read Site Data from STDIN
void readSiteData() {

	REP(i, siteCount) {
		int id, goldRemaining, maxGoldRate, structure, owner, param1, param2;
		scanf("%d %d %d %d %d %d %d", &id, &goldRemaining, &maxGoldRate, &structure, &owner, &param1, &param2);
		int siteIndex = findIndexOfSiteByID(id);
		class Site &site = allSites[siteIndex];
		site.type = SiteType(structure);
		site.owner = PlayerType(owner);
		if (goldRemaining >= 0) {
			site.goldRemaining = goldRemaining;
		}
		if (maxGoldRate >= 0) {
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

	allBuildableSites.clear();
	buildableSites.clear();
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
			allBuildableSites.pb(site);
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
				allBuildableSites.pb(site);
				buildableSites.pb(site);
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
				allBuildableSites.pb(site);
				buildableSites.pb(site);
			}
		}
		else {
			neutralSites.pb(site);
			allBuildableSites.pb(site);
			buildableSites.pb(site);
		}
	}
}

// Sort all categories of sites based on distance from friendlyQueen
void sortSites() {

	sort(allSites.begin(), allSites.end(), siteCompare);
	sort(buildableSites.begin(), buildableSites.end(), siteCompare);
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
class Site findNearestSite(vector<class Site> array, class Point src, int pos = 0) {

	vector<class Site> res = array;

	sort(res.begin(), res.end(), [&](class Site lhs, class Site rhs) {
		return lhs.pos.distance(src) < rhs.pos.distance(src);
	});

	if (pos < res.size()) {
		return res[pos];
	}
	else {
		return Site();
	}
}

int goldRequiredToTrainBarracks(vector<class Site> barracksArray) {
	int cost = 0;
	REP(i, barracksArray.size()) {
		class Site barrack = friendlyBarracks[i];
		cost += UNIT_COST[barrack.barracksUnit];
	}

	return cost;
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

pair<class Point, class Point> tangentPointsOnACircle(class Point p, class Point c, double r) {

	pair<class Point, class Point> res;

	double angle, angle1, angle2;
	double dist = p.distance(c);

	if (r >= dist) {
		r = dist - 1.0;
	}

	angle1 = asin(r / dist);
	angle2 = atan2(c.y - p.y, c.x - p.x);

	angle = angle2 - angle1;
	res.first = Point(c.x + r * sin(angle), c.y + r * -cos(angle));

	angle = angle1 + angle2;
	res.second = Point(c.x + r * -sin(angle), c.y + r * cos(angle));

	return res;
}

string evade(class Unit nearestEnemy) {

	class Site nearestBuildableSite = buildableSites[0];
	double distFromQueen = friendlyQueen.pos.distance(nearestBuildableSite.pos);
	double distToTowerPoint = friendlyQueen.pos.distance(friendlyTowerPoint);

	if (distFromQueen - nearestBuildableSite.r < EVADE_TOWER_BUILD_DISTANCE) {
		DB("EVADE BUILD TOWER %d\n", nearestBuildableSite.id);
		return buildSite(nearestBuildableSite, "TOWER");
	}
	else if (distToTowerPoint < 200 && friendlyTowers.size() > 0) {
		DB("REPAIRING TOWER %d\n", friendlyTowers[0].id);
		return buildSite(friendlyTowers[0], "TOWER");
	}
	else {
		DB("RUNNING TOWARDS : %d %d\n", friendlyTowerPoint.x, friendlyTowerPoint.y);
		return "MOVE " + to_string(friendlyTowerPoint.x) + " " + to_string(friendlyTowerPoint.y);
	}
}

class Point evade(class Site nearestEnemy) {
	class Point delta = friendlyQueen.pos - nearestEnemy.pos;
	double distFromQueen = nearestEnemy.pos.distance(friendlyQueen.pos);
	delta = delta * (QUEEN_SPEED / distFromQueen);
	return friendlyQueen.pos + delta;
}

bool isEnemyTrainingKnights() {
	REP(i, enemyBarracksKnight.size()) {
		class Site barrack = enemyBarracksKnight[i];
		if (barrack.barracksDelay > 0) {
			return true;
		}
	}
	return false;
}

bool isEnemyKnightsAapproaching() {
	return enemyKnights.size() > 2 ? true : false;
}

bool isQueenInDanger() {

	if (friendlyQueen.hp < 20 && isEnemyTrainingKnights() == true) {
		return true;
	}

	int towersCloseBy = 0;
	int kightsCloseBy = 0;
	int senseDistance = 300 - friendlyQueen.hp * 2 + gameTurn / 4;

	REP(i, enemyTowers.size()) {
		class Site tower = enemyTowers[i];
		if (tower.pos.distance(friendlyQueen.pos) <= tower.towerAttackRange + QUEEN_SPEED + 10) {
			towersCloseBy++;
		}
	}

	if (towersCloseBy > friendlyQueen.hp / 20.0) {
		return true;
	}

	REP(i, enemyKnights.size()) {
		class Unit knight = enemyKnights[i];
		if (knight.pos.distance(friendlyQueen.pos) <= senseDistance) {
			kightsCloseBy++;
		}
	}

	return kightsCloseBy > friendlyQueen.hp / 35.0 ? true : false;
}

// Calculate some global variables
void calculateGlobals() {

	// Calculate the current ammount of gold being generated
	goldIncomeRate = 0;
	REP(i, friendlyMines.size()) {
		goldIncomeRate += friendlyMines[i].mineGoldRate;
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

int healsRequired(class Site tower) {
	return ceil((TOWER_MAX_HP - tower.towerHP) / 100.0);
}

class Site findCriticalTower() {

	class Site res;
	int minHP = TOWER_MAX_HP;
	REP(i, friendlyTowers.size()) {
		class Site tower = friendlyTowers[i];
		if (tower.towerHP <= TOWER_CRITICAL_THRESHOLD && tower.towerHP <= minHP) {
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

bool isMineFeasible(class Site mine) {

	if (mine.goldRemaining >= 10 || mine.goldRemaining < 0) {
		return true;
	}
	else {
		return false;
	}
}

bool isSiteInArray(vector<class Site> array, class Site site) {
	REP(i, array.size()) {
		if (array[i].id == site.id) {
			return true;
		}
	}
	return false;
}

void designBase() {

	int i;

	baseBuild.clear();
	buildMines.clear();
	buildBarracks.clear();
	buildTowers.clear();

	//Calculate Initial 3 Mines :
	i = 0;
	while (buildMines.size() < MINE_COUNT) {
		class Site mine = findNearestSite(allBuildableSites, friendlyMinePoint, i);
		if (mine.id != -1 && isMineFeasible(mine)) {
			baseBuild.pb(mine);
			buildMines.pb(mine);
		}
		else if (mine.id == -1) {
			DB("INSUFFICIENT SITES");
			break;
		}
		i++;
	}

	//Calculate Initial 2 Barracks :
	i = 0;
	while (buildBarracks.size() < BARRACK_COUNT) {
		class Site barrack = findNearestSite(allBuildableSites, friendlyBarrackPoint, i);
		if (barrack.id != -1 && isSiteInArray(baseBuild, barrack) == false) {
			baseBuild.pb(barrack);
			buildBarracks.pb(barrack);
		}
		else if (barrack.id == -1) {
			DB("INSUFFICIENT SITES");
			break;
		}
		i++;
	}

	//Calculate Initial 8 Towers :
	i = 0;
	while (buildTowers.size() < TOWER_COUNT) {
		class Site tower = findNearestSite(allBuildableSites, friendlyTowerPoint, i);
		if (tower.id != -1 && isSiteInArray(baseBuild, tower) == false) {
			baseBuild.pb(tower);
			buildTowers.pb(tower);
		}
		else if (tower.id == -1) {
			DB("INSUFFICIENT SITES");
			break;
		}
		i++;
	}
}

void initialCalculation() {

	// Find out some key points on the map
	if (friendlyQueen.pos.x < MAP_WIDTH / 2) {
		friendlyBaseCenter = Point(BASE_X_PADDING, MAP_HEIGHT / 2);
		friendlyBarrackPoint = Point(650, 250);
		friendlyMinePoint = Point(300, 100);
		friendlyTowerPoint = Point(200, MAP_HEIGHT - 200);
		enemyBaseCenter = enemyQueen.pos;
	}
	else {
		friendlyBaseCenter = Point(MAP_WIDTH - BASE_X_PADDING, MAP_HEIGHT / 2);
		friendlyBarrackPoint = Point(MAP_WIDTH - 650, MAP_HEIGHT - 250);
		friendlyMinePoint = Point(MAP_WIDTH - 300, MAP_HEIGHT - 100);
		friendlyTowerPoint = Point(MAP_WIDTH - 200, 200);
		enemyBaseCenter = enemyQueen.pos;
	}
}

bool canBuildSite(class Site site) {

	REP(i, allBuildableSites.size()) {
		if (allBuildableSites[i].id == site.id) {
			return true;
		}
	}

	return false;
}

class Site findRepairableTower() {
	class Site res;
	int minHP = TOWER_MAX_HP;
	REP(i, friendlyTowers.size()) {
		class Site tower = friendlyTowers[i];
		if (tower.towerHP <= TOWER_REPAIR_THRESHOLD && tower.towerHP <= minHP) {
			res = tower;
			minHP = tower.towerHP;
		}
	}

	return res;
}

// Remove an a site from a site array by comparing ids
// and return whether the operation was successful or not
bool removeSiteFromArray(vector<class Site> &array, class Site site) {
	REP(i, array.size()) {
		if (array[i].id == site.id) {
			array.erase(array.begin() + i);
			return true;
		}
	}
	return false;
}

void debuggingInfo() {
	DB("GAME TURN            : %d\n", gameTurn);
	queue<string> pendingActionsCopy = pendingActions;
	DB("PENDING ACTIONS      :");
	while (pendingActionsCopy.empty() == false) {
		DB(" %s,", pendingActionsCopy.front().c_str());
		pendingActionsCopy.pop();
	}
	DB("\n");

	DB("INITIAL MINES        :");
	REP(i, buildMines.size()) {
		DB(" %d", buildMines[i].id);
	}
	DB("\n");

	DB("INITIAL BARRACKS     :");
	REP(i, buildBarracks.size()) {
		DB(" %d", buildBarracks[i].id);
	}
	DB("\n");

	DB("INITIAL TOWERS       :");
	REP(i, buildTowers.size()) {
		DB(" %d", buildTowers[i].id);
	}
	DB("\n");

	DB("TOUCHING SITE        : %d\n", touchedSite);
	DB("NEAREST NEUTRAL SITE : %d\n", neutralSites[0].id);

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

		if (gameTurn == 0) {
			initialCalculation();
		}

		designBase();

		debuggingInfo();

		// Evade Knights if Queen is in Danger
		if (isQueenInDanger()) {
			DB("DANGER\n");
			turnAction = evade(enemyKnights[0]);
		}

		// If there are any pending actions finish that first
		if (turnAction == "WAIT" && pendingActions.empty() == false) {
			turnAction = pendingActions.front();
			pendingActions.pop();
		}

		// Build Mines
		if (turnAction == "WAIT" && gameTurn < 200 && buildMines.size() > 0 && isEnemyKnightsAapproaching() == false) {
			REP(i, buildMines.size()) {
				class Site mineToBuild = findNearestSite(buildMines, friendlyQueen.pos, i);
				// Check if Mine is already build else build it.
				if (mineToBuild.id != -1 && isSiteInArray(friendlyMines, mineToBuild) == false && canBuildSite(mineToBuild)) {
					turnAction = buildSite(mineToBuild, "MINE");
					if (touchedSite == mineToBuild.id) {
						REP(i, mineToBuild.maxGoldRate - 1) {
							pendingActions.push(buildSite(mineToBuild, "MINE"));
						}
					}
					break;
				}
			}
		}

		// Build barracks
		if (turnAction == "WAIT" && buildBarracks.size() > 0 && isEnemyKnightsAapproaching() == false) {
			REP(i, buildBarracks.size()) {
				class Site barrackToBuild = findNearestSite(buildBarracks, friendlyQueen.pos, i);
				// Check if Barrack is already build else build it.
				if (barrackToBuild.id != -1 && isSiteInArray(friendlyBarracks, barrackToBuild) == false && canBuildSite(barrackToBuild)) {
					turnAction = buildSite(barrackToBuild, "BARRACKS-KNIGHT");
					break;
				}
			}
		}

		// Excessive gold
		// Build barracks
		if (turnAction == "WAIT" && gold >= 300 && friendlyBarracks.size() < 2) {
			REP(i, buildBarracks.size()) {
				class Site barrackToBuild = findNearestSite(allBuildableSites, friendlyQueen.pos, i);
				// Check if Barrack is already build else build it.
				if (barrackToBuild.id != -1) {
					turnAction = buildSite(barrackToBuild, "BARRACKS-KNIGHT");
					break;
				}
			}
		}

		// Repair Critical Towers
		if (turnAction == "WAIT") {
			class Site towerToRepair = findCriticalTower();
			// Repair Tower
			if (towerToRepair.id != -1) {
				turnAction = buildSite(towerToRepair, "TOWER");
				if (touchedSite == towerToRepair.id) {
					REP(i, healsRequired(towerToRepair) - 1) {
						pendingActions.push(buildSite(towerToRepair, "TOWER"));
					}
				}
			}
		}

		// Build Towers
		if (turnAction == "WAIT" && friendlyTowers.size() < TOWER_COUNT) {
			REP(i, buildTowers.size()) {
				class Site towerToBuild = findNearestSite(buildTowers, friendlyQueen.pos, i);
				// Check if Tower is already build else build it.
				if (towerToBuild.id != -1 && isSiteInArray(friendlyTowers, towerToBuild) == false && canBuildSite(towerToBuild)) {
					turnAction = buildSite(towerToBuild, "TOWER");
					if (touchedSite == towerToBuild.id) {
						REP(i, INITIAL_TOWER_HEAL) {
							pendingActions.push(buildSite(towerToBuild, "TOWER"));
						}
					}
					break;
				}
			}
		}

		// Repair Towers
		if (turnAction == "WAIT") {
			class Site towerToRepair = findRepairableTower();
			// Repair Tower
			if (towerToRepair.id != -1) {
				turnAction = buildSite(towerToRepair, "TOWER");
				if (touchedSite == towerToRepair.id) {
					REP(i, healsRequired(towerToRepair) - 1) {
						pendingActions.push(buildSite(towerToRepair, "TOWER"));
					}
				}
			}
		}

		// Build Mines
		if (turnAction == "WAIT" && buildMines.size() > 0 && isEnemyKnightsAapproaching() == false) {
			REP(i, buildMines.size()) {
				class Site mineToBuild = findNearestSite(buildMines, friendlyQueen.pos, i);
				// Check if Mine is already build else build it.
				if (mineToBuild.id != -1 && isSiteInArray(friendlyMines, mineToBuild) == false && canBuildSite(mineToBuild)) {
					turnAction = buildSite(mineToBuild, "MINE");
					if (touchedSite == mineToBuild.id) {
						REP(i, mineToBuild.maxGoldRate - 1) {
							pendingActions.push(buildSite(mineToBuild, "MINE"));
						}
					}
					break;
				}
			}
		}

		// Train all barracks together
		vector<class Site> trainableBarracks = getTrainableBarracksID();
		int requiredGold = goldRequiredToTrainBarracks(trainableBarracks);
		if (trainableBarracks.size() == friendlyBarracks.size() && gold >= requiredGold) {
			REP(i, trainableBarracks.size()) {
				class Site barracks = trainableBarracks[i];
				int barracksTrainCost = UNIT_COST[barracks.barracksUnit];
				if (gold >= barracksTrainCost) {
					turnTrain += " " + to_string(barracks.id);
					gold -= barracksTrainCost;
				}
			}
		}

		// Print Turn Actions
		printf("%s\n", turnAction.c_str());
		printf("%s\n", turnTrain.c_str());
		gameTurn += 2;
	}

	return 0;
}

//