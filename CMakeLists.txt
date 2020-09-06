##############################
# General Settings
##############################

cmake_minimum_required(VERSION 2.8)
project(libespm)
include(ExternalProject)

option(PROJECT_STATIC_RUNTIME "Build with static runtime libs (/MT)" ON)

set (Boost_USE_STATIC_LIBS ${PROJECT_STATIC_RUNTIME})
set (Boost_USE_MULTITHREADED ON)
set (Boost_USE_STATIC_RUNTIME ${PROJECT_STATIC_RUNTIME})

find_package(Boost REQUIRED COMPONENTS iostreams filesystem system locale)

ExternalProject_Add(GTest
                    PREFIX "external"
                    URL "https://github.com/google/googletest/archive/release-1.7.0.tar.gz"
                    INSTALL_COMMAND "")
ExternalProject_Get_Property(GTest SOURCE_DIR BINARY_DIR)
set (GTEST_INCLUDE_DIRS "${SOURCE_DIR}/include")
set (GTEST_LIBRARIES "${BINARY_DIR}/${CMAKE_CFG_INTDIR}/${CMAKE_STATIC_LIBRARY_PREFIX}gtest${CMAKE_STATIC_LIBRARY_SUFFIX}")

ExternalProject_Add(testing-plugins
                    PREFIX "external"
                    URL "https://github.com/WrinklyNinja/testing-plugins/archive/1.2.0.tar.gz"
                    CONFIGURE_COMMAND ""
                    BUILD_COMMAND ""
                    INSTALL_COMMAND "")

set(PROJECT_HEADERS "${CMAKE_SOURCE_DIR}/include/libespm/FormId.h"
                    "${CMAKE_SOURCE_DIR}/include/libespm/GameId.h"
                    "${CMAKE_SOURCE_DIR}/include/libespm/Group.h"
                    "${CMAKE_SOURCE_DIR}/include/libespm/Plugin.h"
                    "${CMAKE_SOURCE_DIR}/include/libespm/Record.h"
                    "${CMAKE_SOURCE_DIR}/include/libespm/Subrecord.h")

source_group("Header Files" FILES ${PROJECT_HEADERS})

# Include source and library directories.
include_directories("${CMAKE_SOURCE_DIR}/include"
                     ${Boost_INCLUDE_DIRS}
                     ${GTEST_INCLUDE_DIRS})

##############################
# Platform-Specific Settings
##############################

# Fix codepage warnings.
IF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    add_definitions (-DUNICODE -D_UNICODE)
ENDIF ()

# GCC and Clang settings.
if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++11")

    set(PROJECT_LIBRARIES "pthread")
else (MSVC)
    IF (PROJECT_STATIC_RUNTIME)
        FOREACH(flag
            CMAKE_C_FLAGS_RELEASE CMAKE_C_FLAGS_RELWITHDEBINFO
            CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_DEBUG_INIT
            CMAKE_CXX_FLAGS_RELEASE  CMAKE_CXX_FLAGS_RELWITHDEBINFO
            CMAKE_CXX_FLAGS_DEBUG  CMAKE_CXX_FLAGS_DEBUG_INIT)
            STRING(REPLACE "/MD"  "/MT" "${flag}" "${${flag}}")
            SET("${flag}" "${${flag}} /EHsc")
        ENDFOREACH()
    ENDIF ()
endif ()
