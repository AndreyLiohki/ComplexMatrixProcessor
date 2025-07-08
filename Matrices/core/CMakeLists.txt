set(CORE_SRC
    "ComplexNumber/ComplexNumber.cpp"
    "ComplexNumber/ComplexNumber.h"
    "Matrix/Matrix.cpp"
    "Matrix/Matrix.h"
    "SquareMatrix/SquareMatrix.cpp"
    "SquareMatrix/SquareMatrix.h"
)

add_library(core ${CORE_SRC})

target_include_directories(core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/ComplexNumber
    ${CMAKE_CURRENT_SOURCE_DIR}/Matrix
    ${CMAKE_CURRENT_SOURCE_DIR}/SquareMatrix
)