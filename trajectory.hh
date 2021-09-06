#include "atom.hh"
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

class trajectory{
public:
	string dump_file_name;
	atom **atoms;
	box *bx;
	int n_atoms, n_times;
	int flag_init;
	trajectory(int nr, int nt);
	~trajectory();
	void load_traj_from_single_dump(bool flag_vel, bool flag_force, bool flage_normalized, bool flag_wrapped);
	void set_dumpFile_path(string dump_path);
};
