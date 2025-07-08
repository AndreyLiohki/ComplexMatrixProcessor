file(GLOB_RECURSE DECOMP_SRC "*.cpp" "*.h")

add_library(decompositions ${DECOMP_SRC})
target_include_directories(decompositions PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(decompositions PUBLIC core)
