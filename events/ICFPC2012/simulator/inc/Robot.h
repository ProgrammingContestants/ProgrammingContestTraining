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
		Robot();
		~Robot();

		void init(int _x, int _y, Metadata* md);
		bool move(int dx, int dy);
		bool move(int dx, int dy, bool flooded);
		bool is_dead();
		void destroy();
		void jump(int target_x,int target_y);

		int get_x();
		int get_y();
};
#endif
