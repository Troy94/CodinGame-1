/*~~~~~~~~~~~~~~~~~~*
*                  *
*  $DollarAkshay$  *
*                  *
*~~~~~~~~~~~~~~~~~~*/

//https://www.codingame.com/ide/puzzle/the-bridge-episode-2

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
#define DB(format, ...) fprintf(stderr, format, ##__VA_ARGS__);
#define pb(x) push_back(x)
#define mp(a, b) make_pair(a, b)
#define MSX(a, x) memset(a, x, sizeof(a))
#define SORT(a, n) sort(begin(a), begin(a) + n)
#define ll long long
#define pii pair<int, int>
#define MOD 1000000007

class Bike {
  public:
	int x, y;
	bool active;
	Bike() {
		x = -1;
		y = -1;
		active = -1;
	}
};

class GameState {
  public:
	int totalBikeCount, minBikeCount, laneLength;
	int activeBikeCount, bikeSpeed;
	char lane[4][500];
	vector<class Bike> bikes;

	GameState() {
		totalBikeCount = -1;
		minBikeCount = -1;
		bikes.clear();
	}

	// Initialize Game State
	void init() {
		laneLength = strlen(lane[0]);
		REP(i, totalBikeCount) {
			bikes.push_back(Bike());
		}
	}

	// Every turn calculations
	void turnCalc() {
		activeBikeCount = 0;
		REP(i, totalBikeCount) {
			if (bikes[i].active) {
				activeBikeCount++;
			}
		}
	}

	// Return true if game has been lost
	bool hasLost() {
		if (activeBikeCount < minBikeCount) {
			return true;
		}
		else {
			return false;
		}
	}

	bool hasWon() {
		if (activeBikeCount >= minBikeCount && bikes[0].x >= laneLength - 1) {
			return true;
		}
		else {
			return false;
		}
	}

	bool canGoUp() {
		int minY = 4;
		REP(i, totalBikeCount) {
			class Bike bike = bikes[i];
			if (bike.active) {
				minY = min(minY, bike.y);
			}
		}
		return minY > 0 ? true : false;
	}

	bool canGoDown() {
		int maxY = -1;
		REP(i, totalBikeCount) {
			class Bike bike = bikes[i];
			if (bike.active) {
				maxY = max(maxY, bike.y);
			}
		}
		return maxY < 3 ? true : false;
	}

	// Find the X value of the furthest bike
	int furthestBikeX() {
		int maxX = -1;
		REP(i, totalBikeCount) {
			class Bike bike = bikes[i];
			if (bike.active) {
				maxX = max(maxX, bike.x);
			}
		}
		return maxX;
	}

	// Simulate Wait Action
	void simWait(int dy) {
		REP(i, totalBikeCount) {
			class Bike bike = bikes[i];
			if (bike.active) {
				if (lane[bike.y][bike.x] == '0') {
					bike.active = false;
					activeBikeCount--;
					continue;
				}
				REP(j, bikeSpeed) {
					bike.x = min(laneLength - 1, bike.x + 1);
					if (lane[bike.y][bike.x] == '0' ||
						(lane[bike.y + dy][bike.x] == '0' && j != bikeSpeed - 1)) {
						bike.active = false;
						activeBikeCount--;
						break;
					}
				}
			}
			bikes[i] = bike;
		}
	}

	// Simulate Jump Action
	void simJump() {
		REP(i, totalBikeCount) {
			class Bike bike = bikes[i];
			if (bike.active) {
				bike.x = min(laneLength - 1, bike.x + bikeSpeed);
				if (lane[bike.y][bike.x] == '0') {
					bike.active = false;
					activeBikeCount--;
					break;
				}
			}
			bikes[i] = bike;
		}
	}

	// Simulate Speed Up Action
	void simSpeed() {
		bikeSpeed += 1;
		simWait(0);
	}

	// Simulate Slow Donw Action
	void simSlow() {
		bikeSpeed = max(0, bikeSpeed - 1);
		simWait(0);
	}

