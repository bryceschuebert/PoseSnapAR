cmake_minimum_required(VERSION 3.0.2)

set(CadExDS3DXML_LIBRARIES CadEx::DS3DXML)

if (NOT TARGET CadEx::DS3DXML)

    include("${CMAKE_CURRENT_LIST_DIR}/../helpers/cadex_macros.cmake")

    get_filename_component(_CadExDS3DXML_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)
    set(_CadExDS3DXML_OWN_INCLUDE_DIRS "${_CadExDS3DXML_install_prefix}/inc/")

    foreach(_dir ${_CadExDS3DXML_OWN_INCLUDE_DIRS})
        cadex_check_file_exists(DS3DXML "${_dir}")
    endforeach()

    set(CadExDS3DXML_INCLUDE_DIRS ${_CadExDS3DXML_OWN_INCLUDE_DIRS})
    set(CadExDS3DXML_DEFINITIONS "")
    set(CadExDS3DXML_COMPILE_DEFINITIONS "")

    cadex_set_module_dependencies(DS3DXML "Core")

    add_library(CadEx::DS3DXML SHARED IMPORTED)

    set_property(TARGET CadEx::DS3DXML PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${_CadExDS3DXML_OWN_INCLUDE_DIRS})

    cadex_add_module_libs(DS3DXML "${_CadExDS3DXML_install_prefix}")

    cadex_check_file_exists(DS3DXML "${CMAKE_CURRENT_LIST_DIR}/CadExDS3DXMLConfigVersion.cmake")
endif()
