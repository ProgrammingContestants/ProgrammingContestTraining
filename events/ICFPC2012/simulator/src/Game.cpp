#include "../inc/Game.h"

Game::Game()
{
	int width = 0;
	vector<string> v;
	string str, row;
	while (getline(cin, row) && row != "") {
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
	/* sample */
	int water = 1;
	int flooding = 8;
	int waterproof = 5;
	metadata.init(water, flooding, waterproof);

	generate_field(str);
}

Game::Game(int w, int h)
{
	cerr << "w: " << w << ", h: " << h << endl;
	char c;
	string str, buf;
	cin.ignore();
	for (int i = 0; i < h; ++i) {
		if (i != 0) {
			str += '\n';
		}
		getline(cin, buf);
		str += buf;
	}
	cerr << str << endl;
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
	cerr << "water: " << field.get_water_height() << endl;
}

string Game::get_operations()
{
	string str;
	for (int i = 0; i < operations.size(); ++i) {
		str += operations[i].get_char();
	}
	return str;
}

void Game::print_field()
{
	field.print();
}

Field& Game::get_field()
{
	return field;
}

GameState& Game::get_game_state()
{
	return state;
}
