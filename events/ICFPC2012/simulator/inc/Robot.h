#ifndef _LAMBDA_ROBOT_H
#define _LAMBDA_ROBOT_H

#include "Common.h"
#include "Metadata.h"
#include "Operation.h"

class Robot {
	private:
		int x;
		int y;
		int waterproof;
		int water_life;
		bool dead;
	public:
		Robot();
		~Robot();

		void init(int _x, int _y, Metadata& metadata);
		bool move(int dx, int dy);
		bool move(int dx, int dy, bool flooded);
		bool is_dead();
		void destroy();
		bool set_location(int dest_x,int dest_y);
		bool set_location(int dest_x,int dest_y,bool flooded);

		int get_x();
		int get_y();
};
#endif
