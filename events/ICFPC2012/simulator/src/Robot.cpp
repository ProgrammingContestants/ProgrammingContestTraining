#include "../inc/Robot.h"

Robot::Robot(int x, int y, Metadata* md) : x(x), y(y), dead(false), metadata(md)
{
	waterproof = metadata->get_waterproof();
	water_life = waterproof;
}

Robot::~Robot()
{
}

bool Robot::move(int dx, int dy)
{
	x += dx;
	y += dy;
	return true;
}

bool Robot::move(int dx, int dy, bool flooded)
{
	x += dx;
	y += dy;
	if (flooded) {
		if (--water_life == 0) {
			dead = true;
		}
	}
	else {
		water_life = waterproof;
	}
	return true;
}

bool Robot::is_dead()
{
	return dead;
}

void Robot::destroy()
{
	dead = true;
}

int Robot::get_x()
{
	return x;
}

int Robot::get_y()
{
	return y;
}
