#ifndef _LAMBDA_OPERATION_H
#define _LAMBDA_OPERATION_H
class Operation {
	private:
		OperationType type;
	public:
		Operation(OperationType t);
		~Operation();
		int get_dx();
		int get_dy();
		char get_char();

		enum OperationType {
			LEFT,
			RIGHT,
			UP,
			DOWN,
			WAIT,
			ABORT
		};
};
#endif
