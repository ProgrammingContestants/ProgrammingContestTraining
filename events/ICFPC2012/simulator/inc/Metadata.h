#ifndef _LAMBDA_METADATA_H
#define _LAMBDA_METADATA_H

#include <map>
#include <iostream>
#include <string>
using namespace std;
#include "Common.h"

class Metadata {
	private:
		int water;
		int flooding;
		int waterproof;
		map<int,int> trampoline_targets;
		int growth;
		int razors;
public:
		Metadata();
		~Metadata();

		void init();
		int get_water();
		int get_flooding();
		int get_waterproof();
		char get_target_id(char trampoline_id);
};
#endif
