#include "../inc/Game.h"

Game::Game(istream &in)
{
	int width = 0;
	vector<string> v;
	string str, row;
	while (getline(in, row), row != "") {
		width = max(width, (int)row.length());
		v.push_back(row);
	}
	for(vector<string>::iterator  it=(v).begin(); it!=(v).end(); ++it) {
		int len = (*it).length();
		for (int i = len; i < width; ++i) {
			(*it) += ' ';
		}
		if (str.length() != 0) {
			str +=  '\n';
		}
		str += (*it);
	}

	/* TODO: input and create metadata */
	/* defaluts */
	metadata.init();

	generate_field(str);
}

Game::Game(istream &in, int w, int h)
{
	char c;
	string str;
	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++j) {
			in >> c;
			str += c;
		}
		str += '\n';
	}
	generate_field(str);
}

Game::Game(string str)
{
	generate_field(str);
}

Game::~Game()
{
}

void Game::generate_field(string str)
{
	istringstream iss(str);
	vector<string> rows;
	string row;
	while (getline(iss, row, '\n')) {
		rows.push_back(row);
	}
	field.init(rows, &state, &metadata);
}

bool Game::move(Operation op)
{
	dbg_cerr << "[Game] Recieved operation " << op.get_char() << endl;
	operations.push_back(op);
<<<<<<< HEAD
	field.operate(op);
=======
	field.operate(op, state, metadata);
>>>>>>> 9eabfec889f3d461463438c28153576207a67d82
	return true;
}

bool Game::is_finished()
{
	return state.is_finished();
}

void Game::print_game_states()
{
	field.print();
	cerr << "operations: ";
	for (int i = 0; i < operations.size(); ++i) {
		cerr << operations[i].get_char();
	}
	cerr << endl;
	cerr << "score: " << state.get_score();
	cerr << ", collected: " << state.get_collected();
	cerr << ", remain: " << state.get_remain() << endl;
}

<<<<<<< HEAD
Field* Game::get_field()
=======
string Game::get_operations()
{
	string str;
	for (int i = 0; i < operations.size(); ++i) {
		str += operations[i].get_char();
	}
	return str;
}

Field& Game::get_field()
>>>>>>> 9eabfec889f3d461463438c28153576207a67d82
{
	return &field;
}

GameState* Game::get_game_state()
{
	return &state;
}
