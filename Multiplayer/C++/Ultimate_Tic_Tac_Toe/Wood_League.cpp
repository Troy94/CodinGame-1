/*~~~~~~~~~~~~~~~~~~*
*                  *
*  $DollarAkshay$  *
*                  *
*~~~~~~~~~~~~~~~~~~*/

//https://www.codingame.com/ide/puzzle/tic-tac-toe

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
#define DB(format, ...) fprintf(stderr, format, ##__VA_ARGS__)
#define pb(x) push_back(x)
#define mp(a, b) make_pair(a, b)
#define MSX(a, x) memset(a, x, sizeof(a))
#define SORT(a, n) sort(begin(a), begin(a) + n)
#define ll long long
#define pii pair<int, int>
#define MOD 1000000007

class Move {
  public:
	int x, y;

	Move() {
		x = -1;
		y = -1;
	}

	Move(int x, int y) {
		this->x = x;
		this->y = y;
	}

	string toString() {
		return to_string(y) + " " + to_string(x);
	}

	bool operator==(const class Move rhs) const {
		return x == rhs.x && y == rhs.y;
	}

	bool operator<(const class Move rhs) const {
		return (x < rhs.x) || (x == rhs.x && y < rhs.y);
	}
};

class GameState {
  public:
	char player, opponent;
	int turn;
	char board[3][3];

	GameState() {
		MSX(board, '-');
		player = '-';
		opponent = '-';
		turn = 0;
	}

	// Initialize the game state
	void init(class Move move) {
		if (move.y == -1 && move.x == -1) {
			player = 'X';
			opponent = 'O';
		}
		else {
			player = 'O';
			opponent = 'X';
		}
	}

	void printBoard() {
		REP(i, 3) {
			REP(j, 3) {
				DB("%c", board[i][j]);
			}
			DB("\n");
		}
	}

	// Make a move on the board
	void doMove(class Move move, bool isPlayer) {
		if (move.y != -1 && move.x != -1) {
			board[move.y][move.x] = isPlayer ? player : opponent;
		}
	}

	// Undo the move on the board
	void undoMove(class Move move) {
		if (move.y != -1 && move.x != -1) {
			board[move.y][move.x] = '-';
		}
	}

	// Return the number of moves remaining
	int movesLeft() {
		int movesLeft = 0;
		REP(i, 3) {
			REP(j, 3) {
				movesLeft += board[i][j] == '-' ? 1 : 0;
			}
		}
		return movesLeft;
	}

	// Return whether or not a certian playerType has won
	bool hasWon(char tokenType) {

		// Horizontal
		REP(i, 3) {
			if (board[i][0] == board[i][1] &&
				board[i][1] == board[i][2] &&
				board[i][2] == tokenType) {
				return true;
			}
		}

		// Vertical
		REP(i, 3) {
			if (board[0][i] == board[1][i] &&
				board[1][i] == board[2][i] &&
				board[2][i] == tokenType) {
				return true;
			}
		}

		// Diagonal 0,0 - 2,2
		if (board[0][0] == board[1][1] &&
			board[1][1] == board[2][2] &&
			board[2][2] == tokenType) {
			return true;
		}

		// Diagonal 0,2 - 2,0
		if (board[0][2] == board[1][1] &&
			board[1][1] == board[2][0] &&
			board[2][0] == tokenType) {
			return true;
		}

		return false;
	}

	// Return whether or not the game state is a draw
	bool isDraw() {
		return movesLeft() == 0;
	}
};

const int MAX_DEPTH = 10;
const int INF = 1E9;
const int LOSS_HEURESTIC_COST = -1000;
const int WIN_HEURESTIC_COST = 1000;

int nodesEvaluated = 0;
class Move bestMove;
class GameState game;

int minimax(int depth, int alpha, int beta, bool isPlayer) {

	nodesEvaluated++;
	// Evaluation if Leaf Node
	if (game.hasWon(game.player)) {
		return WIN_HEURESTIC_COST - depth;
	}

	if (game.hasWon(game.opponent)) {
		return LOSS_HEURESTIC_COST + depth;
	}

	if (depth >= MAX_DEPTH || game.isDraw() == true) {
		return 0;
	}

	if (isPlayer) {
		int bestVal = -INF;
		REP(i, 3) {
			REP(j, 3) {
				if (game.board[i][j] == '-') {
					class Move move = Move(j, i);
					game.doMove(move, isPlayer);
					int val = minimax(depth + 1, alpha, beta, !isPlayer);
					// Store the move if depth == 0
					if (val > bestVal && depth == 0) {
						bestMove = move;
					}
					if (depth == 0) {
						DB("%s = %d\n", move.toString().c_str(), val);
					}
					bestVal = max(bestVal, val);
					alpha = max(alpha, bestVal);
					game.undoMove(move);
					if (beta <= alpha) {
						break;
					}
				}
			}
		}
		return bestVal;
	}
	else {
		int bestVal = INF;
		REP(i, 3) {
			REP(j, 3) {
				if (game.board[i][j] == '-') {
					class Move move = Move(j, i);
					game.doMove(move, isPlayer);
					int val = minimax(depth + 1, alpha, beta, !isPlayer);
					bestVal = min(bestVal, val);
					beta = min(beta, bestVal);
					game.undoMove(move);
					if (beta <= alpha) {
						break;
					}
				}
			}
		}
		return bestVal;
	}
}

// Reset some variables every turn
void turnReset() {
	nodesEvaluated = 0;
	bestMove = Move();
}

int main() {

	int row, col, moves, _r, _c;

	// 1st Turn
	scanf("%d %d %d", &row, &col, &moves);
	REP(i, moves) {
		scanf("%d %d", &_r, &_c);
	}
	class Move opponentMove = Move(col, row);
	game.init(opponentMove);

	// Make Opponents Move
	game.doMove(opponentMove, false);

	int bestVal = minimax(0, -INF, INF, true);
	game.doMove(bestMove, true);
	printf("%s ", bestMove.toString().c_str());
	printf("|V:%d N:%d|\n", bestVal, nodesEvaluated);

	// Rest of the Turns
	while (true) {
		turnReset();
		scanf("%d %d %d", &row, &col, &moves);

		REP(i, moves) {
			scanf("%d %d", &_r, &_c);
			DB("%d %d\n", _r, _c);
		}
		// Make Opponents Move
		class Move opponentMove = Move(col, row);
		game.doMove(opponentMove, false);
		int bestVal = minimax(0, -INF, INF, true);

		game.doMove(bestMove, true);
		game.printBoard();
		printf("%s ", bestMove.toString().c_str());
		printf("|V:%d N:%d|\n", bestVal, nodesEvaluated);
	}

	return 0;
}

//