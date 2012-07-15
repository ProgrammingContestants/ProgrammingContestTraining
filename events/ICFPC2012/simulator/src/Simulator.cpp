#include "../inc/Simulator.h"

Simulator::Simulator()
{
	ostringstream oss;
	string line;
	while(getline(cin,line),line!="END-OF-INPUT"){
		oss<<line<<endl;
	}
	istringstream iss(oss.str());

	game = new Game(iss);
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
		if (t != Operation::UNKNOWN) {
			game->move(t);
			game->print_game_states();
		}
		if (game->is_finished()) {
			break;
		}
		cerr << "input operation character" << endl;
	}
	cerr << "GAME FINISHED" << endl;
	game->print_game_states();
}

Operation::OperationType Simulator::char_to_optype(char c)
{
	switch (c) {
		case 'l':
		case 'L':
		case 'c':
			return Operation::LEFT;

		case 'r':
		case 'R':
		case 'b':
			return Operation::RIGHT;

		case 'u':
		case 'U':
		case 'f':
			return Operation::UP;

		case 'd':
		case 'D':
		case 'v':
			return Operation::DOWN;

		case 'w':
		case 'W':
			return Operation::WAIT;

		case 'a':
		case 'A':
			return Operation::ABORT;

		case 's':
		case 'S':
			return Operation::RAZOR;

		default:
			return Operation::UNKNOWN;
	}
}
