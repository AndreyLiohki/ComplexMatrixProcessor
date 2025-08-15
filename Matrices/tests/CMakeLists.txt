enable_testing()

# Все тестовые файлы
set(TEST_SOURCES
    matrix_tests/double_matrices_addition.cpp
    matrix_tests/double_matrices_multiplication.cpp
    matrix_tests/double_matrices_substraction.cpp
    matrix_tests/float_matrices_addition.cpp
    matrix_tests/float_matrices_multiplication.cpp
    matrix_tests/float_matrices_substraction.cpp
    matrix_tests/long_double_matrices_addition.cpp
    matrix_tests/long_double_matrices_substraction.cpp
    matrix_tests/iterator_methods_test.cpp
    matrix_tests/matrix_functions_test.cpp
    properties_test/matrix_properties_test.cpp
    operations_test/matrix_operations_test.cpp
    numerical_characteristics/matrix_numerical_characteristics.cpp
    norms/test_matrix_norms.cpp
)

add_executable(test_runner ${TEST_SOURCES})
target_link_libraries(test_runner matrixlib gtest gtest_main)

add_test(NAME AllMatrixTests COMMAND test_runner)
