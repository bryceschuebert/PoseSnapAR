cmake_minimum_required(VERSION 3.0.2)

set(CadExINV_LIBRARIES CadEx::INV)

if (NOT TARGET CadEx::INV)

    include("${CMAKE_CURRENT_LIST_DIR}/../helpers/cadex_macros.cmake")

    get_filename_component(_CadExINV_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)
    set(_CadExINV_OWN_INCLUDE_DIRS "${_CadExINV_install_prefix}/inc/")

    foreach(_dir ${_CadExINV_OWN_INCLUDE_DIRS})
        cadex_check_file_exists(INV "${_dir}")
    endforeach()

    set(CadExINV_INCLUDE_DIRS ${_CadExINV_OWN_INCLUDE_DIRS})
    set(CadExINV_DEFINITIONS "")
    set(CadExINV_COMPILE_DEFINITIONS "")

    cadex_set_module_dependencies(INV "Core;ACIS")

    add_library(CadEx::INV SHARED IMPORTED)

    set_property(TARGET CadEx::INV PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${_CadExINV_OWN_INCLUDE_DIRS})

    cadex_add_module_libs(INV "${_CadExINV_install_prefix}")

    cadex_check_file_exists(INV "${CMAKE_CURRENT_LIST_DIR}/CadExINVConfigVersion.cmake")
endif()
