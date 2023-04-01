if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
    return()
endif()

cmake_minimum_required (VERSION 3.13)
project(cdxfbconverter CXX)

file(GLOB SRC "${CMAKE_CURRENT_SOURCE_DIR}/*xx")
add_executable(${PROJECT_NAME} ${SRC})

find_package(CadEx COMPONENTS Core REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE CadEx::Core)

set(CADEX_RUN_ARGUMENTS "${CADEX_EXAMPLES_MODELS_DIR}/Radial_Engine.jt ${CMAKE_CURRENT_SOURCE_DIR}/Radial_Engine.jt.cdxfb/scenegraph.cdxfb")
include("${CADEX_ROOT_DIR}/examples/cmake/extra.cmake")

