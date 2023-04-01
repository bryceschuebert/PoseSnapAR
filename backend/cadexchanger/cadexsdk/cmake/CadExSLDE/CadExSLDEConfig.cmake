cmake_minimum_required(VERSION 3.0.2)

set(CadExSLDE_LIBRARIES CadEx::SLDE)

if (NOT TARGET CadEx::SLDE)

    include("${CMAKE_CURRENT_LIST_DIR}/../helpers/cadex_macros.cmake")

    get_filename_component(_CadExSLDE_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)
    set(_CadExSLDE_OWN_INCLUDE_DIRS "${_CadExSLDE_install_prefix}/inc/")

    foreach(_dir ${_CadExSLDE_OWN_INCLUDE_DIRS})
        cadex_check_file_exists(SLDE "${_dir}")
    endforeach()

    set(CadExSLDE_INCLUDE_DIRS ${_CadExSLDE_OWN_INCLUDE_DIRS})
    set(CadExSLDE_DEFINITIONS "")
    set(CadExSLDE_COMPILE_DEFINITIONS "")

    cadex_set_module_dependencies(SLDE "Core")

    add_library(CadEx::SLDE SHARED IMPORTED)

    set_property(TARGET CadEx::SLDE PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${_CadExSLDE_OWN_INCLUDE_DIRS})

    cadex_add_module_libs(SLDE "${_CadExSLDE_install_prefix}")

    cadex_check_file_exists(SLDE "${CMAKE_CURRENT_LIST_DIR}/CadExSLDEConfigVersion.cmake")

endif()