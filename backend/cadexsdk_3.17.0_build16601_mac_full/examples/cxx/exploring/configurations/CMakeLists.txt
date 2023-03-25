cmake_minimum_required (VERSION 3.13)
project(configurations CXX)

file(GLOB SRC "${CMAKE_CURRENT_SOURCE_DIR}/*xx")
add_executable(${PROJECT_NAME} ${SRC})

find_package(CadEx COMPONENTS Core SLD REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE CadEx::Core CadEx::SLD)

set(CADEX_RUN_ARGUMENTS "${CADEX_EXAMPLES_MODELS_DIR}/Configuration_Part.SLDPRT")
include("${CADEX_ROOT_DIR}/examples/cmake/extra.cmake")
