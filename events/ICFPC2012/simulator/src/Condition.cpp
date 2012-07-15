#include "../inc/Condition.h"

Condition::Condition()
{
	type = DIGGING;
}

Condition::~Condition()
{
}

void Condition::change(ConditionType ct)
{
	type = ct;
}

Condition::ConditionType Condition::get_type()
{
	return type;
}

string Condition::get_string()
{
	switch(type) {
		case DIGGING:
			return "DIGGING";
		case ABORTING:
			return "ABORTING";
		case WINNING:
			return "WINNING";
		case LOSING:
			return "LOSING";
	}
}
