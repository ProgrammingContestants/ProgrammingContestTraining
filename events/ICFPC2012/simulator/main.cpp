#include "inc/Simulator.h"

#include <iostream>
using namespace std;

int main(int argc, char const* argv[])
{
	cerr << "input field (end with empty line) (*** TMPORARLY ***)" << endl;
	Simulator* sim = new Simulator();
	sim->run();
	return 0;
}