	// Simulate Moving Up Lanes
	void simUp() {
		if (canGoUp()) {
			REP(i, totalBikeCount) {
				bikes[i].y--;
			}
			simWait(+1);
		}
		else {
			DB("CANT GO UP\n");
			simWait(0);
		}
	}

	// Simulate Moving Down Lanes
	void simDown() {
		if (canGoDown()) {
			REP(i, totalBikeCount) {
				bikes[i].y++;
			}
			simWait(-1);
		}
		else {
			DB("CANT GO DOWN\n");
			simWait(0);
		}
	}
};

const int TIME_LIMIT = 150;
const int MAX_TURN = 7;

const int LOSS_HEURESTIC_COST = -1000;
const int BIKE_HEURESTIC_COST = 100;

class GameState game;
string bestMove;

int backtrack(int turn) {

	class GameState gameCopy = game;

	if (game.hasLost()) {
		return LOSS_HEURESTIC_COST + turn;
	}

	if (game.hasWon()) {
		return (game.activeBikeCount - game.minBikeCount + 1) * BIKE_HEURESTIC_COST - turn;
	}

	if (turn >= MAX_TURN) {
		return game.furthestBikeX() - game.laneLength;
	}

	int bestVal = -10E6, val;

	// Calculate Speed Move Value
	game.simSpeed();
	val = backtrack(turn + 1);
	if (val > bestVal) {
		bestVal = val;
		if (turn == 0) {
			bestMove = "SPEED";
		}
	}
	if (turn <= 0) {
		DB("%d | SIM SPEED : %d\n", turn, val);
	}
	game = gameCopy;

	// Calculate Slow Move Value
	game.simSlow();
	val = backtrack(turn + 1);
	if (val > bestVal) {
		bestVal = val;
		if (turn == 0) {
			bestMove = "SLOW";
		}
	}
	if (turn <= 0) {
		DB("%d | SIM SLOW : %d\n", turn, val);
	}
	game = gameCopy;

	// Calculate Jump Move Value
	game.simJump();
	val = backtrack(turn + 1);
	if (val > bestVal) {
		bestVal = val;
		if (turn == 0) {
			bestMove = "JUMP";
		}
	}
	if (turn <= 0) {
		DB("%d | SIM JUMP : %d\n", turn, val);
	}
	game = gameCopy;

	// Calculate Up Move Value
	if (game.canGoUp()) {
		game.simUp();
		val = backtrack(turn + 1);
		if (val > bestVal) {
			bestVal = val;
			if (turn == 0) {
				bestMove = "UP";
			}
		}
		if (turn <= 0) {
			DB("%d | SIM UP : %d\n", turn, val);
		}
		game = gameCopy;
	}

	// Calculate Down Move Value
	if (game.canGoDown()) {
		game.simDown();
		val = backtrack(turn + 1);
		if (val > bestVal) {
			bestVal = val;
			if (turn == 0) {
				bestMove = "DOWN";
			}
		}
		if (turn <= 0) {
			DB("%d | SIM DOWN : %d\n", turn, val);
		}
		game = gameCopy;
	}

	return bestVal;
}

int main() {

	scanf("%d %d", &game.totalBikeCount, &game.minBikeCount);
	game.activeBikeCount = game.totalBikeCount;

	REP(i, 4) {
		scanf("%s", game.lane[i]);
	}

	game.init();

	while (true) {
		clock_t start = clock();
		scanf("%d", &game.bikeSpeed);
		REP(i, game.totalBikeCount) {
			scanf("%d %d %d", &game.bikes[i].x, &game.bikes[i].y, &game.bikes[i].active);
			DB("%d %d %d\n", game.bikes[i].x, game.bikes[i].y, game.bikes[i].active);
		}
		game.turnCalc();

		backtrack(0);
		clock_t end = clock();
		DB("Time Taken : %.6f\n", ((double)end - start) / CLOCKS_PER_SEC);

		printf("%s\n", bestMove.c_str());
	}
	return 0;
}

//