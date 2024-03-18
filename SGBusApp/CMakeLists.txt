cmake_minimum_required(VERSION 3.5)

project(27_practice VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
set(json_path "C:\\cplusplus\\json")
set(curl_path "C:\\cplusplus\\vcpkg\\packages\\curl_x64-windows")
set(cv2_path "C:\\cplusplus\\vcpkg\\packages\\opencv4_x64-windows")
# >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(27_practice
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        businfo.h businfo.cpp
        page1.h page1.cpp page1.ui
        resources.qrc
        style.json
        page2.h page2.cpp page2.ui
        buseta.h buseta.cpp
        bus_info.db
        businfoquery.h businfoquery.cpp
        stackedpage.h stackedpage.cpp stackedpage.ui

        customitemdelegate.h customitemdelegate.cpp
        page4.h page4.cpp page4.ui
        customitemdelegate.h customitemdelegate.cpp
        customitemmodel.h customitemmodel.cpp
        page5.h page5.cpp page5.ui


    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET 27_practice APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(27_practice SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(27_practice
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(27_practice PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
                                          Qt${QT_VERSION_MAJOR}::Sql)
# >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
target_include_directories(${PROJECT_NAME} PRIVATE ${json_path}\\include
                                                   ${curl_path}\\include
                                                   ${cv2_path}\\include)

target_link_libraries(${PROJECT_NAME} PRIVATE ${curl_path}\\lib\\libcurl.lib
                                              ${cv2_path}\\lib\\opencv_core4.lib
                                              ${cv2_path}\\lib\\opencv_imgproc4.lib
                                              ${cv2_path}\\lib\\opencv_highgui4.lib)
# >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.27_practice)
endif()
set_target_properties(27_practice PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS 27_practice
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(27_practice)
endif()
