#include"basis.h"
#include"curve.h"
#include <igl/opengl/glfw/Viewer.h>
#include<iostream>
#include<array>
#include"test.h"
#include<mesh_processing.h>
#include <igl/boundary_loop.h>
#include <igl/map_vertices_to_circle.h>
#include <igl/harmonic.h>
#include <igl/write_triangle_mesh.h>

igl::opengl::glfw::Viewer global_viewer;
void show_basis(const std::vector<double>&b_vec) {
	for (int i = 0; i < b_vec.size(); i++) {
		std::cout << b_vec[i] << " ";
	}
	std::cout << std::endl;
}
void test_opengl() {
	// Inline mesh of a cube
	const Eigen::MatrixXd V = (Eigen::MatrixXd(8, 3) <<
		0.0, 0.0, 0.0,
		0.0, 0.0, 1.0,
		0.0, 1.0, 0.0,
		0.0, 1.0, 1.0,
		1.0, 0.0, 0.0,
		1.0, 0.0, 1.0,
		1.0, 1.0, 0.0,
		1.0, 1.0, 1.0).finished();
	const Eigen::MatrixXi F = (Eigen::MatrixXi(12, 3) <<
		1, 7, 5,
		1, 3, 7,
		1, 4, 3,
		1, 2, 4,
		3, 8, 7,
		3, 4, 8,
		5, 7, 8,
		5, 8, 6,
		1, 5, 6,
		1, 6, 2,
		2, 6, 8,
		2, 8, 4).finished().array() - 1;

	// Plot the mesh
	igl::opengl::glfw::Viewer viewer;
	viewer.data().set_mesh(V, F);
	viewer.data().set_face_based(true);
	viewer.launch();
}


void draw_a_line() {
	Eigen::MatrixXd pts(3,3),Color(3,3);
	//
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			Color(i, j) = 0;
			pts(i, j) = 0;
		}
	}
	pts(0, 0) = 1; pts(0, 1) = 2; pts(0, 2) = 3;
	std::cout << pts << std::endl;
	igl::opengl::glfw::Viewer viewer;
	viewer.data().set_points(pts,Color);
	viewer.launch();
}
void draw_a_curve() {
	int p = 3;
	// 8 control points
	std::vector<double>U = { {0,0,0,0,0.1,0.4,0.7,0.9,1,1,1,1} };
	std::array<double, 8> us = { {0.1,0.2,0.3,0.5,0.6,0.7,0.8,0.9} };
	std::vector<Vector3d> pts(8);
	pts[0] = Vector3d(0, 0, 0);
	pts[1] = Vector3d(0, 1, 0);
	pts[2] = Vector3d(0, 1, 2);
	pts[3] = Vector3d(0, 1, 1);
	pts[4] = Vector3d(0, 2, 1);
	pts[5] = Vector3d(0, 2, 0);
	pts[6] = Vector3d(0, 3, 1);
	pts[7] = Vector3d(0, 3, 3);
	igl::opengl::glfw::Viewer viewer;
	Eigen::MatrixXd  Color(8, 3), Hcolor(100, 3), OneColor(1, 3), PTS(8, 3), Curve(100, 3);
	OneColor(0, 0) = 0; OneColor(0, 1) = 0; OneColor(0, 2) = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 3; j++) {
			Color(i, j) = 0;
			
		}
		PTS.row(i) = pts[i];
		
	}
	for (int i = 0; i < 100; i++) {
		Curve.row(i) = BsplinePoint(3, U, i / double(100), pts);
		Hcolor(i, 0) = 0.5; Hcolor(i, 1) = 0.5; Hcolor(i, 2) = 0.5;
	}
	std::cout << Curve << std::endl;
	viewer.data().set_points(PTS, Color);
	viewer.data().add_points(Curve, Hcolor);
	viewer.launch();
	//for (int i = 0; i < 8; i++) {
	//	
	//}
}
void plot_fitting_result() {
	Eigen::MatrixXd control_pts;
	Eigen::MatrixXd control_pts_color;
	Eigen::MatrixXd curve_pts; Eigen::MatrixXd curve_pts_color;
	Eigen::MatrixXd target_pts; Eigen::MatrixXd target_pts_color;
	visual_curve_fitting(control_pts, control_pts_color,
			curve_pts, curve_pts_color, target_pts, target_pts_color);
	Eigen::MatrixXi edges;
	vertices_to_edges(curve_pts, edges);
	igl::opengl::glfw::Viewer viewer;
	viewer.data().set_points(control_pts, control_pts_color);
	//viewer.data().add_points(curve_pts, curve_pts_color);
	viewer.data().add_points(target_pts, target_pts_color);
	std::cout << "target pts nbr, " << target_pts.rows() << std::endl;
	viewer.data().set_edges(curve_pts, edges, curve_pts_color.row(0));
	viewer.launch();
}

// scale is the length of the axis arrows
void draw_axis(const double scale) {
	Eigen::MatrixXd red(1, 3), green(1, 3), blue(1, 3);
	Eigen::MatrixXd origin(1, 3), xaxis(1, 3), yaxis(1, 3),zaxis(1, 3);
	origin.row(0) = Vector3d(0, 0, 0);
	red.row(0) = Vector3d(1, 0, 0);
	green.row(0) = Vector3d(0, 1, 0);
	blue.row(0) = Vector3d(0, 0, 1);
	Eigen::MatrixXd V1,V2, C;
	V1.resize(3, 3); V2.resize(3, 3);
	V1 << origin, origin, origin;
	V2 << red, green, blue;

	C.resize(3, 3);
	C << red, green, blue;
	V1 = V1 * scale;
	V2 = V2 * scale;
	//Eigen::MatrixXi E(3,2);
	//E.row(0) << 0, 1;
	//E.row(1) << 0, 2;
	//E.row(2) << 0, 3;
	global_viewer.data().add_edges(V1, V2, C);
	global_viewer.data().line_width = 3;
}

