#ifndef _LAMBDA_CONDITION_H
#define _LAMBDA_CONDITION_H

#include "Common.h"
#include <string>
using namespace std;

class Condition {
	public:
		enum ConditionType {
			DIGGING,
			ABORTING,
			WINNING,
			LOSING
		};

		Condition();
		~Condition();
		void change(ConditionType ct);

		ConditionType get_type();
		string get_string();

	private:
		ConditionType type;
};
#endif
