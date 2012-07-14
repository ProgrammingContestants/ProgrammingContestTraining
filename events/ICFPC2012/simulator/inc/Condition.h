#ifndef _LAMBDA_CONDITION_H
#define _LAMBDA_CONDITION_H
class Condition {
	private:
	public:
		Condition(ConditionType s);
		~Condition();
		string get_string();

		enum ConditionType {
			DIGGING,
			ABORTING,
			WINNING,
			LOSING
		};
};
#endif