// this is to remove some faces of a mesh accroding to the vertices coordinates.
// axis select from 0, 1, 2. 
void remove_some_faces(const int axis, const double value, const bool remove_larger,
	const Eigen::MatrixXd& V, const Eigen::MatrixXi F, Eigen::MatrixXi& newF) {
	int rows = F.rows();
	newF.resize(1, 3);
	int already_updated = 0;
	for (int i = 0; i < rows; i++) {
		if (remove_larger) {
			if (V(F(i, 0), axis) > value || V(F(i, 1), axis) > value || V(F(i, 2), axis) > value) {
				continue;
			}
		}
		else {
			if (V(F(i, 0), axis) < value || V(F(i, 1), axis) < value || V(F(i, 2), axis) < value) {
				continue;
			}
		}
		newF.conservativeResize(already_updated + 1, 3);
		newF.row(already_updated) = F.row(i);
		already_updated++;

	}

}



void visual_and_chop_mesh(const bool write_mesh) {
	//const std::string path = "D:\\vs\\sparse_data_interpolation\\meshes\\";
	//const std::string filename = path + "camel_b.obj";
	//Eigen::MatrixXd V, Vclean; Eigen::MatrixXi F;
	//read_and_visual_mesh(filename, V, F);
	//Eigen::MatrixXd fcolor(1, 3), ecolor(1, 3);
	//fcolor.row(0) = Vector3d(0, 0.5, 0.5); ecolor.row(0) = Vector3d(0, 0, 0);

	/////////////////////////////////////////////
	////// parameterization part
	////Eigen::VectorXi bnd;
	////igl::boundary_loop(F, bnd);// boundary vertices detection
	////Eigen::MatrixXd bnd_uv, param;
	/////*igl::map_vertices_to_circle(V, bnd, bnd_uv);*/
	////map_vertices_to_square(V, bnd, bnd_uv);
	//////exit(0);
	////igl::harmonic(V, F, bnd, bnd_uv, 1, param);
	/////////////////////////////////////////////////
	//
	//Eigen::MatrixXi newF,Fclean;
	//remove_some_faces(2, 20, false, V, F, newF);
	//remove_some_faces(1, 32, false, V, newF, newF);
	//
	//generate_clean_mesh_data_for_parametrization(V, newF, Vclean, Fclean);
	//if (write_mesh)
	//	igl::write_triangle_mesh(path + "camel_small.obj", Vclean, Fclean);
	//Eigen::VectorXi bnd;
	//igl::boundary_loop(Fclean, bnd);
	//Eigen::MatrixXd visual_bnd(bnd.size(), 3);
	//for (int i = 0; i < bnd.size(); i++) {
	//	visual_bnd.row(i) = Vclean.row(bnd[i]);
	//}
	////std::cout << "boundary ids,\n" << bnd << std::endl;
	//global_viewer.data().set_mesh(Vclean, Fclean);
	//global_viewer.data().add_points(visual_bnd, fcolor);
	//draw_axis(10);
	//global_viewer.launch();


}


//void mesh_parameterization() {
//	const std::string path = "D:\\vs\\sparse_data_interpolation\\meshes\\";
//	const std::string filename = path + "camel_small.obj";
//	Eigen::MatrixXd Vori, V; Eigen::MatrixXi Fori, F;
//	read_and_visual_mesh(filename, Vori, Fori);
//	Eigen::MatrixXd fcolor(1, 3), ecolor(1, 3);
//	fcolor.row(0) = Vector3d(0, 0.5, 0.5); ecolor.row(0) = Vector3d(0, 0, 0);
//	V = Vori; F = Fori;
//	/////////////////////////////////////////
//	// parameterization part
//	Eigen::VectorXi bnd;
//	igl::boundary_loop(F, bnd);// boundary vertices detection
//	Eigen::MatrixXd bnd_uv, param;
//	/*igl::map_vertices_to_circle(V, bnd, bnd_uv);*/
//	map_vertices_to_square(V, bnd, bnd_uv);
//	//exit(0);
//	igl::harmonic(V, F, bnd, bnd_uv, 1, param);
//	/////////////////////////////////////////////
//
//
//	global_viewer.data().set_mesh(V, F);
//	draw_axis(10);
//	Eigen::MatrixXd firstP(1, 3);
//	firstP.row(0) = V.row(bnd[0]);
//	global_viewer.data().add_points(firstP, fcolor);
//	global_viewer.launch();
//
//
//}
int main() {
	//test_opengl();
	//int p = 3;
	//std::vector<double>U = { {0,0,0,0,0.1,0.4,0.7,0.9,1,1,1,1} };
	//draw_a_line();
	//draw_a_curve();
	//test_fitting();
	//plot_fitting_result();
	//test_curve_knot_fixing();
	//visual_mesh();
	//mesh_parameterization();
	visual_and_chop_mesh(false);
	return 0;
}