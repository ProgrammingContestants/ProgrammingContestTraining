#include "../inc/Robot.h"

Robot::Robot()
{
}

Robot::~Robot()
{
}

void Robot::init(int _x, int _y, Metadata& metadata)
{
	x = _x;
	y = _y;
	dead = false;

	waterproof = metadata.get_waterproof();
	water_life = waterproof;
}

bool Robot::move(int dx, int dy)
{
	x += dx;
	y += dy;
	return true;
}

bool Robot::breathe(bool flooded)
{
	if (flooded) {
		if (water_life-- == 0) {
			return false;
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
