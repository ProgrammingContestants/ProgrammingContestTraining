#ifndef _LAMBDA_CELL_H
#define _LAMBDA_CELL_H

#include "Common.h"

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
			TRAMPOLINE,
			TARGET,
			EMPTY
		};

		Cell(char c);
		~Cell();
		void flood();
		void set_type(CellType t);
		void set_type(CellType t, char id);
		CellType get_type();
		char get_char();
		char get_id();

	private:
		CellType type;
		bool flooded;
		char id;
		static const char UNDEF_ID = -1;
};
#endif
