#ifndef _LAMBDA_METADATA_H
#define _LAMBDA_METADATA_H

#include <map>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class Metadata {
	private:
		int water;
		int flooding;
		int waterproof;
		map<int,int> trampoline_targets;
public:
		Metadata();
		~Metadata();

		void init(int w, int f, int wp, map<int,int> targets);
		void init();
		int get_water();
		int get_flooding();
		int get_waterproof();
		char get_target_id(char trampoline_id);
};
#endif
