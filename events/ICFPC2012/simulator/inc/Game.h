#ifndef _LAMBDA_GAME_H
#define _LAMBDA_GAME_H

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
		Metadata* metadata;
		Field* field;
		GameState* state;
		void generate_field(string str);
		vector<Operation> operations;
	public:
		Game(Metadata* md);
		Game(int w, int h, Metadata* md);
		Game(string str, Metadata* md);
		~Game();
		bool move(Operation op);
		bool is_finished();
		void print_game_states();
};
#endif
