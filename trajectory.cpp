#include "trajectory.hh"

using namespace std;

trajectory::trajectory(int nr, int nt){
	flag_init = true;
	n_atoms = nr;
	n_times = nt;
	atoms = (atom**) malloc(nt * sizeof(atom*));
	for(int t = 0; t < n_times; t++){
		atoms[t] = (atom*) malloc(n_atoms * sizeof(atom));
	}
	bx = (box*) malloc(nt * sizeof(box));
}
trajectory::~trajectory(){
	for(int t = 0; t < n_times; t++){
		free(atoms[t]);
	}
	free(atoms);
	free(bx);
}
void trajectory::load_traj_from_single_dump(bool flag_vel, bool flag_force, bool flage_normalized, bool flag_wrapped){
	int iniLine = 5;
	ifstream inputFile(dump_file_name);
	if (!inputFile)
	{
		cout << "ERROR: no input file: " << dump_file_name << endl;
		exit(1);
	}
	string temp;
	int tempInd;
	double x, y, z, tmpVal;
	for(int t = 0; t < n_times; t++){
		cout << "loading time: " << t << endl;
		for(int j = 0; j < iniLine; j++){
			getline(inputFile,temp);
		}
		inputFile >> bx[t].x_min >> bx[t].x_max ;
		bx[t].cal_LX();
		inputFile >> bx[t].y_min >> bx[t].y_max ;
		bx[t].cal_LY();
		inputFile >> bx[t].z_min >> bx[t].z_max ;
		bx[t].cal_LZ();

		getline(inputFile,temp);

		getline(inputFile,temp);

		for(int i = 0 ; i < n_atoms; i++){
			inputFile >> tempInd;

			if(flag_vel && flag_force && flage_normalized && !flag_wrapped){
				inputFile >> atoms[t][tempInd - 1].type >>  x >> y >> z >> atoms[t][tempInd - 1].f.x >> atoms[t][tempInd - 1].f.y >> atoms[t][tempInd - 1].f.z >> atoms[t][tempInd - 1].vel.x >> atoms[t][tempInd - 1].vel.y >> atoms[t][tempInd - 1].vel.z;
				atoms[t][tempInd - 1].pos.x = x;
				atoms[t][tempInd - 1].pos.y = y;
				atoms[t][tempInd - 1].pos.z = z;
				atoms[t][tempInd - 1].revert_norm(bx[t]);
				atoms[t][tempInd - 1].posU = atoms[t][tempInd - 1].pos;
				atoms[t][tempInd - 1].pos = atoms[t][tempInd - 1].apply_pbc(bx[t]);
			}
		}
		getline(inputFile, temp);
	}
	inputFile.close();
}
void trajectory::set_dumpFile_path(string dump_path){
	size_t spac;
	spac = dump_path.find("*");
	if(spac > 0 && spac <= dump_path.size()){
		cout << "the dump_path for trajectories should not include *" << endl;
		exit(12);
	}
	dump_file_name = dump_path;
}
