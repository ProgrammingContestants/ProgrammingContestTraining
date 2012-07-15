#include "../inc/Metadata.h"
#include <cassert>

Metadata::Metadata():water(0),flooding(0),waterproof(10),growth(25),razors(0)
{
}

Metadata::~Metadata()
{
}

void Metadata::init(istream& in)
{
	while(!in.eof()){
		string keyword;
		in>>keyword;
		if(keyword=="Water"){
			in>>water;
		}else if(keyword=="Flooding"){
			in>>flooding;
		}else if(keyword=="Waterproof"){
			in>>waterproof;
		}else if(keyword=="Trampoline"){
			char trampoline;
			in>>trampoline;
			string keyword2;
			in>>keyword2;
			assert(keyword2=="targets");
			char target;
			in>>target;
			trampoline_targets[trampoline]=target;
		}else if(keyword=="Growth"){
			in>>growth;
		}else if(keyword=="Razors"){
			in>>razors;
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
int Metadata::get_growth()
{
	return growth;
}
int Metadata::get_razors()
{
	return razors;
}
