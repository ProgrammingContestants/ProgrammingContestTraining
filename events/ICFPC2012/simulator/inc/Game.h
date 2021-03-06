#ifndef _LAMBDA_GAME_H
#define _LAMBDA_GAME_H

#include "Common.h"
#include "Metadata.h"
#include "Field.h"
#include "Operation.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Game {
	private:
		Metadata metadata;
		Field field;
		GameState state;
		void generate_field(string str);
		vector<Operation> operations;
	public:
		Game(istream &in);
		~Game();
		bool move(Operation op);
		bool is_finished();
		void print_game_states();
		string get_operations();
		void print_field();

		Field& get_field();
		GameState& get_game_state();
		Metadata& get_metadata();
		int get_water_height();
		int get_robot_water_life();

		// for test
		GameState& moves(string commands);
};
#endif
