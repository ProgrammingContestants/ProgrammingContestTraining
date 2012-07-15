#ifndef _LAMBDA_OPERATION_H
#define _LAMBDA_OPERATION_H

#include "Common.h"
#include <iostream>
#include <cassert>
using namespace std;

class Operation {
	public:
		enum OperationType {
			LEFT,
			RIGHT,
			UP,
			DOWN,
			WAIT,
			ABORT,
			RAZOR,
			UNKNOWN
		};

		Operation(OperationType t);
		~Operation();
		int get_dx();
		int get_dy();
		char get_char();
		OperationType get_type();

	private:
		OperationType type;
};
#endif
