#include "atom.hh"
#include "cmath"

atom::atom(){}
atom::atom(Vec r, Vec rU, Vec v, int id, int IX, int IY, int IZ, int typ, double q):
ix(IX), iy(IY),iz(IZ),pos(r),posU(rU),vel(v),ind(id),type(typ), charge(q)
{
	flag_init = true;
}

atom::~atom(){

}
Vec atom::apply_pbc(box bx){
	Vec r;
	r.x = posU.x - ((int) floor((posU.x - bx.x_min) / bx.lx)) * bx.lx;
	r.y = posU.y - ((int) floor((posU.y - bx.y_min) / bx.ly)) * bx.ly;
	r.z = posU.z - ((int) floor((posU.z - bx.z_min) / bx.lz)) * bx.lz;
	return r;
}
Vec atom::unwrapped(box bx){
	Vec r;
	r.x = pos.x + bx.lx * ix;
	r.y = pos.y + bx.ly * iy;
	r.z = pos.z + bx.lz * iz;
	return r;
}
void atom::revert_norm(box bx){
	pos.x = pos.x * bx.lx + bx.x_min;
	pos.y = pos.y * bx.ly + bx.y_min;
	pos.z = pos.z * bx.lz + bx.z_min;
}
