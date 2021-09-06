#ifndef ATOM_CPP
#define ATOM_CPP

#include "p_vec_ten.hh"
#include "box.hh"
#include <iostream>


typedef p_vec<> Vec;

class atom{
	public:
		Vec pos, posU, vel, f;
		int type;
		double charge;
		int ix,iy, iz;
		int ind;
		bool flag_init = false;
		atom();
		atom(Vec r, Vec rU, Vec v, int id, int IX, int IY, int IZ, int typ, double q);
		~atom();
		Vec apply_pbc(box bx);
		Vec unwrapped(box bx);
		void revert_norm(box bx);
};
#endif
