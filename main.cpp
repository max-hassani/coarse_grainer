#include <iostream>
#include <fstream>
#include "snapshot.hh"
#include "p_vec_ten.hh"
#include <cstdlib>
#include <algorithm>
#include <time.h>
#include <string.h>
#include "input.hh"
#include "trajectory.hh"

using namespace std;
typedef p_vec<> Vec;

int main(int argc, char **argv){
	clock_t start, end;
	start = clock();
	if(argc !=2){
			cout << "the path to the input file is missing from the given argument!!!" << endl;
		  return 1;

	}
	char input_path[1000];
	strcpy(input_path, argv[1]);

	cout << "the input path: " << input_path << endl;
	input inp(input_path);
	inp.read();
	if(!inp.flag_traj){
		box bx;
		snapshot config(inp.NRPART,bx);
		config.set_dumpFile_path(inp.dump_path, inp.t_first);
		config.load_dump(true, true, false, false);
	}else{
		trajectory traj(inp.NRPART, inp.num_times);
		traj.set_dumpFile_path(inp.dump_path);
		traj.load_traj_from_single_dump(true, true, true, false);
	}
	end = clock();
	cout << "Time required for execution:"<< (double)(end-start)/CLOCKS_PER_SEC<< " seconds." << endl;
	cout << "DONE!" << endl;
	return 0;
}
