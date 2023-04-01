cmake_minimum_required (VERSION 3.13)
project(customizedviewer_qtquick_qml CXX)

file(GLOB SRC "${CMAKE_CURRENT_SOURCE_DIR}/*xx")
file(GLOB SRC2 "${CMAKE_CURRENT_SOURCE_DIR}/../baseviewer/*xx")
list(FILTER SRC2 EXCLUDE REGEX "/baseviewer/main.cxx$")
list(APPEND SRC ${SRC2})

add_executable(${PROJECT_NAME} WIN32 ${SRC})

find_package(CadEx COMPONENTS Core View ViewQtQuick STEP REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE CadEx::Core CadEx::View CadEx::ViewQtQuick CadEx::STEP)

find_package(Qt5 COMPONENTS Core Gui Qml Quick Widgets REQUIRED)
qt5_wrap_cpp(MOCS ${CMAKE_CURRENT_SOURCE_DIR}/../baseviewer/BaseViewerApplication.hxx)
qt5_add_resources(QRCS ${CMAKE_CURRENT_SOURCE_DIR}/resources/CustomizedViewerQml.qrc
                       ${CMAKE_CURRENT_SOURCE_DIR}/../baseviewer/resources/BaseQml.qrc)
target_sources(${PROJECT_NAME} PRIVATE ${MOCS} ${QRCS})
source_group("Generated Files" FILES  ${MOCS} ${QRCS})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Qml Qt5::Quick Qt5::Qml Qt5::Widgets)
if(ANDROID)
    find_package(Qt5 COMPONENTS AndroidExtras REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::AndroidExtras)
endif()

include("${CADEX_ROOT_DIR}/examples/cmake/extra.cmake")
