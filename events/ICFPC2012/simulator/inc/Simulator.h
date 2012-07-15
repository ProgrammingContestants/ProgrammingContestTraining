#ifndef _LAMBDA_SIMULATOR_H
#define _LAMBDA_SIMULATOR_H

#include "Game.h"
#include "Operation.h"

class Simulator {
	private:
		Game* game;

		Operation::OperationType char_to_optype(char c);
		
	public:
		Simulator();
		~Simulator();
		void run();
};
#endif
