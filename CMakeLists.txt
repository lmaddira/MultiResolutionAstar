cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(mixedplanner)
SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++14 -O3")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
INCLUDE_DIRECTORIES(
  include
  ${CMAKE_SOURCE_DIR}/include
)


find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
# find_package(OpenMP REQUIRED)
find_package(GLEW REQUIRED)
# find_package(GLFW REQUIRED)

find_package(glfw3 REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS} ${GLEW_LIBRARIES} ${GLFW_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} )
# /home/Downloads/glfw-3.3.2/include
add_library(visualisation src/visualisation.cpp src/visualisation.h)
target_link_libraries(visualisation ${OPENGL_LIBRARY} ${GLEW_LIBRARIES} glfw glut)

add_executable(mixedplanner src/planner.cpp src/planner.h src/environment.h src/continousPlanner.h)
target_link_libraries(mixedplanner visualisation ${OPENGL_LIBRARY} ${GLEW_LIBRARIES} glfw glut)

# add_executable(visualisation src/visualisation.cpp)
# target_link_libraries(visualisation ${OPENGL_LIBRARY} ${GLEW_LIBRARIES} glfw glut)