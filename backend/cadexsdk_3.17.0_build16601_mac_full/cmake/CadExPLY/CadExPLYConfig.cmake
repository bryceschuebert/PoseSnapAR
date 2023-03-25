cmake_minimum_required(VERSION 3.0.2)

set(CadExPLY_LIBRARIES CadEx::PLY)

if(NOT TARGET CadEx::PLY)

    include("${CMAKE_CURRENT_LIST_DIR}/../helpers/cadex_macros.cmake")

    get_filename_component(_CadExPLY_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)
    set(_CadExPLY_OWN_INCLUDE_DIRS "${_CadExPLY_install_prefix}/inc/")

    foreach(_dir ${_CadExPLY_OWN_INCLUDE_DIRS})
        cadex_check_file_exists(PLY "${_dir}")
    endforeach()

    set(CadExPLY_INCLUDE_DIRS ${_CadExPLY_OWN_INCLUDE_DIRS})
    set(CadExPLY_DEFINITIONS "")
    set(CadExPLY_COMPILE_DEFINITIONS "")

    cadex_set_module_dependencies(PLY "Core")

    add_library(CadEx::PLY SHARED IMPORTED)

    set_property(TARGET CadEx::PLY PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${_CadExPLY_OWN_INCLUDE_DIRS})

    cadex_add_module_libs(PLY "${_CadExPLY_install_prefix}")

    cadex_check_file_exists(PLY "${CMAKE_CURRENT_LIST_DIR}/CadExPLYConfigVersion.cmake")

endif()
