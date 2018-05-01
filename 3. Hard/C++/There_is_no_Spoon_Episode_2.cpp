/*~~~~~~~~~~~~~~~~~~*
*                  *
*  $DollarAkshay$  *
*                  *
*~~~~~~~~~~~~~~~~~~*/

//https://www.codingame.com/ide/puzzle/there-is-no-spoon-episode-2

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

	string toString() {
		return to_string(x) + " " + to_string(y);
	}

	int toInt() {
		return x * 100 + y;
	}

	inline bool operator<(const class Point &rhs) const {
		return (x < rhs.x) || (x == rhs.x && y < rhs.y);
	}

	inline bool operator==(const class Point &rhs) const {
		return x == rhs.x && y == rhs.y;
	}

	inline bool operator!=(const class Point &rhs) const {
		return x != rhs.x || y != rhs.y;
	}
};

class Link {
  public:
	class Point p1, p2;
	Link() {
		p1 = Point();
		p2 = Point();
	}

	Link(class Point p1, class Point p2) {
		if (p2 < p1) {
			class Point temp = p1;
			p1 = p2;
			p2 = temp;
		}
		this->p1 = p1;
		this->p2 = p2;
	}

	string toString() {
		return p1.toString() + " " + p2.toString();
	}

	bool collidesWith(class Link l) {
		// type = 1 for horizontal, 2 for vertical
		class Point a1 = p1;
		class Point a2 = p2;
		class Point b1 = l.p1;
		class Point b2 = l.p2;
		int aType = a1.y == a2.y ? 1 : 2;
		int bType = b1.y == b2.y ? 1 : 2;

		if (aType == bType) {
			if (a1.y == b1.y &&
				((a1.x > b1.x && a1.x < b2.x) || (a2.x > b1.x && a2.x < b2.x) ||
				 (b1.x > a1.x && b1.x < a2.x) || (b2.x > a1.x && b2.x < a2.x))) {
				return true;
			}
			else if (a1.x == b1.x &&
					 ((a1.y > b1.y && a1.y < b2.y) || (a2.y > b1.y && a2.y < b2.y) ||
					  (b1.y > a1.y && b1.y < a2.y) || (b2.y > a1.y && b2.y < a2.y))) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			// Swap the Points to make a horizontal and b vertical
			if (aType == 2 && bType == 1) {
				class Point c1 = a1, c2 = a2;
				a1 = b1;
				a2 = b2;
				b1 = c1;
				b2 = c2;
			}

			if (a1.y > min(b1.y, b2.y) && a1.y < max(b1.y, b2.y) &&
				b1.x > min(a1.x, a2.x) && b1.x < max(a1.x, a2.x)) {
				return true;
			}
			else {
				return false;
			}
		}
	}

	bool operator==(const class Link &rhs) const {
		return p1 == rhs.p1 && p2 == rhs.p2;
	}

	bool operator<(const class Link &rhs) const {
		return (p1 < rhs.p1) || (p1 == rhs.p1 && p2 < rhs.p2);
	}
};

class GameState {
  public:
	int height, width;

	int board[30][30];
	int linkCount[30][30];
	int linkExists[30][30];

	map<class Link, int> links;

	GameState() {
		height = -1;
		width = -1;
	}

	void parseLine(char line[31], int lineNumber) {
		REP(j, width) {
			board[lineNumber][j] = line[j] == '.' ? 0 : line[j] - '0';
		}
	}

	void init() {
		REP(i, height) {
			REP(j, width) {
				linkExists[i][j] = 0;
				linkCount[i][j] = 0;
			}
		}
	}

	bool hasWon() {
		REP(i, height) {
			REP(j, width) {
				if (linkCount[i][j] != board[i][j]) {
					return false;
				}
			}
		}
		return true;
	}

	vector<int> getNeighbourValuesSorted(class Point p) {
		vector<int> res;

		// Check Up
		FORD(i, p.y - 1, 0) {
			if (board[i][p.x] > 0) {
				if (linkCount[i][p.x] < board[i][p.x]) {
					res.pb(board[i][p.x]);
				}
				break;
			}
		}

		// Check Down
		FOR(i, p.y + 1, height - 1) {
			if (board[i][p.x] > 0) {
				if (linkCount[i][p.x] < board[i][p.x]) {
					res.pb(board[i][p.x]);
				}
				break;
			}
		}

		// Check Left
		FORD(i, p.x - 1, 0) {
			if (board[p.y][i] > 0) {
				if (linkCount[p.y][i] < board[p.y][i]) {
					res.pb(board[p.y][i]);
				}
				break;
			}
		}

		// Check Right
		FOR(i, p.x + 1, width - 1) {
			if (board[p.y][i] > 0) {
				if (linkCount[i][p.x] < board[p.y][i]) {
					res.pb(board[p.y][i]);
				}
				break;
			}
		}

		SORT(res, res.size());

		return res;
	}

