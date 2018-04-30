/*~~~~~~~~~~~~~~~~~~*
*                  *
*  $DollarAkshay$  *
*                  *
*~~~~~~~~~~~~~~~~~~*/

//https://www.codingame.com/ide/puzzle/chemical-equation-balancing

#include <algorithm>
#include <assert.h>
#include <ctype.h>
#include <deque>
#include <fstream>
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
#include <unordered_map>
#include <vector>

using namespace std;

#define sp system("pause")
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define FORD(i, a, b) for (int i = a; i >= b; --i)
#define REP(i, n) FOR(i, 0, (int)n - 1)
#define DB(format, ...) fprintf(stderr, format, ##__VA_ARGS__)
#define pb(x) push_back(x)
#define mp(a, b) make_pair(a, b)
#define MSX(a, x) memset(a, x, sizeof(a))
#define SORT(a, n) sort(begin(a), begin(a) + n)
#define ll long long
#define pii pair<int, int>
#define MOD 1000000007

class Element {
  public:
	int count;
	string name;

	//Construct an Element from a String
	Element(string s) {
		name = "";
		count = 0;
		bool digitFlag = false;
		REP(i, s.size()) {
			if (isdigit(s[i])) {
				digitFlag = true;
				count = count * 10 + (s[i] - '0');
			}
			else {
				name += s[i];
			}
		}

		if (digitFlag == false) {
			count = 1;
		}
	}

	// Create Element from name and count
	Element(int count, string name) {
		this->count = count;
		this->name = name;
	}

	friend ostream &operator<<(ostream &out, class Element const &e) {
		out << e.name;
		if (e.count > 1) {
			out << e.count;
		}
		return out;
	}

	bool operator<(class Element const &rhs) {
		return name < rhs.name;
	}
};

class Molecule {
  public:
	vector<class Element> elements;

	// Construct a molecule from a string
	Molecule(string s) {
		string elementString = "";
		REP(i, s.size()) {
			if (isupper(s[i]) && elementString.size() > 0) {
				elements.push_back(Element(elementString));
				elementString = "";
			}
			elementString += s[i];
		}
		elements.push_back(Element(elementString));
	}

	friend ostream &operator<<(ostream &out, class Molecule const &m) {
		REP(i, m.elements.size()) {
			class Element e = m.elements[i];
			out << e;
		}
		return out;
	}
};

const int MAX_COEFF = 6;
vector<class Molecule> LHS, RHS;

// Find the element count for an array of molecules
vector<class Element> findElementCount(vector<class Molecule> &eq, vector<int> &coeff) {

	unordered_map<string, int> elemCount;
	REP(i, eq.size()) {
		class Molecule m = eq[i];
		REP(j, m.elements.size()) {
			class Element e = m.elements[j];
			if (elemCount.find(e.name) == elemCount.end()) {
				elemCount[e.name] = e.count * coeff[i];
			}
			else {
				elemCount[e.name] += e.count * coeff[i];
			}
		}
	}

	vector<class Element> res;
	for (auto it = elemCount.begin(); it != elemCount.end(); it++) {
		res.push_back(Element(it->second, it->first));
	}

	sort(res.begin(), res.end());
	return res;
}

// Check whether count of elements on LHS are the same as RHS
bool isBalanced(vector<class Element> &LHS, vector<class Element> &RHS) {

	// This condition should never happen. Just there for fail safe
	if (LHS.size() != RHS.size()) {
		return false;
	}

	REP(i, LHS.size()) {
		if (LHS[i].count != RHS[i].count) {
			return false;
		}
	}

	return true;
}

vector<int> generateCoeff(int seqNumber, int size) {
	vector<int> res;
	REP(i, size) {
		res.pb(1);
	}

	int i = 0;
	while (seqNumber > 0) {
		res[i] = seqNumber % MAX_COEFF + 1;
		seqNumber /= MAX_COEFF;
		i++;
	}

	return res;
}

// Integer power function.
int intPow(int b, int e) {
	if (e == 1) {
		return b;
	}
	else {
		return intPow(b, e - 1) * b;
	}
}

// Helper Function to print vector
void printVector(vector<int> a) {
	REP(i, a.size()) {
		cout << a[i];
		if (i != a.size() - 1) {
			cout << " + ";
		}
	}
}

// Helper Function to print vector
void printElementVector(vector<class Element> a) {
	REP(i, a.size()) {
		cout << a[i];
		if (i != a.size() - 1) {
			cout << " + ";
		}
	}
}

int main() {

	string line;
	bool isLHS = true;

	while (cin >> line) {
		if (line == "+") {
			continue;
		}
		else if (line == "->") {
			isLHS = false;
		}
		else {
			class Molecule m = Molecule(line);
			if (isLHS) {
				LHS.push_back(m);
			}
			else {
				RHS.push_back(m);
			}
		}
	}

	int seqLimitLHS = intPow(MAX_COEFF, LHS.size());
	int seqLimitRHS = intPow(MAX_COEFF, RHS.size());

	vector<int> coeffLHS, coeffRHS;
	bool found = false;

	clock_t start = clock();

	REP(l, seqLimitLHS) {
		coeffLHS = generateCoeff(l, LHS.size());
		vector<class Element> countLHS = findElementCount(LHS, coeffLHS);
		REP(r, seqLimitRHS) {
			coeffRHS = generateCoeff(r, RHS.size());
			vector<class Element> countRHS = findElementCount(RHS, coeffRHS);

			// printVector(coeffLHS);
			// cout << " -> ";
			// printVector(coeffRHS);
			// cout << endl;

			// printElementVector(countLHS);
			// cout << " -> ";
			// printElementVector(countRHS);
			// cout << endl;

			if (isBalanced(countLHS, countRHS)) {
				found = true;
				break;
			}
		}
		if (found) {
			break;
		}
	}

	clock_t end = clock();
	DB("Time Taken : %.6f sec\n", ((double)end - start) / CLOCKS_PER_SEC);

	REP(i, LHS.size()) {
		if (coeffLHS[i] > 1) {
			cout << coeffLHS[i];
		}
		cout << LHS[i];
		if (i != LHS.size() - 1) {
			cout << " + ";
		}
	}

	cout << " -> ";

	REP(i, RHS.size()) {
		if (coeffRHS[i] > 1) {
			cout << coeffRHS[i];
		}
		cout << RHS[i];
		if (i != RHS.size() - 1) {
			cout << " + ";
		}
	}
	cout << endl;

	return 0;
}

//