#include "../inc/GameState.h"

GameState::GameState(): remain(0), collected(0), score(0)
{
}

GameState::~GameState()
{
}

void GameState::change_condition(Condition::ConditionType ct)
{
	condition.change(ct);
}

void GameState::collect_lambda()
{
	--remain; ++collected;
	score += 25;
}

void GameState::win()
{
	condition.change(Condition::WINNING);
	score += collected * 50;
}

void GameState::lose()
{
	condition.change(Condition::LOSING);
}

void GameState::drown()
{
	condition.change(Condition::LOSING);
}

void GameState::abort()
{
	condition.change(Condition::ABORTING);
	score += collected * 25;
}

void GameState::decrement_score()
{
	--score;
}

bool GameState::is_finished()
{
	return condition.get_type() != Condition::DIGGING;
}

/* Getters */
int GameState::get_remain()
{
	return remain;
}
int GameState::get_collected()
{
	return collected;
}
Condition GameState::get_condition()
{
	return condition;
}
int GameState::get_score()
{
	return score;
}

string GameState::get_condition_string()
{
	return condition.get_string();
}

void GameState::set_remain(int r)
{
	remain = r;
}