	// Find the number of immediate neighbours in all 4 directions
	int totalNeighbourCount(class Point p) {

		int res = 0;

		// Check Up
		FORD(i, p.y - 1, 0) {
			if (board[i][p.x] > 0) {
				res++;
				break;
			}
		}

		// Check Down
		FOR(i, p.y + 1, height - 1) {
			if (board[i][p.x] > 0) {
				res++;
				break;
			}
		}

		// Check Left
		FORD(i, p.x - 1, 0) {
			if (board[p.y][i] > 0) {
				res++;
				break;
			}
		}

		// Check Right
		FOR(i, p.x + 1, width - 1) {
			if (board[p.y][i] > 0) {
				res++;
				break;
			}
		}

		return res;
	}

	// Find the number of immediate neighbours in all 4 directions that can be connected to
	int neighbourCount(class Point p) {

		int res = 0;

		// Check Up
		FORD(i, p.y - 1, 0) {
			if (board[i][p.x] > 0) {
				class Link l = Link(p, Point(p.x, i));
				res += linkCount[i][p.x] < board[i][p.x] && (links.find(l) == links.end() || links[l] < 2) ? 1 : 0;
				break;
			}
		}

		// Check Down
		FOR(i, p.y + 1, height - 1) {
			if (board[i][p.x] > 0) {
				class Link l = Link(p, Point(p.x, i));
				res += linkCount[i][p.x] < board[i][p.x] && (links.find(l) == links.end() || links[l] < 2) ? 1 : 0;
				break;
			}
		}

		// Check Left
		FORD(i, p.x - 1, 0) {
			if (board[p.y][i] > 0) {
				class Link l = Link(p, Point(i, p.y));
				res += linkCount[p.y][i] < board[p.y][i] && (links.find(l) == links.end() || links[l] < 2) ? 1 : 0;
				break;
			}
		}

		// Check Right
		FOR(i, p.x + 1, width - 1) {
			if (board[p.y][i] > 0) {
				class Link l = Link(p, Point(i, p.y));
				res += linkCount[p.y][i] < board[p.y][i] && (links.find(l) == links.end() || links[l] < 2) ? 1 : 0;
				break;
			}
		}

		return res;
	}

	// Find the number of links available in neighbours in all 4 directions
	int neighbourLinkCount(class Point p) {

		int res = 0;
		// DB("%s | ", p.toString().c_str());

		// Check Up
		FORD(i, p.y - 1, 0) {
			if (board[i][p.x] > 0) {
				class Link l = Link(p, Point(p.x, i));
				if (links.find(l) != links.end()) {
					res += min(board[i][p.x] - linkCount[i][p.x], 2 - links[l]);
				}
				else {
					res += min(board[i][p.x] - linkCount[i][p.x], 2);
				}
				break;
			}
		}
		// DB("U %d | ", res);

		// Check Down
		FOR(i, p.y + 1, height - 1) {
			if (board[i][p.x] > 0) {
				class Link l = Link(p, Point(p.x, i));
				if (links.find(l) != links.end()) {
					res += min(board[i][p.x] - linkCount[i][p.x], 2 - links[l]);
				}
				else {
					res += min(board[i][p.x] - linkCount[i][p.x], 2);
				}
				break;
			}
		}
		// DB("D %d | ", res);

		// Check Left
		FORD(i, p.x - 1, 0) {
			if (board[p.y][i] > 0) {
				class Link l = Link(p, Point(i, p.y));
				if (links.find(l) != links.end()) {
					res += min(board[p.y][i] - linkCount[p.y][i], 2 - links[l]);
				}
				else {
					res += min(board[p.y][i] - linkCount[p.y][i], 2);
				}
				break;
			}
		}
		// DB("L %d | ", res);

		// Check Right
		FOR(i, p.x + 1, width - 1) {
			if (board[p.y][i] > 0) {
				class Link l = Link(p, Point(i, p.y));
				if (links.find(l) != links.end()) {
					res += min(board[p.y][i] - linkCount[p.y][i], 2 - links[l]);
				}
				else {
					res += min(board[p.y][i] - linkCount[p.y][i], 2);
				}
				break;
			}
		}
		// DB("R %d\n", res);

		return res;
	}

	// Find the number of links available in neighbours in all 4 directions
	class Link findNeighbourLink(class Point p, bool firstLink) {

