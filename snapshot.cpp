#include "snapshot.hh"
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

snapshot::snapshot(int n){
	flag_init = true;
	flag_box_init = false;
	n_atoms = n;
	atoms = (atom*) malloc(n_atoms * sizeof(atom));
}
snapshot::snapshot(int n , box BX){
	flag_init = true;
	flag_box_init = true;
	n_atoms = n;
	atoms = (atom*) malloc(n_atoms * sizeof(atom));
	bx = BX;
}
snapshot::~snapshot(){
	free(atoms);
}
void snapshot::load_dump(char *fname, bool flag_wrap, bool flag_norm, bool flag_charge, bool flag_vel)
{
	int iniLine = 5;
	ifstream inputFile(fname);
	if (!inputFile)
	{
		cout << "ERROR: no input file: " << fname << endl;
		exit(1);
	}
	string temp;
	for(int i = 0; i < iniLine; i++){
		getline(inputFile,temp);
	}
	if(!flag_box_init){
		inputFile >> bx.x_min >> bx.x_max ;
		bx.cal_LX();
		inputFile >> bx.y_min >> bx.y_max ;
		bx.cal_LY();
		inputFile >> bx.z_min >> bx.z_max ;
		bx.cal_LZ();
	}else{
		for(int i = 0; i < 3; i++){
			getline(inputFile,temp);
		}
	}
	getline(inputFile,temp);
	cout << temp<< endl;
	getline(inputFile,temp);
	int tempInd;
	double x, y, z;
	for(int i = 0; i < n_atoms; i++){
		inputFile >> tempInd;
		if(!flag_vel){
			if(flag_charge){
				inputFile >> atoms[tempInd - 1].type >>  x >> y >> z >> atoms[tempInd - 1].charge;
			}else{
				inputFile >> atoms[tempInd - 1].type >>  x >> y >> z;
			}
		}else{
			if(flag_charge){
				inputFile >> atoms[tempInd - 1].type >>  x >> y >> z >> atoms[tempInd - 1].vel.x >> atoms[tempInd - 1].vel.y >> atoms[tempInd - 1].vel.z >> atoms[tempInd - 1].charge;
			}else{
				inputFile >> atoms[tempInd - 1].type >>  x >> y >> z >> atoms[tempInd - 1].vel.x >> atoms[tempInd - 1].vel.y >> atoms[tempInd - 1].vel.z;
			}
		}
		if(!flag_wrap){
			if(!flag_norm){
				atoms[tempInd - 1].posU.x = x;
				atoms[tempInd - 1].posU.y = y;
				atoms[tempInd - 1].posU.z = z;
				atoms[tempInd - 1].pos = atoms[tempInd - 1].apply_pbc(bx);
			}else{
				cout << "error: " << endl;
				exit(2);
			}
		}else{
			if(!flag_norm){
				atoms[tempInd - 1].pos.x = x;
				atoms[tempInd - 1].pos.y = y;
				atoms[tempInd - 1].pos.z = z;
			}else{
				atoms[tempInd - 1].pos.x = x;
				atoms[tempInd - 1].pos.y = y;
				atoms[tempInd - 1].pos.z = z;
				atoms[tempInd - 1].pos = atoms[tempInd - 1].revert_norm(bx);
			}
		}
	}
}
