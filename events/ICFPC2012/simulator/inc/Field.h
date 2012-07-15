#ifndef _LAMBDA_FIELD_H
#define _LAMBDA_FIELD_H

#include "Metadata.h"
#include "Cell.h"
#include "Operation.h"
#include "GameState.h"
#include "Robot.h"

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Field
{
	private:
		int steps;
		int flooding;
		int water;

		int width;
		int height;
		vector<Cell> cells;

		Robot rob;

		bool move_robot(int dx, int dy, GameState& state);
		void update(GameState& state);
		void flood();

	public:
		Field();
		~Field();

		void init(vector<string> rows, GameState& s, Metadata& metadata);
		int get_width();
		int get_height();
		Cell get_cell(int x, int y);
		string get_string();
		void operate(Operation op, GameState& state);
		void print();
};
#endif
