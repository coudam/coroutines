cmake_minimum_required(VERSION 3.8)
project(state_machine)

find_package(LLVM REQUIRED CONFIG)

SET (CMAKE_CXX_COMPILER "/usr/bin/clang++")

add_compile_options("-O2" "-g" "-std=c++2a" )
add_compile_options("-stdlib=libc++")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")

add_executable(state_machine 
	generator.hpp
	resumable.hpp
	state_machine.cpp
	states.hpp	
)

llvm_map_components_to_libnames(state_machine support core irreader)

target_link_libraries(state_machine ${state_machine})
