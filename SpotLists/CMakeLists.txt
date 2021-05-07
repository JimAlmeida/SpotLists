cmake_minimum_required(VERSION 3.1.0)

project (NetworkAPP VERSION 1.0.0 LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/whoshuu/cpr.git GIT_TAG c8d33915dbd88ad6c92b258869b03aba06587ff9) # the commit hash for 1.5.0
FetchContent_MakeAvailable(cpr)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

list(APPEND CMAKE_PREFIX_PATH "C:/Qt/5.15.2/msvc2019_64")

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(
    APP
    MainWindow.cpp
    main.cpp
    SpotLists.qrc
)

target_link_libraries (APP cpr::cpr Qt5::Widgets )