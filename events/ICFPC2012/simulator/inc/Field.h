#ifndef _LAMBDA_FIELD_H
#define _LAMBDA_FIELD_H

#include "Common.h"
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

		Robot robot;

		bool used_razor;

		bool move_robot(int dx, int dy, GameState& state, Metadata& metadata);
		void update(GameState& state, Metadata& metadata);
		void flood();
		bool use_razor(GameState& state);

	public:
		Field();
		~Field();

		void init(vector<string> rows, GameState& s, Metadata& metadata);
		int get_width();
		int get_height();
		Cell &get_cell(int x, int y);
		Cell &get_cell_internal(int x, int y);
		int get_water_height();
		string get_string();
		bool operate(Operation op, GameState& state, Metadata& metadata);
		void print();
		Robot& get_robot();
		const int get_steps();
		bool has_used_razor();
};
#endif
