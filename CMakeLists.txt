cmake_minimum_required(VERSION 3.10)
project(LOMA_puzzle_solver)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

if(MSVC)
	# Pas de warning sur windows c'est trop chiant
	# add_compile_options(/W4 /WX)
else()
	add_compile_options(-Wall -Werror)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/header)

set(SRCS
	src/main.c
	src/cnf.c
	src/interface.c
	src/letter.c
	src/letter_pos.c
	src/puzzle.c
	src/rule.c
	src/sat.c
	src/solver.c
)

add_executable(puzzle_solver ${SRCS})
