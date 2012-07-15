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
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			cells.push_back(Cell(rows[y][x]));
			/* TODO: is it right doing here? */
			if (rows[y][x] == 'R') {
				robot.init(x, y, metadata);
			}
			else if (rows[y][x] == '\\') {
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

Cell &Field::get_cell(int x, int y)
{
	/* 1 origin, bottom left is (1, 1) */
	return get_cell_internal(x-1,height-y);
}

Cell &Field::get_cell_internal(int x, int y)
{
	return cells[width * y + x];
}

string Field::get_string()
{
	string str;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if(robot.get_x()==x&&robot.get_y()==y){
				str += 'R';
			}else{
				str += cells[width * y + x].get_char();
			}
		}
		str += '\n';
	}
	return str;
}

void Field::operate(Operation op, GameState& state, Metadata& metadata)
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

	move_robot(dx, dy, state, metadata);
	update(state);

	/* dead check */
	if (robot.is_dead()) {
		state.lose();
	}
	if( !robot.breathe(cells[width * robot.get_y() + robot.get_x()].is_flooded()) ) {
		/* Die by Drowing */
		state.drown();
	}

	flood();
}

void Field::flood()
{
	if (flooding != 0 && steps % flooding == 0) {
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

bool Field::move_robot(int dx, int dy, GameState& state, Metadata& metadata)
{
	/* TODO: SEGFAULT GURAD */

	int y = robot.get_y(), x = robot.get_x();
	Cell &cell = get_cell_internal(x+dx,y+dy);
	switch (cell.get_type()) {
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
				if (get_cell_internal(x+dx*2,y).get_type() == Cell::EMPTY) {
					get_cell_internal(x+dx*2,y).set_type(Cell::ROCK);
				} else {
					return false;
				}
			}
			break;

		/* Trampoline jumping */
		case Cell::TRAMPOLINE:
			{
			char target_id=metadata.get_target_id(cell.get_id());
			for(int tx=0;tx<get_width();tx++){
				for(int ty=0;ty<get_height();ty++){
					Cell& c = get_cell_internal(tx,ty);
					if(c.get_type()==Cell::TARGET&&c.get_id()==target_id){
						get_cell_internal(x,y).set_type(Cell::EMPTY);
						robot.set_location(tx,ty);
						c.set_type(Cell::ROBOT);
					}else if(c.get_type()==Cell::TRAMPOLINE&&metadata.get_target_id(c.get_id())==target_id){
						c.set_type(Cell::EMPTY);
					}
				}
			}
			return true;
			}

		default:
			return false;
	}
	dbg_cerr << "[Field] robot move: (dx, dy) = (" << dx << ", " << dy << ")" << endl;
	robot.move(dx, dy);
	get_cell_internal(x,y).set_type(Cell::EMPTY);
	get_cell_internal(x+dx,y+dy).set_type(Cell::ROBOT);
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
	if (robot.get_y() - 1 >= 0
			&& old[width * (robot.get_y()-1) + (robot.get_x())].get_type() != Cell::ROCK
			&& cells[width * (robot.get_y()-1) + (robot.get_x())].get_type() == Cell::ROCK) {
		robot.destroy();
	}
}

void Field::print()
{
	cout << get_string();
}

Robot& Field::get_robot()
{
	return robot;
}

const int Field::get_steps()
{
	return steps;
}
