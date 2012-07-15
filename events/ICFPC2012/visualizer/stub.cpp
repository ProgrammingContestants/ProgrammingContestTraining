#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

int W, H;
char *field;

void read_field()
{
	string line;
	for (int iy = 0; iy < H; iy++)
	{
		getline(cin, line);
		for (int ix = 0; ix < W; ix++)
		{
			field[iy * W + ix] = line[ix];
		}
	}
}

void print_field()
{
	for (int iy = 0; iy < H; iy++)
	{
		for (int ix = 0; ix < W; ix++)
		{
			cout << field[iy * W + ix];
		}
		cout << endl;
	}
	cout.flush();
}

void print_score()
{
	cout << rand() % 501 << endl;
}

void random_overwrite()
{
	static const char CS[] = { 'R', '#', '*', '\\', 'L', 'O', '.', ' ' };
	for (int iy = 0; iy < H; iy++)
	{
		for (int ix = 0; ix < W; ix++)
		{
			field[iy * W + ix] = CS[rand() % 8];
		}
	}
}

int main()
{
	srand((unsigned int)time(NULL));

	string line;

	getline(cin, line);
	W = atoi(line.c_str());

	getline(cin, line);
	H = atoi(line.c_str());

	field = new char[W * H];
	read_field();

	for (;getline(cin, line);)
	{
		random_overwrite();

		print_field();
		print_score();

		if (line[0] == 'A')
		{
			break;
		}
	}
}
