cmake_minimum_required( VERSION 2.8 )

set( PROJECT Diploma )

project( ${PROJECT} )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -pthread" )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

set( SOURCE
  main.cpp
  ParallelHandler.cpp
  Tests/MatrixTest.cpp
  HelperClasses/MatrixPrinter.cpp
  HelperClasses/TimeMeasurer.cpp
  HelperClasses/Statistics.cpp
)

add_executable( ${PROJECT} ${SOURCE} )

target_link_libraries( ${PROJECT} cppunit )
target_link_libraries( ${PROJECT} gmpxx )
target_link_libraries( ${PROJECT} gmp )
