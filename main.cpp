#include <iostream>
#include <fstream>
#include "snapshot.hh"
#include "p_vec_ten.hh"
#include <cstdlib>
#include <algorithm>
#include <time.h>
#include <string.h>
#include "input.hh"

using namespace std;
typedef p_vec<> Vec;

int main(int argc, char **argv){
	if(argc !=2){
			cout << "the path to the input file is missing from the given argument!!!" << endl;
		  return 1;

	}
	char input_path[1000];
	strcpy(input_path, argv[1]);

	cout << "the input path: " << input_path << endl;
	input inp(input_path);
	inp.read();
	box bx;
	snapshot config(inp.NRPART,bx);
	config.set_dumpFile_path(inp.dump_path, inp.t_first);
	config.load_dump(true, true, false, false);
	return 0;
}
