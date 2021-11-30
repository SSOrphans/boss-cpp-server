cmake_minimum_required(VERSION 3.16.0)
project(BossCppServer VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
if (OpenSSL_FOUND)
	include_directories(${OpenSSL_INCLUDE_DIRS})
endif()

find_package(Boost 1.77.0 EXACT QUIET MODULE REQUIRED)
if (Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
endif()

find_package(LibXml2 REQUIRED)
if (LibXml2_FOUND)
	include_directories(${LibXml2_INCLUDE_DIRS})
endif()

add_subdirectory(source)
# add_subdirectory(tests)
