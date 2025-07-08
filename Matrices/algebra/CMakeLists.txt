set(ALGEBRA_SRC
    "MatrixProperties/MatrixProperties.cpp"
    "MatrixProperties/MatrixProperties.h"
    "MatrixOperations/MatrixOperations.cpp"
    "MatrixOperations/MatrixOperations.h"
    "Norms/Norms.h"
    "Norms/Norms.cpp"
)

add_library(algebra ${ALGEBRA_SRC})

target_include_directories(algebra PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/MatrixProperties
    ${CMAKE_CURRENT_SOURCE_DIR}/MatrixOperations
)

target_link_libraries(algebra PUBLIC core)