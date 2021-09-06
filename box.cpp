#include "box.hh"

box::box(double XMIN, double XMAX, double YMIN, double YMAX, double ZMIN, double ZMAX):
x_min(XMIN),x_max(XMAX),y_min(YMIN),y_max(YMAX),z_min(ZMIN),z_max(ZMAX)
{
	cal_LX();
	cal_LY();
	cal_LZ();
}
box::box(){}
box::~box(){}
void box::cal_LX(){
	lx = x_max - x_min;
}
void box::cal_LY(){
	ly = y_max - y_min;
}
void box::cal_LZ(){
	lz = z_max - z_min;
}
