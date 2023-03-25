cmake_minimum_required (VERSION 3.13)
project(validationproperties CXX)

file(GLOB SRC "${CMAKE_CURRENT_SOURCE_DIR}/*xx")
add_executable(${PROJECT_NAME} ${SRC})

find_package(CadEx COMPONENTS Core REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE CadEx::Core)

include("${CADEX_ROOT_DIR}/examples/cmake/extra.cmake")