		// Check Up
		FORD(i, p.y - 1, 0) {
			if (board[i][p.x] > 0) {
				class Point node = Point(p.x, i);
				class Link l = Link(p, node);
				int linksToNode = links.find(l) == links.end() ? 0 : links[l];
				if (firstLink && linkCount[node.y][node.x] + 1 < board[node.y][node.x] && linksToNode == 0) {
					return l;
				}
				else if (!firstLink && linkCount[node.y][node.x] < board[node.y][node.x] && linksToNode < 2) {
					return l;
				}
				break;
			}
		}

		// Check Down
		FOR(i, p.y + 1, height - 1) {
			if (board[i][p.x] > 0) {
				class Point node = Point(p.x, i);
				class Link l = Link(p, node);
				int linksToNode = links.find(l) == links.end() ? 0 : links[l];
				if (firstLink && linkCount[node.y][node.x] + 1 < board[node.y][node.x] && linksToNode == 0) {
					return l;
				}
				else if (!firstLink && linkCount[node.y][node.x] < board[node.y][node.x] && linksToNode < 2) {
					return l;
				}
				break;
			}
		}

		// Check Left
		FORD(i, p.x - 1, 0) {
			if (board[p.y][i] > 0) {
				class Point node = Point(i, p.y);
				class Link l = Link(p, node);
				int linksToNode = links.find(l) == links.end() ? 0 : links[l];
				if (firstLink && linkCount[node.y][node.x] + 1 < board[node.y][node.x] && linksToNode == 0) {
					return l;
				}
				else if (!firstLink && linkCount[node.y][node.x] < board[node.y][node.x] && linksToNode < 2) {
					return l;
				}
				break;
			}
		}

		// Check Right
		FOR(i, p.x + 1, width - 1) {
			if (board[p.y][i] > 0) {
				class Point node = Point(i, p.y);
				class Link l = Link(p, node);
				int linksToNode = links.find(l) == links.end() ? 0 : links[l];
				if (firstLink && linkCount[node.y][node.x] + 1 < board[node.y][node.x] && linksToNode == 0) {
					return l;
				}
				else if (!firstLink && linkCount[node.y][node.x] < board[node.y][node.x] && linksToNode < 2) {
					return l;
				}
				break;
			}
		}

		DB("ERR : NO LINK FOUND\n");

		return Link();
	}

	// Find the a special link whne node is 1
	class Link findSpecialLink(class Point p) {

		// Check Up
		FORD(i, p.y - 1, 0) {
			if (board[i][p.x] > 0) {
				class Point node = Point(p.x, i);
				class Link l = Link(p, node);
				if (board[i][p.x] > 1) {
					return l;
				}
				break;
			}
		}

		// Check Down
		FOR(i, p.y + 1, height - 1) {
			if (board[i][p.x] > 0) {
				class Point node = Point(p.x, i);
				class Link l = Link(p, node);
				if (board[i][p.x] > 1) {
					return l;
				}
				break;
			}
		}

		// Check Left
		FORD(i, p.x - 1, 0) {
			if (board[p.y][i] > 0) {
				class Point node = Point(i, p.y);
				class Link l = Link(p, node);
				if (board[p.y][i] > 1) {
					return l;
				}
				break;
			}
		}

		// Check Right
		FOR(i, p.x + 1, width - 1) {
			if (board[p.y][i] > 0) {
				class Point node = Point(i, p.y);
				class Link l = Link(p, node);
				if (board[p.y][i] > 1) {
					return l;
				}
				break;
			}
		}

		DB("ERR : NO LINK FOUND\n");

		return Link();
	}

	// Required Link count for a node
	int
	requiredLinkCount(class Point p) {
		return board[p.y][p.x] - linkCount[p.y][p.x];
	}

	// Check if all the links form a single connected graph
	bool isSingleComponent() {

		map<class Point, vector<class Point>> graph;
		map<class Point, bool> visited;

		for (auto it = links.begin(); it != links.end(); it++) {
			class Link link = it->first;
			graph[link.p1].push_back(link.p2);
			graph[link.p2].push_back(link.p1);
			visited[link.p1] = false;
			visited[link.p2] = false;
		}

		/// BFS
		queue<class Point> q;
		class Point start = visited.begin()->first;
		q.push(start);
		visited[start] = true;

		while (q.empty() == false) {
			class Point p = q.front();
			q.pop();
			// Iterate through all neighbours
			vector<class Point> neighbours = graph[p];
			REP(i, neighbours.size()) {
				class Point next = neighbours[i];
				if (visited[next] == false) {
					q.push(next);
					visited[next] = true;
				}
			}
		}

		// Check if there are any unvisited nodes
		for (auto it = visited.begin(); it != visited.end(); it++) {
			if (it->second == 0) {
				return false;
			}
		}

		return true;
	}

