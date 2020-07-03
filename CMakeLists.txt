cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(mixedplanner)
INCLUDE_DIRECTORIES(
  include
  ${CMAKE_SOURCE_DIR}/include
)


find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(OpenMP REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

add_executable(mixedplanner src/planner.cpp src/planner.h src/environment.h src/continousPlanner.h src/visualisation.h)
target_link_libraries(mixedplanner ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})