#include <fstream>
#include <iostream>
#include <string.h>

using namespace std;

class input{
public:
	ifstream inFile;
	static const int NLIST = 11;
	static const int NLIST_digit = 5;
	int flag_box;
	bool flag_traj= false;
	int flag_t_first, flag_t_step, flag_num_times, flag_NRPART, flag_cutOff;
	int flag_dump, flag_per[3], flag_normalization, flag_proj, flag_save_3D;
	int t_first, t_step, num_times, NRPART;
	string dump_path;
	int dump_path_size;
	double BOX_CUTOFF, CUTOFF;
	string *listInput;// {"t_init", "t_step","num_times","NRPART","cut_off","dump_path","periodicity", "normalized_coordinate", "proj_plane","save_3D"};
	input(char*);
	~input();
	void read();
	void compare_assign(int caseNr, string val);
	void compare_assign(int caseNr, double val);
	void checkInput();
};
