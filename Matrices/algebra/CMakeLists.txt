file(GLOB_RECURSE ALGEBRA_SRC CONFIGURE_DEPENDS "*.cpp" "*.h")

add_library(algebra ${ALGEBRA_SRC}   "MatrixOperations.h" "MatrixOperations.cpp")
target_include_directories(algebra PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(algebra PUBLIC core)  # Зависит от core
