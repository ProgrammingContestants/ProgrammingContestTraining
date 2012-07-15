#include "../inc/Operation.h"

Operation::Operation(OperationType t) : type(t)
{
}

Operation::~Operation()
{
}

int Operation::get_dx()
{
	switch (type) {
		case LEFT:
			return -1;
		case RIGHT:
			return 1;
		default:
			return 0;
	}
}

int Operation::get_dy()
{
	switch (type) {
		case UP:
			return -1;
		case DOWN:
			return 1;
		default:
			return 0;
	}
}

char Operation::get_char()
{
	switch (type) {
		case LEFT:
			return 'L';
		case RIGHT:
			return 'R';
		case UP:
			return 'U';
		case DOWN:
			return 'D';
		case WAIT:
			return 'W';
		case ABORT:
			return 'A';
		case RAZOR:
			return 'S';
		default:
			assert(0);
	}
}

Operation::OperationType Operation::get_type()
{
	return type;
}
