cmake_minimum_required( VERSION 2.8 )

set( PROJECT Diploma )

project( ${PROJECT} )

if (UNIX)
  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x" )
endif()

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/Tests )

set( SOURCE
  main.cpp
  Tests/MatrixTest.cpp
)

add_executable( ${PROJECT} ${SOURCE} )

target_link_libraries( ${PROJECT} pthread )
target_link_libraries( ${PROJECT} cppunit )
