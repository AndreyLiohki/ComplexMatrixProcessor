file(GLOB_RECURSE CORE_SRC CONFIGURE_DEPENDS "*.cpp" "*.h")

add_library(core ${CORE_SRC})
target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
