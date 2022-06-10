cmake_minimum_required(VERSION 3.21)

project(
Chatbot
VERSION 1.5
LANGUAGES CXX)
 
#Setting project's properties
if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CMAKE_CXX_EXTENSIONS OFF)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED True)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
    if (MSVC)
	    set(COMPILER_OPTIONS /RTC1 /EHa /WX)
        add_compile_options(${COMPILER_OPTIONS})
        message("Compiler options that were set ${COMPILER_OPTIONS}")    
    endif()
endif()

#Creating additional directories to work with the chatbot's data
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/utility)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/utility/database)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/utility/image)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/utility/table)

#The rest of required libraries were retrieved using vcpkg
#Looking for vcpkg

#find_path(VCPKG_DIR NAMES vcpkg/scripts/buildsystems/vcpkg.cmake)
#message("VCPKG_DIR include dir = ${VCPKG_DIR}")
include("C:/vcpkg/scripts/buildsystems/vcpkg.cmake")

#Boost libraries are header only
find_package(Boost REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

#REST-SDK
find_package(cpprestsdk CONFIG REQUIRED)

#SQLite3
find_package(unofficial-sqlite3 CONFIG REQUIRED)

#OpenCV
find_package(OpenCV REQUIRED)

#FTXUI
find_package(ftxui CONFIG REQUIRED)

#tabulate
find_package(tabulate CONFIG REQUIRED)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(src)
add_subdirectory(apps)

#GoogleTest optional
option(BUILD_TESTS "Build the tests")
if (BUILD_TESTS)
    find_package(GTest CONFIG REQUIRED)
    add_subdirectory(tests)
endif()