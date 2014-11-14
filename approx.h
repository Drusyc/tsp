
#ifndef __APPROX_H__
#define __APPROX_H__


struct arc {
	double cout;
	int p1;
	int p2;	
};



//void algo_approx (int n);

void algo_approx (double ** mat, int * res, double * res_cout, int n);



#endif //__APPROX_H__

