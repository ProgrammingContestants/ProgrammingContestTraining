#include "../inc/Cell.h"
#include <cassert>

Cell::Cell(char c) : flooded(false), id(UNDEF_ID)
{
	switch (c) {
		case 'R':
			type = ROBOT;
			break;
		case '#':
			type = WALL;
			break;
		case '*':
			type = ROCK;
			break;
		case '\\':
			type = LAMBDA;
			break;
		case 'L':
			type = CLIFT;
			break;
		case 'O':
			type = OLIFT;
			break;
		case '.':
			type = EARTH;
			break;
		case ' ':
			type = EMPTY;
			break;
		case 'W':
			type = BEARD;
			break;
		case '!':
			type = RAZOR;
			break;
		case '@':
			type = HOR;
			break;
		default:
			if('A'<=c&&c<='I'){
				type=TRAMPOLINE;
				id=c;
			}else if('1'<=c&&c<='9'){
				type=TARGET;
				id=c;
			}else{
				assert(0);
			}
	}
}

Cell::~Cell()
{
}

void Cell::flood()
{
	flooded = true;
}

bool Cell::is_flooded()
{
	return flooded;
}

Cell::CellType Cell::get_type()
{
	return type;
}

void Cell::set_type(CellType t)
{
	set_type(t,UNDEF_ID);
}

void Cell::set_type(CellType t, char id)
{
	type = t;
	this->id = id;
}

char Cell::get_char()
{
	switch (type) {
		case ROBOT:
			return 'R';
		case WALL:
			return '#';
		case ROCK:
			return '*';
		case LAMBDA:
			return '\\';
		case CLIFT:
			return 'L';
		case OLIFT:
			return 'O';
		case EARTH:
			return '.';
		case TRAMPOLINE:
			return id;
		case TARGET:
			return id;
		case BEARD:
			return 'W';
		case RAZOR:
			return '!';
		case HOR:
			return '@';
		case EMPTY:
			return ' ';
	}
}


char Cell::get_id(){
	assert(id!=UNDEF_ID);
	return id;
}
