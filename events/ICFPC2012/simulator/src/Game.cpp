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
	int water = 0;
	int flooding = 0;
	int waterproof = 10;
	metadata.init(water, flooding, waterproof);

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
	field.init(rows, state, metadata);
}

bool Game::move(Operation op)
{
	cerr << "[Game] Recieved operation " << op.get_char() << endl;
	operations.push_back(op);
	field.operate(op, state);
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
	cerr << "state: " << state.get_condition_string() << endl;
}

Field& Game::get_field()
{
	return field;
}

GameState& Game::get_game_state()
{
	return state;
}
