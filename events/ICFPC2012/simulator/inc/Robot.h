#ifndef _LAMBDA_ROBOT_H
#define _LAMBDA_ROBOT_H

#include "Operation.h"
class Robot {
	private:
		int x;
		int y;
	public:
		Robot(int x, int y);
		~Robot();
		bool move(Operation op);
};
#endif