	// Check if you can still build a single component
	bool canStillBuildSingleComponent() {

		map<class Point, vector<class Point>> graph;
		map<class Point, int> visited;
		set<class Point> rootNodes;

		for (auto it = links.begin(); it != links.end(); it++) {
			class Link link = it->first;
			graph[link.p1].push_back(link.p2);
			graph[link.p2].push_back(link.p1);
			visited[link.p1] = 0;
			visited[link.p2] = 0;

			if (board[link.p1.y][link.p1.x] == linkCount[link.p1.y][link.p1.x]) {
				rootNodes.insert(link.p1);
			}

			if (board[link.p2.y][link.p2.x] == linkCount[link.p2.y][link.p2.x]) {
				rootNodes.insert(link.p2);
			}
		}

		int k = 0;
		for (auto it = rootNodes.begin(); it != rootNodes.end(); it++) {
			k++;
			/// BFS
			queue<class Point> q;
			class Point start = *it;
			// DB("ROOT = %s | ", start.toString().c_str());
			q.push(start);
			visited[start] = k;
			bool foundOpening = false;

			while (q.empty() == false && foundOpening == false) {
				class Point p = q.front();
				q.pop();
				// Iterate through all neighbours
				vector<class Point> neighbours = graph[p];
				REP(i, neighbours.size()) {
					class Point next = neighbours[i];
					if (visited[next] == 0 || visited[next] != k) {
						q.push(next);
						visited[next] = k;
						if (board[next.y][next.x] - linkCount[next.y][next.x] > 0) {
							foundOpening = true;
							// DB("Found opening @ %s | %d %d\n", next.toString().c_str(), board[next.y][next.x], linkCount[next.y][next.x]);
							break;
						}
					}
				}
			}

			if (foundOpening == false) {
				// DB("Did not find opening\n");
				return false;
			}
		}

		return true;
	}

	void printMatrix(int a[30][30]) {
		REP(i, height) {
			REP(j, width) {
				DB("%d ", a[i][j]);
			}
			DB("\n");
		}
	}

	// Add a link
	bool addLink(class Link link, bool checks) {

		// Perform checks only if variable is true
		if (checks) {
			// If there already exists 2 similiar links dont add it
			if (links.find(link) != links.end()) {
				if (links[link] >= 2) {
					//DB("CHECK : %s | 2 Links already Exist\n", link.toString().c_str());
					return false;
				}
			}

			// Don't add the link if it collides with anyother link
			for (auto it = links.begin(); it != links.end(); it++) {
				class Link existingLink = it->first;
				if (link.collidesWith(existingLink)) {
					//DB("CHECK : %s collides with %s\n", link.toString().c_str(), existingLink.toString().c_str());
					return false;
				}
			}
		}

		links[link] = links.find(link) != links.end() ? links[link] + 1 : 1;
		linkCount[link.p1.y][link.p1.x]++;
		linkCount[link.p2.y][link.p2.x]++;

		if (linkCount[link.p1.y][link.p1.x] == board[link.p1.y][link.p1.x] &&
			linkCount[link.p2.y][link.p2.x] == board[link.p2.y][link.p2.x] &&
			checks && hasWon() == false && canStillBuildSingleComponent() == false) {
			removeLink(link);
			return false;
		}

		// DB("Added Link : %s\n", link.toString().c_str());
		return true;
	}

	bool removeLink(class Link link) {

		if (links.find(link) != links.end()) {
			links[link]--;
			if (links[link] == 0) {
				links.erase(link);
			}

			linkCount[link.p1.y][link.p1.x]--;
			linkCount[link.p2.y][link.p2.x]--;
			//DB("Removed Link : %s\n", link.toString().c_str());
			return true;
		}
		else {
			DB("ERR : Link not found\n");
			return false;
		}
	}

	// Return whether all the link counts are satisfied
	bool hasEnded() {
		REP(i, height) {
			REP(j, width) {
				if (linkCount[i][j] != board[i][j]) {
					return false;
				}
			}
		}
		return true;
	}

	// Return whether or not a game has been lost
	bool hasLost() {

		// Check if link count for a particular node excedes
		REP(i, height) {
			REP(j, width) {
				class Point p = Point(j, i);
				int req = requiredLinkCount(p);
				int avail = neighbourLinkCount(p);
				if (req < 0 || avail < req) {
					//DB("LOSS DUE TO Insufficient Nodes | R/A = %d %d\n", req, avail);
					return true;
				}
			}
		}

		if (hasEnded() && isSingleComponent() == false) {
			//DB("LOSS DUE TO MULTPLE COMPONENTS\n");
			return true;
		}

		return false;
	}
};

