#include "../inc/Metadata.h"

Metadata::Metadata()
{
}

Metadata::~Metadata()
{
}

void Metadata::init(int w, int f, int wp)
{
	water = w;
	flooding = f;
	waterproof = wp;
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
