#ifndef _LAMBDA_GAMESTATE_H
#define _LAMBDA_GAMESTATE_H

#include "Common.h"
#include "Condition.h"

class GameState {
	private:
		int remain;
		int collected;
		Condition condition;
		int score;
	public:
		GameState();
		~GameState();
		void change_condition(Condition::ConditionType ct);
		void collect_lambda();
		void win();
		void lose();
		void abort();
		void decrement_score();
		bool is_finished();

		int get_remain();
		void set_remain(int r);
		int get_collected();
		Condition get_condition();
		int get_score();
		string get_condition_string();
};
#endif
