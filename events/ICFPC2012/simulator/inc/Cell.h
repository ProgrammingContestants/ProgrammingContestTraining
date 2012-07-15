#ifndef _LAMBDA_CELL_H
#define _LAMBDA_CELL_H

class Cell {
	public:
		enum CellType {
			ROBOT,
			WALL,
			ROCK,
			LAMBDA,
			CLIFT,
			OLIFT,
			EARTH,
			EMPTY
		};

		Cell(char c);
		~Cell();
		void set_type(CellType t);
		void flood();
		bool is_flooded();

		CellType get_type();
		char get_char();

	private:
		CellType type;
		bool flooded;
};
#endif
