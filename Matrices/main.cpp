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
	matrix_1(0, 0) = 2;
	matrix_1(0, 1) = 3;
	matrix_1(1, 0) = 9;
	matrix_1(1, 1) = 6;

	matrix_2(0, 0) = 3;
	matrix_2(0, 1) = 5;
	matrix_2(1, 0) = 1;
	matrix_2(1, 1) = 3;

	auto result = (matrix_1 + matrix_2);
	auto result_2 = (matrix_1 * matrix_2);
	auto result_3 = (matrix_1 - matrix_2);

	Decompositions::LUP_Decomposition::Lup_Decomposition<double> obj(matrix_2);
	std::cout << obj.get_L();
	std::cout << std::endl;

	std::cout << obj.get_U();
	std::cout << std::endl; 

	std::cout << obj.get_P();
	std::cout << std::endl;

	std::cout << Algebra::Characteristics::determinant(obj);
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	Decompositions::QR_Decomposition::Qr_Decomposition<double> obj_2(matrix_1);

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << obj_2.get_Q() << std::endl;
	std::cout << obj_2.get_R() << std::endl;

	std::cout << obj_2.get_Q() * obj_2.get_R() << std::endl;
	std::cout << obj_2.get_Q() * Algebra::Operations::transpose(obj_2.get_Q()) << std::endl;


}