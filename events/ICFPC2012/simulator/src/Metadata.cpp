#include "../inc/Metadata.h"
#include <cassert>

Metadata::Metadata():water(0),flooding(0),waterproof(10),growth(25),razors(0)
{
}

Metadata::~Metadata()
{
}

void Metadata::init()
{
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