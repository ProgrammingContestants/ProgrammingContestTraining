#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

int W, H;
char *field;

void read_field()
{
	vector<string> lines;
	string line;
	while (getline(cin, line))
	{
		if (line.empty()) break;
		lines.push_back(line);
	}

	W = (int)lines[0].length();
	H = (int)lines.size();
	field = new char[W * H];

	for (int iy = 0; iy < H; iy++)
	{
		for (int ix = 0; ix < W; ix++)
		{
			field[iy * W + ix] = lines[iy][ix];
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

	cerr << "reading field..." << endl;
	read_field();
	cerr << "read field ended." << endl;

	while (getline(cin, line))
	{
		if (line == "END-OF-INPUT") break;
		cerr << "read metadata: " << line << endl;
	}

	while (getline(cin, line))
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
