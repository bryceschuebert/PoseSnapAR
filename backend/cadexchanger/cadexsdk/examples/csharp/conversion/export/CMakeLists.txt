cmake_minimum_required(VERSION 3.13)

project(export LANGUAGES CSharp)

include(CSharpUtilities)

file(GLOB SRC "*.cs")

add_executable(${PROJECT_NAME} ${SRC} ./../../Properties/AssemblyInfo.cs ./../../cadex_license.cs)

set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DOTNET_TARGET_FRAMEWORK_VERSION "v3.5")

# examples always link to win64 csharp libraries
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DOTNET_REFERENCES
                                             "System"
                                             "${CADEX_ROOT_DIR}/csharp/win64/CadExCoreNet.dll"
                                             "${CADEX_ROOT_DIR}/csharp/win64/CadExOBJNet.dll")

set(CADEX_RUN_ARGUMENTS "${CADEX_EXAMPLES_MODELS_DIR}/as1.xml ${CMAKE_CURRENT_SOURCE_DIR}/as1.obj")
include("${CADEX_ROOT_DIR}/examples/cmake/extra.cmake")
