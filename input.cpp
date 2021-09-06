#include "input.hh"


input::input(char *file_name){
	inFile.open(file_name);
	listInput = (string*) malloc(NLIST *sizeof(string));
	string temp_list[] = {"t_init", "t_step","num_times","NRPART","cut_off","dump_path","periodicity", "normalized_coordinate", "proj_plane","save_3D", "trajectory"};
	for(int i = 0; i < NLIST; i++){
		listInput[i] = temp_list[i];
	}
	flag_normalization = 0 ;
	flag_box = 0;
	flag_dump = 0;
	 if(!inFile){
		 cout << "FATAL ERROR: the input file not found at " << file_name << "!";
		 exit(1);
	 }
}
input::~input(){
	free(listInput);
}

void input::read(){
	string str;
	double val;
	int i = 0;//line number
	int counter = 0;// number of correct inputs
	size_t spac;
	string sub1;
	string sub2;
	while(!inFile.eof()){
		getline(inFile, str);
		spac = str.find("=");
		sub1 = str.substr(0,spac);
		sub2 = str.substr(spac+1);
		int flag = 0;
		for(int j = 0; j < NLIST; j++){
			if(sub1.compare(listInput[j]) == 0){
				if(j < NLIST_digit){
					val = stod(sub2);
					compare_assign(j,val);
				}else{
					compare_assign(j,sub2);
				}
				flag = 1;
				counter++;
			}
		}
		if(flag == 0 && str.length() != 0){
			cout << "error here" << endl;
			cout << "length: " << str.length() << endl;
			cout << "The input file at line " << i+1 << " is not defined well" << endl;
			cout << "Take a look!" << endl;
			cout << "str: " << str << endl;
			spac = str.find("=");
			sub1 = str.substr(0,spac);
			sub2 = str.substr(spac+1);
			cout << "sub1: " << sub1 << " sub2:" << sub2 << endl;
			cout << "spac: "<< spac << endl;
			exit(2);
		}
		i++;
	 }
	checkInput();
}
void input::compare_assign(int caseNr, string val){

	switch (caseNr) {
		case NLIST_digit:{
			dump_path_size = val.length();
			dump_path = val;
			cout << "dump_path= " << dump_path<< endl;
			flag_dump = 1;
			break;
		}
		case NLIST_digit+1:
		{
		  int ind_flag = 0;
		  for(int i = 0; i < val.length(); i++){
			if(val[i] != ' '){
			  if(val[i] == 'p' || val[i] == 's' || val[i]=='f'){
				if(val[i] == 'p'){
				  flag_per[ind_flag] = 1;
				}else if(val[i]=='s' || val[i]=='f'){
				  flag_per[ind_flag]=2;
				}
				ind_flag++;
			  }else{
				cout << "Error: "<< endl;
				cout << "the given input for the periodicity is not correct" << endl;
				cout << "the given values for each direction must be from {\'s\', \'p\',\'f\'}" << endl;
				cout << "given input: "<< val << endl;
				exit(16);
			  }
			}
		  }
		  if(flag_per[0] == 1){
			cout << "periodic in x direction" << endl;
		  }else{
			cout << "non-periodic in x direction" << endl;
		  }
		  if(flag_per[1] == 1){
			cout << "periodic in y direction" << endl;
		  }else{
			cout << "non-periodic in y direction" << endl;
		  }
		  if(flag_per[2] == 1){
			cout << "periodic in z direction" << endl;
		  }else{
			cout << "non-periodic in z direction" << endl;
		  }
		  break;
		}
		case NLIST_digit+2:{
			if(val == "yes"){
				flag_normalization = 1;
			}else if(val == "YES"){
				flag_normalization = 1;
			}else if(val == "Yes"){
				flag_normalization = 1;
			}
			cout << "flag_normalization= " << flag_normalization << endl;
			break;
		}
		case NLIST_digit+3:{
			if(val == "xy" || val == "yx"){
			  flag_proj = 1;
			}else if(val == "xz" || val == "zx"){
			  flag_proj = 2;
			}else if(val == "zy"|| val == "yz"){
			  flag_proj = 3;
			}else if(val == "none"){
			  flag_proj = 4;
			}
			break;
		}
		case NLIST_digit+4:{
			if(val == "yes"){
				flag_save_3D =1;
			}else if(val == "YES"){
				flag_save_3D =1;
			}else if(val == "Yes"){
				flag_save_3D =1;
			}else if(val == "no"){
			  flag_save_3D = 2;
			}
		//static int count= 0;
		//count++;
			cout << "flag_save_3D = " << flag_save_3D << endl;
			break;
		}
		case NLIST_digit+5:
		{
			if(val == "yes"){
				flag_traj = true;
			}
			break;
		}
	}
}
void input::compare_assign(int caseNr, double val){

	switch (caseNr) {
		case 0:
			t_first = (int) val;
			flag_t_first=1;
			cout << "t_first= " << t_first << endl;
			break;
		case 1:
			t_step = (int) val;
			flag_t_step = 1;
			cout << "t_step= " << t_step << endl;
			break;
		case 2:	//LX = val;
			num_times = (int)val;
			flag_num_times = 1;
			cout << "num_times= " << num_times << endl;
			break;
		case 3:
			NRPART = (int) val;
			cout << "NRPART= " << NRPART<< endl;
			flag_NRPART = 1;
			break;
		case 4:{
			CUTOFF = val;
			BOX_CUTOFF=2.2*CUTOFF;
			cout << "cutoff: " << CUTOFF << endl;
			flag_cutOff = 1;
			break;
		}
	}
}
void input::checkInput(){
  int exit_flag= 0;
  if(flag_dump == 0){
    cout << "the dump file path is not set" << endl;
    exit_flag++;
  }
  if(flag_NRPART== 0){
    cout << "the number of particles is not set" << endl;
    exit_flag++;
  }
  if(flag_t_step== 0){
    cout << "the incremental timestep is not set" << endl;
    exit_flag++;
  }
  if(flag_t_first== 0){
    cout << "the initial timestep not set" << endl;
    exit_flag++;
  }
  if(flag_num_times== 0){
    cout << "the number of times is not set" << endl;
    exit_flag++;
  }
  if(flag_normalization == 0){
    cout << "the normalizitian flag is not set" << endl;
    exit_flag++;
  }
  if(flag_save_3D == 0){
    cout << "the preference for 3D save is not set" << endl;
    exit_flag++;
  }
  for(int i = 0; i < 3; i++){
    if(flag_per[i] == 0){
      cout << "periodicity is not set correctly" << endl;
      exit_flag++;
    }
  }
  if(flag_proj == 0){
    cout << "2D projection is not set correctly" << endl;
    exit_flag++;
  }
  if(flag_cutOff == 0){
    cout << "cutoff is not set correctly" << endl;
    exit_flag++;
  }
  if(exit_flag > 0){
    cout << "number of error with the input file : " << exit_flag << endl;
    exit(1);
  }
}
