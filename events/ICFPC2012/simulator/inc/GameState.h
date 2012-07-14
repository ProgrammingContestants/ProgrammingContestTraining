#ifndef _LAMBDA_GAMESTATE_H
#define _LAMBDA_GAMESTATE_H
class GameState {
	private:
		int remain;
		int collected;
		int status;
		int score;
	public:
		GameState();
		~GameState();
};
#endif
