#include "../inc/Field.h"

Field::Field()
{
}

Field::~Field()
{
}

void Field::init(vector<string> rows, GameState& s, Metadata& metadata)
{
	steps = 0;
	water = metadata.get_water();
	flooding = metadata.get_flooding();

	width = rows[0].length();
	height = rows.size();

	int cnt_lambda = 0;
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			cells.push_back(Cell(rows[i][j]));
			/* TODO: is it right doing here? */
			if (rows[i][j] == 'R') {
				rob.init(j, i, metadata);
			}
			else if (rows[i][j] == '\\') {
				++cnt_lambda;
			}
		}
	}

	/* flooding */
	for (int i = height - 1; i >= height - water; i--) {
		for (int j = 0; j < width; j++) {
			cells[width * i + j].flood();
		}
	}

	/* TODO: should make init() function? */
	s.set_remain(cnt_lambda);
}

int Field::get_width()
{
	return width;
}

int Field::get_height()
{
	return height;
}

Cell Field::get_cell(int x, int y)
{
	/* 1 origin, bottom left is (1, 1) */
	--x;
	return cells[width * (height - y) + x];
}

string Field::get_string()
{
	string str;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			str += cells[width * i + j].get_char();
		}
		str += '\n';
	}
	return str;
}

void Field::operate(Operation op, GameState& state)
{
	++steps;
	int dx = 0, dy = 0;
	switch(op.get_type()) {
		case Operation::LEFT:
			dx = -1;
			break;
		case Operation::RIGHT:
			dx = 1;
			break;
		case Operation::UP:
			dy = -1;
			break;
		case Operation::DOWN:
			dy = 1;
			break;
		case Operation::WAIT:
			break;
		case Operation::ABORT:
			state.abort();
			return;
	}

	/* Operation cost */
	state.decrement_score();

	move_robot(dx, dy, state);
	update(state);

	/* dead check */
	if (rob.is_dead()) {
		state.lose();
	}
	if( !rob.breathe(cells[width * rob.get_y() + rob.get_x()].is_flooded()) ) {
		/* Die by Drowing */
		state.drown();
	}

	flood();
}

void Field::flood()
{
	if (steps % flooding == 0) {
		cerr << "Flooding!" << endl;
		++water;
		for (int i = 0; i < width; i++) {
			cells[width * (height - water) + i].flood();
		}
	}
}

int Field::get_water_height()
{
	return water;
}

bool Field::move_robot(int dx, int dy, GameState& state)
{
	/* TODO: SEGFAULT GURAD */

	int y = rob.get_y(), x = rob.get_x();
	switch (cells[width * (y+dy) + (x+dx)].get_type()) {
		/* Stay */
		case Cell::ROBOT:
			break;

		/* Cannot move */
		case Cell::WALL:
		case Cell::CLIFT:
			return false;

		/* Natural move */
		case Cell::EMPTY:
			break;
		case Cell::EARTH:
			break;

		/* State changing move */
		case Cell::LAMBDA:
			state.collect_lambda();
			break;
		case Cell::OLIFT:
			state.win();
			break;

		/* Rock pushing */
		case Cell::ROCK:
			if (dx == 0) {
				return false;
			} else {
				if (cells[width * y + x + dx + dx].get_type() == Cell::EMPTY) {
					cells[width * y + x + dx + dx].set_type(Cell::ROCK);
				} else {
					return false;
				}
			}
			break;
		default:
			return false;
	}
	cerr << "[Field] robot move: (dx, dy) = (" << dx << ", " << dy << ")" << endl;
	rob.move(dx, dy);

	cells[width * y + x].set_type(Cell::EMPTY);
	cells[width * (y+dy) + (x+dx)].set_type(Cell::ROBOT);
	return true;
}

void Field::update(GameState& state)
{
	vector<Cell> old = cells;
	for (int i = height - 1; i >= 0; --i) {
		 for (int j = 0; j < width; ++j) {
			if (old[width * (i) + (j)].get_type() == Cell::ROCK) {
				if (i + 1 < height
						&& old[width * (i+1) + (j)].get_type() == Cell::EMPTY) {
					cells[width * (i) + (j)].set_type(Cell::EMPTY);
					cells[width * (i+1) + (j)].set_type(Cell::ROCK);
				}
				else if (i + 1 < height
						&& old[width * (i+1) + (j)].get_type() == Cell::ROCK) {
					if (j + 1 < width
							&& old[width * (i) + (j+1)].get_type() == Cell::EMPTY
							&& old[width * (i+1) + (j+1)].get_type() == Cell::EMPTY) {
						/* Fall Right */
						cells[width * (i) + (j)].set_type(Cell::EMPTY);
						cells[width * (i+1) + (j+1)].set_type(Cell::ROCK);
					}
					else if (j - 1 >= 0
							&& old[width * (i) + (j-1)].get_type() == Cell::EMPTY
							&& old[width * (i+1) + (j-1)].get_type() == Cell::EMPTY) {
						/* Fall Left */
						cells[width * (i) + (j)].set_type(Cell::EMPTY);
						cells[width * (i+1) + (j-1)].set_type(Cell::ROCK);
					}
				}
				else if (i + 1 < height
						&& old[width * (i+1) + (j)].get_type() == Cell::LAMBDA) {
					if (j + 1 < width
							&& old[width * (i) + (j+1)].get_type() == Cell::EMPTY
							&& old[width * (i+1) + (j+1)].get_type() == Cell::EMPTY) {
						/* Fall Right */
						cells[width * (i) + (j)].set_type(Cell::EMPTY);
						cells[width * (i+1) + (j+1)].set_type(Cell::ROCK);
					}
				}
			}
			if (old[width * (i) + (j)].get_type() == Cell::CLIFT
					&& state.get_remain() == 0) {
				cells[width * (i) + (j)].set_type(Cell::OLIFT);
			}
		}
	}
	if (rob.get_y() - 1 >= 0
			&& old[width * (rob.get_y()-1) + (rob.get_x())].get_type() != Cell::ROCK
			&& cells[width * (rob.get_y()-1) + (rob.get_x())].get_type() == Cell::ROCK) {
		rob.destroy();
	}
}

void Field::print()
{
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			cout << cells[width * i + j].get_char();
		}
		cout << endl;
	}
}
