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

# On récupère tout les fichiers sources
file(GLOB SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
file(GLOB TESTS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/test/*.c")
file(GLOB APPS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/apps/*.c")

# On créer notre librairie de solveur de puzzle
add_library(puzzle_solver_lib STATIC ${SOURCES})

# MOVED TO PYTHON TESTING !!
# On créer tout les executable de tout nos tests
# foreach(TEST_FILE ${TESTS})
	# get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
	# add_executable(${TEST_NAME}.tst ${TEST_FILE})
	# target_link_libraries(${TEST_NAME}.tst puzzle_solver_lib)
# endforeach()

# On créer tout les executable de toutes nos applications
foreach(APP_FILE ${APPS})
	get_filename_component(APP_NAME ${APP_FILE} NAME_WE)
	add_executable(${APP_NAME} ${APP_FILE})
	target_link_libraries(${APP_NAME} puzzle_solver_lib)
endforeach()
