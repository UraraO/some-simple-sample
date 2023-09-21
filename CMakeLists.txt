cmake_minimum_required(VERSION 3.24)
project(simple_example)

set(CMAKE_CXX_STANDARD 23)

set(SRC_FILE
	main.cpp

)

add_executable(main ${SRC_FILE})

add_subdirectory(backup)
add_subdirectory(Cpp_samples)


