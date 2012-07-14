#ifndef _LAMBDA_FIELD_H
#define _LAMBDA_FIELD_H
class Field {
	private:
		vector<Cell> cells;
	public:
		int get_width();
		int get_height();
		int get_cell(int x, int y);
};
#endif
