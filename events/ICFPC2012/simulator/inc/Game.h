#ifndef _LAMBDA_GAME_H
#define _LAMBDA_GAME_H

#include "Field.h"

#include <string>

class Game {
	private:
		Field field;
		void generate_field(string str);
	public:
		Game();
		Game(string str);
		~Game();
};
#endif
