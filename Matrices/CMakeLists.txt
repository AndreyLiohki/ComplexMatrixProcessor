cmake_minimum_required(VERSION 3.10)
project(MatrixLib)

# Стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем include директорию для шаблонов
include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(matrixlib INTERFACE)
target_include_directories(matrixlib INTERFACE ${CMAKE_SOURCE_DIR}/include)

# Подключаем исходники и тесты
add_subdirectory(tests)

# Главный исполняемый файл (если нужен)
add_executable(main main.cpp)
target_link_libraries(main matrixlib)

# Чтобы можно было запускать тесты через ctest
enable_testing()
cmake_minimum_required(VERSION 3.10)
project(MatrixLib)
