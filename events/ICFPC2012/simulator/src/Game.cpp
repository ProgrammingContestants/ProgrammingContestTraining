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

	metadata.init(in);
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
	dbg_cerr << "[Game] Recieved operation " << op.get_char() << endl;
	operations.push_back(op);
	field.operate(op, state, metadata);
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
	cerr << ", turn: " << field.get_steps() << endl;
	cerr << ", collected: " << state.get_collected();
	cerr << ", remain: " << state.get_remain();
	cerr << ", state: " << state.get_condition_string() << endl;
	cerr << ", water: " << field.get_water_height() << endl;
	cerr << ", razors: " << state.get_razors();
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

Metadata& Game::get_metadata()
{
	return metadata;
}

// for test
GameState& Game::moves(string commands)
{
  for (int i = 0; i < commands.size(); i++) {
    Operation::OperationType op;
    switch (commands[i]) {
      case 'l':
      case 'L':
         op = Operation::LEFT;

      case 'r':
      case 'R':
        op = Operation::RIGHT;

      case 'u':
      case 'U':
        op = Operation::UP;

      case 'd':
      case 'D':
        op = Operation::DOWN;

      case 'w':
      case 'W':
        op = Operation::WAIT;

      case 'a':
      case 'A':
        op = Operation::ABORT;

      default:
        op = Operation::UNKNOWN;
      operations.push_back(op);
      field.operate(op, state, metadata);
    }
  }
  return state;
}
