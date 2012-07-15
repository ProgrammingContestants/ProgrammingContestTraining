#include "../inc/Metadata.h"
#include <cassert>

Metadata::Metadata()
{
}

Metadata::~Metadata()
{
}

void Metadata::init(int w, int f, int wp, map<int,int> targets)
{
	water = w;
	flooding = f;
	waterproof = wp;
	trampoline_targets=targets;
}

void Metadata::init()
{
	int water = 0;
	int flooding = 0;
	int waterproof = 10;
	map<int,int> trampoline_targets;
	int growth = 25;
	int razors = 0;

	while(!cin.eof()){
		string keyword;
		cin>>keyword;
		if(keyword=="Water"){
			cin>>water;
		}else if(keyword=="Flooding"){
			cin>>flooding;
		}else if(keyword=="Waterproof"){
			cin>>waterproof;
		}else if(keyword=="Trampoline"){
			char trampoline;
			cin>>trampoline;
			string keyword2;
			cin>>keyword2;
			assert(keyword2=="targets");
			char target;
			cin>>target;
			trampoline_targets[trampoline]=target;
		}else if(keyword=="Growth"){
			cin>>growth;
		}else if(keyword=="Razors"){
			cin>>razors;
		}
	}

	init(water,flooding,waterproof,trampoline_targets);
}

int Metadata::get_water()
{
	return water;
}
int Metadata::get_flooding()
{
	return flooding;
}
int Metadata::get_waterproof()
{
	return waterproof;
}

char Metadata::get_target_id(char trampoline_id)
{
	map<int,int>::iterator it=trampoline_targets.find(trampoline_id);
	assert(it!=trampoline_targets.end());
	return (*it).second;
}