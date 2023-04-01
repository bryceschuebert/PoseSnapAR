cmake_minimum_required (VERSION 3.13)
project(meshsimplify CXX)

file(GLOB SRC "${CMAKE_CURRENT_SOURCE_DIR}/*xx")
add_executable(${PROJECT_NAME} ${SRC})
target_compile_definitions(${PROJECT_NAME} PRIVATE __CADEX_PREVIEW_ADVANCED_GEOMETRY)

find_package(CadEx COMPONENTS Core AdvGeom REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE CadEx::Core CadEx::AdvGeom)

set(CADEX_RUN_ARGUMENTS "${CADEX_EXAMPLES_MODELS_DIR}/Little_River_1974.wrl ${CMAKE_CURRENT_SOURCE_DIR}/Little_River_1974.xml")
include("${CADEX_ROOT_DIR}/examples/cmake/extra.cmake")
