/*~~~~~~~~~~~~~~~~~~*
 *                  *
 * $Dollar Akshay$  *
 *                  *
 *~~~~~~~~~~~~~~~~~~*/

//https://www.codingame.com/ide/148336711054a6e0efd78e43572a33a717f17de

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
#include <bitset>
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
#define DB(s,x) fprintf(stderr,s,x);
#define MS(x,n) memset(x,n,sizeof(x))
#define SORT(a,n) sort(begin(a),begin(a)+n)
#define REV(a,n) reverse(begin(a),begin(a)+n)
#define ll long long
#define pii pair<int,int>
#define MOD 1000000007

vector<int> poly[100];

int findMSB(unsigned int n) {
	
	FORD(i, 31, 0) {
		if (n & 1<<i)
			return i;
	}
	return -1;
}

int polyDivide(unsigned int a, unsigned int b) {

	int res = 0, rem = a;

	while (rem>=b && rem!=0) {
		int ma = findMSB(rem), mb = findMSB(b);
		rem^=b<<(ma-mb);
	}

	return rem;

}

bool checkPrimality(unsigned int n, unsigned int d) {

	FOR(i, 1, d/2) {
		REP(j, poly[i].size()) {
			if (polyDivide(n, poly[i][j])==0)
				return false;
		}
	}
	return true;

}

void generatePrimePolynomials() {

	poly[1].push_back(2);
	poly[1].push_back(3);
	FOR(i, 2, 16) {
		FOR(j, 1<<i, (2<<i)-1) {
			bool prime = checkPrimality(j, i);
			if (prime)
				poly[i].push_back(j);
		}
	}


}

void encrypt(unsigned int a[16], unsigned int b[16], int size) {

	REP(i, size) {
		REP(j, size) {
			b[(i + j) / 32] ^= ( ( a[i/32] >> (i%32)          )  &
								 ( a[j/32 + size/32] >> (j%32))  & 
								 ( 1                          )   ) << ((i+j)%32);
		}
	}

}

void encrypt32(unsigned int a[16], unsigned int b[16]) {

	ll int test = 0;
	REP(i, 32) {
		REP(j, 32) {
			test ^= (ll int)((a[0]>>i) &
					 (a[1]>>j) &
					 (1)) << ((i+j));
			b[(i+j)/32] ^= ( ( a[0]>>i ) &
							 ( a[1]>>j ) &
							 (    1    )  ) << ((i+j)%32) ;
		}
	}

}

int main(){

	generatePrimePolynomials();
	int size=32;
	unsigned int a[16], b[16];

	while (true) {
		REP(i, 2)
			scanf("%x", &a[i]);

		REP(i, 2)
			b[i] = 0;

		encrypt32(a, b);

		REP(i, 2)
			printf("%08x ", b[i]);
		printf("\n\n");
	}

	sp;
	return 0;
}
//