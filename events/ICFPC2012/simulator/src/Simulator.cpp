#include "../inc/Simulator.h"

Simulator::Simulator()
{
	int w, h;
	cin >> w >> h;
	game = new Game(w, h);
}

Simulator::Simulator(bool console)
{
	game = new Game();
}

Simulator::~Simulator()
{
}

void Simulator::run()
{
	char c;
	cerr << "input operation character" << endl;
	while (cin >> c) {
		Operation::OperationType t = char_to_optype(c);
		if (t == Operation::UNKNOWN) {
			continue;
		}

		game->move(t);
		output();
		game->print_game_states();

		if (game->is_finished()) {
			break;
		}
		cerr << "input operation character" << endl;
	}
	cerr << "GAME FINISHED" << endl;
	game->print_game_states();
}

void Simulator::output()
{
	game->print_field();
	/* TODO: extra */
	if (game->is_finished()) {
		cout << "end" << endl;
	} else {
		cout << "next" << endl;
	}
}


Operation::OperationType Simulator::char_to_optype(char c)
{
	switch (c) {
		case 'l':
		case 'L':
		case 'z':
			return Operation::LEFT;

		case 'r':
		case 'R':
		case 'c':
			return Operation::RIGHT;

		case 'u':
		case 'U':
		case 's':
			return Operation::UP;

		case 'd':
		case 'D':
		case 'x':
			return Operation::DOWN;

		case 'w':
		case 'W':
			return Operation::WAIT;

		case 'a':
		case 'A':
			return Operation::ABORT;

		default:
			return Operation::UNKNOWN;
	}
}
