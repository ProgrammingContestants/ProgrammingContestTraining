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
	return move(dx,dy,false);
}

bool Robot::move(int dx, int dy, bool flooded)
{
	return set_location(x+dx,y+dy,flooded);
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

bool Robot::set_location(int dest_x,int dest_y){
	return set_location(dest_x,dest_y,false);
}

bool Robot::set_location(int dest_x,int dest_y,bool flooded){
	x=dest_x;
	y=dest_y;
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

