cmake_minimum_required (VERSION 3.13)
project(transfer CXX)

file(GLOB SRC "${CMAKE_CURRENT_SOURCE_DIR}/*xx")
add_executable(${PROJECT_NAME} ${SRC})

find_package(CadEx COMPONENTS Core REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE CadEx::Core)

set(CADEX_RUN_ARGUMENTS "${CADEX_EXAMPLES_MODELS_DIR}/omni_wheel.stp ${CMAKE_CURRENT_SOURCE_DIR}/omni_wheel.jt")
include("${CADEX_ROOT_DIR}/examples/cmake/extra.cmake")
