#include"basis.h"
#include<iostream>
#include<assert.h>
// the B-spline basis function N_{i,0}(u). U is the knot vector
double Ni0(const int i, const double u, const std::vector<double> &U) {
	if (u >= U[i] && u < U[i + 1]) return 1.0;
	return 0;
}

double handle_division(const double a, const double b) {
	
	if (b == 0) {
		// if the denominator is 0, then this term is 0
		return 0;
	}
	else return a / b;
}
// the B-spline basis function N_{i,p}(u)
double Nip(const int i, const int p, const double u, const std::vector<double> &U) {
	if (p == 0) {
		return Ni0(i, u, U);
	}
	
	double result1 = handle_division(u - U[i], U[i + p] - U[i])*Nip(i, p - 1, u, U);
	double result2 = handle_division(U[i + p + 1] - u, U[i + p + 1] - U[i + 1])*Nip(i + 1, p - 1, u, U);
	return result1 + result2;
}

double Degree_1_Derivative(const int i, const int p, const double u, const std::vector<double> &U) {
	double result1 = handle_division(p, U[i + p] - U[i])*Nip(i, p - 1, u, U);
	double result2 = handle_division(p, U[i + p + 1] - U[i + 1])*Nip(i + 1, p - 1, u, U);
	return result1 - result2;
}

// the kth derivate of basis function
double kth_derivate_Nip(const int k, const int i, 
	const int p, const double u, const std::vector<double> &U) {
	assert(k <= p);
	if (k == 0) {// if k=0, return itself
		return Nip(i, p, u, U);
	}
	double result1 = handle_division(p, U[i + p] - U[i])*kth_derivate_Nip(k-1, i, p - 1, u, U);
	double result2 = handle_division(p, U[i + p + 1] - U[i + 1])*kth_derivate_Nip(k-1, i + 1, p - 1, u, U);
	return result1 - result2;
}
