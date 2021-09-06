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
	n_atoms = n;
	atoms = (atom*) malloc(n_atoms * sizeof(atom));
	bx = BX;
}
snapshot::~snapshot(){
	free(atoms);
}
void snapshot::load_dump(bool flag_wrap, bool flag_norm, bool flag_charge, bool flag_vel)
{
	int iniLine = 5;
	ifstream inputFile(dump_file_name);
	if (!inputFile)
	{
		cout << "ERROR: no input file: " << dump_file_name << endl;
		exit(1);
	}
	string temp;
	for(int i = 0; i < iniLine; i++){
		getline(inputFile,temp);
	}
	if(!flag_box_init){
		cout << "here here" << endl;
		inputFile >> bx.x_min >> bx.x_max ;
		bx.cal_LX();
		cout << "LX: " << bx.lx << endl;
		inputFile >> bx.y_min >> bx.y_max ;
		bx.cal_LY();
		cout << "LY: " << bx.ly << endl;
		inputFile >> bx.z_min >> bx.z_max ;
		bx.cal_LZ();
		cout << "LZ: " << bx.lz << endl;
	}else{
		cout << "unfortunately here" << endl;
		for(int i = 0; i < 3; i++){
			getline(inputFile,temp);
		}
	}
	getline(inputFile,temp);
	cout << temp<< endl;
	getline(inputFile,temp);
	int tempInd;
	double x, y, z, tmpVal;


	cout << "bx.x: " << bx.lx << " " << bx.x_min << " " << bx.x_max << endl;
	cout << "bx.y: " << bx.ly << " " << bx.y_min << " " << bx.y_max << endl;
	cout << "bx.z: " << bx.lz << " " << bx.z_min << " " << bx.z_max << endl;

	for(int i = 0; i < n_atoms; i++){
		inputFile >> tempInd;
		if(!flag_vel){
			if(flag_charge){
				inputFile >> atoms[tempInd - 1].type >>  x >> y >> z >> tmpVal >> tmpVal >> tmpVal >>  atoms[tempInd - 1].charge;
			}else{
				inputFile >> atoms[tempInd - 1].type >>  x >> y >> z >> tmpVal >> tmpVal >> tmpVal;
				if(tempInd < 10){
					cout << "ind: " << tempInd - 1 << "\t" << atoms[tempInd - 1].type << "\t" <<  x << "\t" << y << "\t" << z << endl;
				}
			}
		}else{
			if(flag_charge){
				inputFile >> atoms[tempInd - 1].type >>  x >> y >> z >> atoms[tempInd - 1].vel.x >> atoms[tempInd - 1].vel.y >> atoms[tempInd - 1].vel.z >> tmpVal >> tmpVal >> tmpVal >> atoms[tempInd - 1].charge;
			}else{
				inputFile >> atoms[tempInd - 1].type >>  x >> y >> z >> atoms[tempInd - 1].vel.x >> atoms[tempInd - 1].vel.y >> atoms[tempInd - 1].vel.z >> tmpVal >> tmpVal >> tmpVal;
			}
		}
		if(!flag_wrap){
			if(!flag_norm){
				atoms[tempInd - 1].posU.x = x;
				atoms[tempInd - 1].posU.y = y;
				atoms[tempInd - 1].posU.z = z;
				atoms[tempInd - 1].pos = atoms[tempInd - 1].apply_pbc(bx);
			}else{
				cout << "error: when the positions are normalized, wrapped positions are expected!!!" << endl;
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
					atoms[tempInd - 1].revert_norm(bx);
			}
		}
	}
	inputFile.close();
}
void snapshot::set_dumpFile_path(string dump_path, int t){
  size_t spac;
  string sub1;
  string sub2;
  spac = dump_path.find("*");
  sub1 = dump_path.substr(0,spac);
  sub2 = dump_path.substr(spac+1);
  //cout << dump_path << endl;
  //cout << sub1 << endl;
  //cout << sub2 << endl;
  char arr2[100];
  char arr3[100];
  /*for(int i = 0; i < sub1.length(); i++){
    arr2[i] = sub1[i];
  }
  for(int i = 0; i < sub2.length(); i++){
    arr3[i] = sub2[i];
  }*/
  //cout << arr2 << endl;
  strcpy(arr2, sub1.c_str());
  strcpy(arr3, sub2.c_str());
  sprintf(dump_file_name, "%s%d%s",arr2,t,arr3);
  cout << dump_file_name << endl;
  int n = sub1.length()+sub2.length()+7;
  //cout << "size: " << n << endl;
  dump_file_name[n]='\0';
}
