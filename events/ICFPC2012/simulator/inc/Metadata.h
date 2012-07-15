#ifndef _LAMBDA_METADATA_H
#define _LAMBDA_METADATA_H
class Metadata {
	private:
		int water;
		int flooding;
		int waterproof;
	public:
		Metadata();
		~Metadata();

		void init(int w, int f, int wp);
		int get_water();
		int get_flooding();
		int get_waterproof();
			
};
#endif
