/* HEADER */
using namespace std;/*{{{*/
#define DEBUG_ON
#define CONDITION true

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

#define EACH(c,it) for(__typeof((c).begin()) it=(c).begin(); it!=(c).end(); ++it)

#ifdef DEBUG_ON
	#define dprt(fmt, ...) if (CONDITION) fprintf(stderr, fmt, __VA_ARGS__)
#else
	#define cerr if(0) cerr
	#define dprt(fmt, ...)
#endif
/*}}}*/
/* HEADER END */

/* Variables *//*{{{*/
struct pos {
	int x, y;
};
pos rob;
vector<string> field;
int height;
int width;

int score;
int remain;
int collected;
bool abort_flag;
bool winning;
bool losing;

vector<char> operations;
/*}}}*/

void init ()/*{{{*/
{
	score = 0;
	remain = 0;
	collected = 0;
	abort_flag = false;
	winning = false;
	losing = false;
	operations.clear();

	// find robot, lambda
	for (int i = 0; i < height; ++i) {
		 for (int j = 0; j < width; ++j) {
			if (field[i][j] == 'R') {
				rob.y = i;
				rob.x = j;
			}
			else if (field[i][j] == '\\') {
				++remain;
			}
		}
	}
}/*}}}*/

void show_field ()/*{{{*/
{
	EACH (field, row) {
		cout << (*row) << endl;
	}
}/*}}}*/

void input_field ()/*{{{*/
{
	width = 0;
	string row;
	while (getline(cin, row), row != "") {
		width = max(width, (int)row.length());
		field.push_back(row);
	}
	EACH (field, row) {
		int len = (*row).length();
		for (int i = len; i < width; ++i) {
			(*row) += " ";
		}
	}
	height = field.size();
}/*}}}*/

void update ()/*{{{*/
{
	vector<string> old = field;
	for (int i = height - 1; i >= 0; --i) {
		 for (int j = 0; j < width; ++j) {
			if (old[i][j] == '*') {
				if (i + 1 < height && old[i+1][j] == ' ') {
					field[i][j] = ' ';
					field[i+1][j] = '*';
				}
				else if (i + 1 < height && old[i+1][j] == '*') {
					if (j + 1 < width && old[i][j+1] == ' ' && old[i+1][j+1] == ' ') {
						/* Fall Right */
						field[i][j] = ' ';
						field[i+1][j+1] = '*';
					}
					else if (j - 1 >= 0 && old[i][j-1] == ' ' && old[i+1][j-1] == ' ') {
						/* Fall Left */
						field[i][j] = ' ';
						field[i+1][j-1] = '*';
					}
				}
				else if (i + 1 < height && old[i+1][j] == '\\') {
					if (j + 1 < width && old[i][j+1] == ' ' && old[i+1][j+1] == ' ') {
						/* Fall Right */
						field[i][j] = ' ';
						field[i+1][j+1] = '*';
					}
				}
			}
			if (old[i][j] == 'L' && remain == 0) {
				field[i][j] = 'O';
			}
		}
	}
	if (rob.y - 1 >= 0 && old[rob.y-1][rob.x] != '*' && field[rob.y-1][rob.x] == '*') {
		cerr << "LOSE!" << endl;
		losing = true;
	}
}/*}}}*/

void move (char c)/*{{{*/
{
	--score;

	pos from = rob;
	pos to = rob;
	switch (c) {
		case 'l':
		case 'L':
		case 'z':
			operations.push_back('L');
			--to.x;
			break;
		case 'r':
		case 'R':
		case 'c':
			operations.push_back('R');
			++to.x;
			break;
		case 'u':
		case 'U':
		case 's':
			operations.push_back('U');
			--to.y;
			break;
		case 'd':
		case 'D':
		case 'x':
			operations.push_back('D');
			++to.y;
			break;
		case 'w':
		case 'W':
			operations.push_back('W');
			return;
		case 'a':
		case 'A':
			operations.push_back('A');
			abort_flag = true;
			++score; /* (restore) */
			return;
	}

	int dx = to.x - from.x;
	switch (field[to.y][to.x]) {
		case ' ':
			break;
		case '.':
			break;
		case '\\':
			--remain;
			++collected;
			score += 25;
			break;
		case 'O':
			winning = true;
			break;

		case '#':
		case 'L':
			return;

		case '*':
			if (dx == 0) {
				return;
			} else {
				if (field[to.y][to.x + dx] == ' ') {
					field[to.y][to.x + dx] = '*';
				} else {
					return;
				}
			}
			break;
		default:
			break;
	}
	field[from.y][from.x] = ' ';
	field[to.y][to.x] = 'R';
	rob.y = to.y; rob.x = to.x;
}/*}}}*/

int main (int argc, char const* argv[])/*{{{*/
{
	cerr << "input field (end with empty line)" << endl;
	input_field();
	vector<string> save = field;

	char c;
	do {
		field = save;
		init();
		while (true) {
			show_field();
			dprt("robot (%d, %d)\n", rob.y, rob.x);
			cerr << "score: " << score << ", remain: " << remain << ", collected: " << collected << endl;
			cerr << "l: left, r: right, u: up, d: down, w: wait, a: abort, (or key \"zsxc\" to move)" << endl;
			cin >> c;
			move(c);
			update();
			if (abort_flag || winning || losing) {
				break;
			}
		}
		if (winning) {
			score += collected * 50;
		} else if (abort_flag) {
			score += collected * 25;
		}

		show_field();
		cerr << "SCORE: " << score << endl;
		cerr << "OPERATION: ";
		EACH (operations, op) {
			cerr << (*op);
		}
		cerr << endl;
	} while (cerr << "q: exit, else: try again" << endl, cin >> c, c != 'q');
	return 0;
}/*}}}*/
