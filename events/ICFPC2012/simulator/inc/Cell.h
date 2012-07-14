#ifndef _LAMBDA_CELL_H
#define _LAMBDA_CELL_H

class Cell {
	private:
		CellType type;
		bool flooded;
	public:
		Cell(CellType type);
		~Cell();
		CellType get_type();

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
};
#endif
