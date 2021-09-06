#ifndef BOX_CPP
#define BOX_CPP

class box{
public:
	double x_min, x_max;
	double y_min, y_max;
	double z_min, z_max;
	double lx, ly, lz;
	bool flag_init = false;
	box();
	box(double XMIN, double XMAX, double YMIN, double YMAX, double ZMIN, double ZMAX);
	~box();
	void cal_LX();
	void cal_LY();
	void cal_LZ();
};

#endif
