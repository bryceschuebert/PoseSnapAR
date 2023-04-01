cmake_minimum_required (VERSION 3.13)
project(visualizationmesher CXX)

file(GLOB SRC "${CMAKE_CURRENT_SOURCE_DIR}/*xx")
add_executable(${PROJECT_NAME} ${SRC})
target_compile_definitions(${PROJECT_NAME} PRIVATE __CADEX_PREVIEW_B_REP_TO_POLY_ASSOCIATIONS=1)

find_package(CadEx COMPONENTS Core REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE CadEx::Core)

set(CADEX_RUN_ARGUMENTS "${CADEX_EXAMPLES_MODELS_DIR}/LeverArm.xml")
include("${CADEX_ROOT_DIR}/examples/cmake/extra.cmake")
