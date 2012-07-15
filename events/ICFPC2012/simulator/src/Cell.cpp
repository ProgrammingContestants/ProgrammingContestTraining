#include "../inc/Cell.h"

Cell::Cell(char c) : flooded(false)
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
	}
}

Cell::~Cell()
{
}

Cell::CellType Cell::get_type()
{
	return type;
}

void Cell::set_type(CellType t)
{
	type = t;
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
		case EMPTY:
			return ' ';
	}
}
