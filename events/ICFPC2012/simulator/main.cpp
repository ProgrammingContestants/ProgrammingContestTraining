#include "inc/Simulator.h"

#include <iostream>
using namespace std;

int main(int argc, char const* argv[])
{
	Simulator sim(true);
	sim.run();
	return 0;
}
