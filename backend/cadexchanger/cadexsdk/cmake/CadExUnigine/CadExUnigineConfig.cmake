cmake_minimum_required(VERSION 3.0.2)

set(CadExUnigine_LIBRARIES CadEx::Unigine)

if(NOT TARGET CadEx::Unigine)

    include("${CMAKE_CURRENT_LIST_DIR}/../helpers/cadex_macros.cmake")

    get_filename_component(_CadExUnigine_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)
    set(_CadExUnigine_OWN_INCLUDE_DIRS "${_CadExUnigine_install_prefix}/inc/")

    foreach(_dir ${_CadExUnigine_OWN_INCLUDE_DIRS})
        cadex_check_file_exists(Unigine "${_dir}")
    endforeach()

    set(CadExUnigine_INCLUDE_DIRS ${_CadExUnigine_OWN_INCLUDE_DIRS})
    set(CadExUnigine_DEFINITIONS "")
    set(CadExUnigine_COMPILE_DEFINITIONS "")

    cadex_set_module_dependencies(Unigine "Core")

    add_library(CadEx::Unigine SHARED IMPORTED)

    set_property(TARGET CadEx::Unigine PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${_CadExUnigine_OWN_INCLUDE_DIRS})

    cadex_add_module_libs(Unigine "${_CadExUnigine_install_prefix}")

    cadex_check_file_exists(Unigine "${CMAKE_CURRENT_LIST_DIR}/CadExUnigineConfigVersion.cmake")

endif()
