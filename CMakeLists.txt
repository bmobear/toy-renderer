cmake_minimum_required(VERSION 2.8)
project(toy-renderer)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# OpenGL
# FIND GLUT
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})
if(NOT GLUT_FOUND)
    message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)
# FIND OPENGL
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)
# FIND GLEW
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_PATH})
if(NOT GLEW_FOUND)
    message(ERROR " GLEW not found!")
endif(NOT GLEW_FOUND)

# OpenCV
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

# OpenMesh
find_package(OpenMesh REQUIRED)
include_directories(${OPENMESH_INCLUDE_DIRS})
set_property(
    DIRECTORY
    APPEND PROPERTY COMPILE_DEFINITIONS _USE_MATH_DEFINES
)

# Boost
find_package( Boost 1.36.0 COMPONENTS system filesystem REQUIRED )
include_directories( ${Boost_INCLUDE_DIR} )

# ToyRenderer
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -lX11")

file(GLOB src "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(toy-renderer ${src})

target_link_libraries(toy-renderer ${OpenCV_LIBS} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARY}  ${Boost_LIBRARIES} ${Boost_FILESYSTEM_LIBRARY} ${OPENMESH_LIBRARIES})

