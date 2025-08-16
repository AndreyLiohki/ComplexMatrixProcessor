#include <iostream>
#include <complex>

#include "include/matrixlib/core/matrix.h"
#include "include/matrixlib/core/type_traits.h"
#include "include/matrixlib/algebra/matrix_operations.h"
#include "include/matrixlib/algebra/matrix_properties.h"
#include "include/matrixlib/algebra/norms.h"
#include "include/matrixlib/decompositions/lup_decomposition.h"
#include "include/matrixlib/decompositions/qr_decomposition.h"
#include "include/matrixlib/algebra/numerical_characteristics.h"

int main() {
	Core::Matrix<double> matrix_1(2, 2);
	Core::Matrix<double> matrix_2(2, 2);
	Core::Matrix<std::complex<double>> matrix_3(2, 2);

	Core::Matrix<double> m(3, 3);
    m(0, 0) = 1; m(0, 1) = 2; m(0, 2) = 3;
    m(1, 0) = 4; m(1, 1) = 5; m(1, 2) = 6;
    m(2, 0) = 7; m(2, 1) = 8; m(2, 2) = 10;
	
	matrix_1(0, 0) = 2;
	matrix_1(0, 1) = 3;
	matrix_1(1, 0) = 9;
	matrix_1(1, 1) = 6;

	matrix_2(0, 0) = -4;
	matrix_2(0, 1) = 6;
	matrix_2(1, 0) = -3;
	matrix_2(1, 1) = 5;

	matrix_3(0,0) = {0.0, -1.0}; 
	matrix_3(0,1) = {0.0, 0.0};
    matrix_3(1,0) = {0.0, 0.0}; 
	matrix_3(1,1) = {0.0, 1.0};

	auto result = (matrix_1 + matrix_2);
	auto result_2 = (matrix_1 * matrix_2);
	auto result_3 = (matrix_1 - matrix_2);

	Decompositions::LUP_Decomposition::Lup_Decomposition<double> obj(m);
	std::cout << obj.get_L()<<std::endl;
	std::cout << obj.get_P()<<std::endl;
	std::cout << obj.get_L()*obj.get_U()<<std::endl;
	std::cout << obj.get_P()*m<<std::endl;


}