cmake_minimum_required(VERSION 3.16)

project(OpenGLProject)

set(SRC_LIST ${PROJECT_SOURCE_DIR}/src/main.cpp ${PROJECT_SOURCE_DIR}/src/glad.c)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output)

include_directories(${PROJECT_SOURCE_DIR}/include)

link_directories(${PROJECT_SOURCE_DIR}/lib)
link_libraries(libglfw3.a)

add_executable(main ${SRC_LIST})