const int MAX_DEPTH = 3;

const int LOSS_HEURESTIC_COST = -1000;
const int WIN_HEURESTIC_COST = 1000;

class GameState game;
class Link gameMove;
int gameTurn = 0;

int backtrack(int depth) {

	if (game.hasLost()) {
		return LOSS_HEURESTIC_COST;
	}

	if (game.hasWon()) {
		return WIN_HEURESTIC_COST;
	}

	if (depth >= MAX_DEPTH) {
		return 0;
	}

	int bestVal = -1E6;

	REP(i, game.height) {
		REP(j, game.width) {
			class Point p = Point(j, i);
			int req = game.requiredLinkCount(p);
			if (req > 0) {
				int avail = game.neighbourLinkCount(p);
				int neigh = game.neighbourCount(p);
				//DB("%s | R/A/N = %d %d %d\n", p.toString().c_str(), req, avail, neigh);
				class Link link = game.findNeighbourLink(p, false);
				bool success = game.addLink(link, true);
				if (success) {
					int val = backtrack(depth + 1);
					if (val > bestVal) {
						bestVal = val;
						if (depth <= 0) {
							gameMove = link;
						}
					}
					if (depth <= 0) {
						DB("%d | %s | Val = %d\n", depth, link.toString().c_str(), val);
					}
					game.removeLink(link);
				}
				else {
					//DB("WARN : Link cant be added | %s\n", link.toString().c_str());
				}
			}
		}
	}

	return bestVal;
}

bool findObviousNodes() {

	// Nodes that require all links around it
	REP(i, game.height) {
		REP(j, game.width) {
			class Point p = Point(j, i);
			if (game.board[i][j] > 0) {
				int req = game.requiredLinkCount(p);
				int avail = game.neighbourLinkCount(p);
				int neigh = game.neighbourCount(p);
				//DB("%s | R/A/N = %d %d %d\n", p.toString().c_str(), req, avail, neigh);
				if (req > 0 && req == avail) {
					class Link link = game.findNeighbourLink(p, false);
					gameMove = link;
					DB("All Occupied Link\n");
					return true;
				}
			}
		}
	}

	// Nodes that require atleast 1 node around it
	REP(i, game.height) {
		REP(j, game.width) {
			class Point p = Point(j, i);
			if (game.board[i][j] > 0) {
				int req = game.requiredLinkCount(p);
				int avail = game.neighbourLinkCount(p);
				int neigh = game.neighbourCount(p);
				// DB("%s | R/A/N = %d %d %d\n", p.toString().c_str(), req, avail, neigh);
				if (req > 0 && req == avail - 1 && avail > neigh) {
					class Link link = game.findNeighbourLink(p, true);
					gameMove = link;
					DB("One Each Link\n");
					return true;
				}
			}
		}
	}

	// Special Cases for Nodes with 1
	REP(i, game.height) {
		REP(j, game.width) {
			class Point p = Point(j, i);
			if (game.board[i][j] == 1) {
				int req = game.requiredLinkCount(p);
				int avail = game.neighbourLinkCount(p);
				int neigh = game.neighbourCount(p);
				vector<int> neighVal = game.getNeighbourValuesSorted(p);
				// DB("%s | R/A/N = %d %d %d\n", p.toString().c_str(), req, avail, neigh);
				if (req > 0 && neigh > 1 && neighVal[neighVal.size() - 2] == 1) {
					class Link link = game.findSpecialLink(p);
					gameMove = link;
					DB("Special One Case : ");
					REP(i, neighVal.size()) {
						DB("%d ", neighVal[i]);
					}
					DB("\n");
					return true;
				}
			}
		}
	}

	return false;
}

int main() {

	scanf("%d %d", &game.width, &game.height);
	DB("W X H = %d X %d\n", game.width, game.height);

	REP(i, game.height) {
		char line[31];
		scanf("%s", line);
		game.parseLine(line, i);
		DB("%s\n", line);
	}

	game.init();

	while (true) {
		gameMove = Link();
		if (findObviousNodes() == false) {
			backtrack(0);
		}

		if (gameMove == Link()) {
			break;
		}

		game.addLink(gameMove, false);
		printf("%s 1\n", gameMove.toString().c_str());
		DB("%s | END TURN\n\n", gameMove.toString().c_str());
		gameTurn++;
	}

	return 0;
}

//