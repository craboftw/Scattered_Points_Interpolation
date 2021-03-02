﻿#pragma once
#include<Eigen/Core>
#include"basis.h"
#include"Types.hpp"
Vector3d BsplinePoint(const int degree, const std::vector<double>& U, const double para,
	const std::vector<Vector3d>& pts);

Vector3d BsplinePoint(const int degree, const std::vector<double>& U, const double para,
	const Eigen::MatrixXd& pts);

// Lease-Square approximation method
Eigen::MatrixXd solve_curve_control_points(const int degree, const std::vector<double>& U,
	const std::vector<double>& paras, const std::vector<Vector3d>& points);

std::vector<double> fix_knot_vector_to_interpolate_curve(const int degree, const std::vector<double>& init_vec,
	const std::vector<double>& paras, const std::vector<Vector3d>& points);

void fix_stairs_row_too_many(const int degree, const std::vector<double>& Uin,
	const std::vector<double>& paras, std::vector<double>& Uout);

std::vector<double> knot_vector_insert_one_value(const std::vector<double>& U, const double value);

bool equation_has_solution(const Eigen::MatrixXd& A,
	const Eigen::VectorXd& b, int& rank_diff);

// check if there is solution(s) for interpolation problem
bool equation_has_solution(const Eigen::MatrixXd& A,
	const Eigen::VectorXd& b);

// using boolean predicates to conservatively fix a knot vector to interpolate curve
std::vector<double> fix_knot_vector_to_interpolate_curve_boolean(const int degree, const std::vector<double>& init_vec,
	const std::vector<double>& paras);