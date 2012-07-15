#ifndef _LAMBDA_ROBOT_H
#define _LAMBDA_ROBOT_H

#include "Metadata.h"
#include "Operation.h"

class Robot {
	private:
		Metadata* metadata;
		int x;
		int y;
		int waterproof;
		int water_life;
		bool dead;
	public:
		Robot(int x, int y, Metadata* md);
		~Robot();
		bool move(int dx, int dy);
		bool move(int dx, int dy, bool flooded);
		bool is_dead();
		void destroy();

		int get_x();
		int get_y();
};
#endif
