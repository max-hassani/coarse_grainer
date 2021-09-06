#include "atom.hh"
#include <iostream>

class snapshot{
public:
	int n_atoms;
	bool flag_init = false;
	bool flag_box_init= false;
	box bx;
	atom *atoms;
	char dump_file_name[1000];
	snapshot(int n);
	snapshot(int n, box BX);
	~snapshot();
	void load_dump(bool flag_wrap, bool flag_norm, bool flag_charge, bool flag_vel);
	void load_data(char *file_name);
	void set_dumpFile_path(string dump_path, int t);
};
