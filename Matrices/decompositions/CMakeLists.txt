set(CORE_SRC
    "CholeskyDecomposition/CholeskyDecomposition.cpp"
    "CholeskyDecomposition/CholeskyDecomposition.h"
    "LUPDecomposition/LUPDecomposition.cpp"
    "LUPDecomposition/LUPDecomposition.h"
    "QRDecomposition/QRDecomposition.cpp"
    "QRDecomposition/QRDecomposition.h"
    "SVDDecomposition/SVDDecomposition.cpp"
    "SVDDecomposition/SVDDecomposition.h"
)


add_library(decompositions ${CORE_SRC})

target_include_directories(core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/CholeskyDecomposition
    ${CMAKE_CURRENT_SOURCE_DIR}/LUPDecomposition
    ${CMAKE_CURRENT_SOURCE_DIR}/QRDecomposition
    ${CMAKE_CURRENT_SOURCE_DIR}/SVDDecomposition
)