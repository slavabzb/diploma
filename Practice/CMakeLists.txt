cmake_minimum_required( VERSION 2.8 )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/Tests )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11" )

set( PROJECT Diploma )

set( SOURCE
  Sample.cpp
  Tests/ConstructionTest.cpp
)

project( ${PROJECT} )

add_executable( ${PROJECT} ${SOURCE} )

target_link_libraries( ${PROJECT} pthread )
target_link_libraries( ${PROJECT} cppunit )
